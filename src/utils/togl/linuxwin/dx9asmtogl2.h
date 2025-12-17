//========= Copyright Valve Corporation, All rights reserved. ============//
//                       TOGL CODE LICENSE
//
//  Copyright 2011-2014 Valve Corporation
//  All Rights Reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//------------------------------------------------------------------------------
// DX9AsmToGL2.h
//------------------------------------------------------------------------------
#pragma once
#include "tier1/utlstring.h"

#define DISASM_OK      0
#define DISASM_ERROR   1

#define MAX_SHADER_CONSTANTS	512

#define MAX_DECLARED_OUTPUTS	32
#define MAX_DECLARED_INPUTS	32

#define HEXCODE_HEADER		"// Hex: "

// Option bits
#define D3DToGL_OptionUseEnvParams				0x0001
#define D3DToGL_OptionDoFixupZ					0x0002		// Add instructions to put Z in the right interval for GL
#define D3DToGL_OptionDoFixupY					0x0004		// Add instructions to flip the Y over for GL
#define D3DToGL_OptionDoUserClipPlanes			0x0008		// ARB mode: Include OPTION vertex_program_2 and append DP4's to write into oCLP[0] and oCLP[1]
// GLSL mode: generate code to write gl_ClipVertex

#define D3DToGL_AddHexComments					0x0020		// Include hex comments in the code for debugging
#define D3DToGL_PutHexCommentsAfterLines		0x0040		// If D3DToGL_AddHexComments is set, this puts the codes to the right, rather than on separate lines
#define D3DToGL_GeneratingDebugText				0x0080		// This tells it that we're just getting info for debugging so go easy on asserts and errors
#define D3DToGL_OptionSRGBWriteSuffix			0x0400		// Tack sRGB conversion suffix on to pixel shaders
#define D3DToGL_OptionGenerateBoneUniformBuffer	0x0800		// if enabled, the vertex shader "bone" registers (all regs DXABSTRACT_VS_FIRST_BONE_SLOT and higher) will be separated out into another uniform buffer (vcbone)
#define D3DToGL_OptionUseBindlessTexturing		0x1000
#define D3DToGL_OptionSpew						0x80000000

// Code for which component of the "dummy" address register is needed by an instruction
#define ARL_DEST_NONE		-1
#define ARL_DEST_X			 0
#define ARL_DEST_Y			 1
#define ARL_DEST_Z			 2
#define ARL_DEST_W			 3

class D3DToGL {
private:
	// Pointers for dwToken stream management
	uint32* m_pdwBaseToken;
	uint32* m_pdwNextToken;

	// Vertex shader or pixel shader, and version (necessary because some opcodes alias)
	bool m_bVertexShader;
	uint32 m_dwMinorVersion;
	uint32 m_dwMajorVersion;

	// Option flags
	bool m_bUseEnvParams; // set D3DToGL_OptionUseEnvParams in 'options' to use
	bool m_bDoFixupZ; // set D3DToGL_OptionDoFixupZ
	bool m_bDoFixupY; // set D3DToGL_OptionDoFixupZ
	bool m_bDoUserClipPlanes; // set D3DToGL_OptionDoUserClipPlanes
	bool m_bSpew; // set D3DToGL_OptionSpew
	bool m_bGenerateSRGBWriteSuffix; // set D3DToGL_OptionSRGBWriteSuffix
	bool m_bGenerateBoneUniformBuffer;
	bool m_bUseBindlessTexturing;

	// Counter for dealing with nested loops
	int m_nLoopDepth;

	// Add "// Hex: 0xFFEEF00"-type statements after each instruction is parsed.
	bool m_bAddHexCodeComments; // set D3DToGL_AddHexComments

	// Only applicable if m_bAddHexCodeComments is true.
	// If this is true, then it puts the hex code comments to the right of the instructions in a comment
	// rather than preceding the instructions.
	// Defaults to FALSE.
	bool m_bPutHexCodesAfterLines; // set D3DToGL_PutHexCommentsAtEnd

	// This tells it that we're just getting info for debugging so go easy on asserts and errors.
	// Defaults to FALSE.
	bool m_bGeneratingDebugText;

	// Various scratch temps needed to handle mis-matches in instruction sets between D3D and OpenGL
	bool m_bNeedsD2AddTemp;
	bool m_bNeedsNRMTemp;
	bool m_bDeclareAddressReg;
	bool m_bNeedsLerpTemp;
	bool m_bNeedsSinCosDeclarations;

	// Keep track of which vs outputs are used so we can declare them
	bool m_bDeclareVSOPos;
	bool m_bDeclareVSOFog;
	uint32 m_dwTexCoordOutMask;

	int32 m_nVSPositionOutput;

	// Mask of varyings which need centroid decoration
	uint32 m_nCentroidMask;

	// Keep track of which temps are used so they can be declared
	uint32 m_dwTempUsageMask;
	uint32 m_dwTempBoolUsageMask;
	bool m_bOutputColorRegister[ 4 ];
	bool m_bOutputDepthRegister;

	// Declaration of integer and bool constants
	uint32 m_dwConstIntUsageMask;
	uint32 m_dwConstBoolUsageMask;

	uint32 m_dwDefConstIntUsageMask;
	uint32 m_dwDefConstIntIterCount[ 32 ];

	// Did we use atomic_temp_var?
	bool m_bUsedAtomicTempVar;

	// Track constants so we know how to declare them
	bool m_bConstantRegisterDefined[ MAX_SHADER_CONSTANTS ];

	// Track sampler types when declared so we can properly decorate TEX instructions
	uint32 m_dwSamplerTypes[ 32 ];

	// Track sampler usage
	uint32 m_dwSamplerUsageMask;

	// Track shadow sampler usage
	int m_nShadowDepthSamplerMask;
	bool m_bDeclareShadowOption;

	// Track attribute references
	// init to 0xFFFFFFFF (unhit)
	// index by (dwRegToken & D3DSP_REGNUM_MASK) in VS DCL insns
	// fill with (usage<<4) | (usage index).
	uint32 m_dwAttribMap[ 16 ];

	// Register high water mark
	uint32 m_nHighestRegister;
	int32 m_nHighestBoneRegister;

	// GLSL does indentation for readability
	int m_NumIndentTabs;

	// Output buffers.
	CUtlBuffer* m_pBufHeaderCode;
	CUtlBuffer* m_pBufAttribCode;
	CUtlBuffer* m_pBufParamCode;
	CUtlBuffer* m_pBufALUCode;

	char* m_pFinalAssignmentsCode;
	int m_nFinalAssignmentsBufSize;

	// Recorded positions for debugging.
	uint32* m_pRecordedInputTokenStart;
	int m_nRecordedParamCodeStrlen;
	int m_nRecordedALUCodeStrlen;
	int m_nRecordedAttribCodeStrlen;

	// In GLSL mode, these store the semantic attached to each oN register.
	// They are the values that you pass to GetUsageIndexAndString.
	uint32 m_DeclaredOutputs[ MAX_DECLARED_OUTPUTS ];

	uint32 m_DeclaredInputs[ MAX_DECLARED_INPUTS ];

	// Have they used the tangent input semantic (i.e. is g_pTangentAttributeName declared)?
	bool m_bTangentInputUsed;

	bool m_bUsesDSTInstruction;

private:
	// Utilities to aid in decoding token stream
	auto GetNextToken() -> uint32;
	auto SkipTokens( uint32 numToSkip ) -> void;
	auto Opcode( uint32 dwToken ) -> uint32;
	auto OpcodeSpecificData( uint32 dwToken ) -> uint32;
	auto TextureType( uint32 dwToken ) -> uint32;
	auto GetRegType( uint32 dwRegToken ) -> uint32;

	// Write to the different buffers.
	auto StrcatToHeaderCode( const char* pBuf ) -> void;
	auto StrcatToALUCode( const char* pBuf ) -> void;
	auto StrcatToParamCode( const char* pBuf ) -> void;
	auto StrcatToAttribCode( const char* pBuf ) -> void;
	auto PrintToBufWithIndents( CUtlBuffer& buf, const char* pFormat, ... ) -> void;

	// This helps write the token hex codes into the output stream for debugging.
	auto AddTokenHexCodeToBuffer( char* pBuffer, int nSize, int nLastStrlen ) -> void;
	auto RecordInputAndOutputPositions() -> void;
	auto AddTokenHexCode() -> void;

	// Utilities for decoding tokens in to strings according to ASM syntax
	auto PrintOpcode( uint32 inst, char* buff, int nBufLen ) -> void;

	// fSemanticFlags is SEMANTIC_INPUT or SEMANTIC_OUTPUT.
	auto PrintUsageAndIndexToString( uint32 dwToken, char* strUsageUsageIndexName, int nBufLen, int fSemanticFlags ) -> void;
	auto GetUsageAndIndexString( uint32 dwToken, int fSemanticFlags ) -> CUtlString;
	auto GetParameterString( uint32 dwToken, uint32 dwSourceOrDest, bool bForceScalarSource, int* pARLDestReg ) -> CUtlString;
	auto GetGLSLOperatorString( uint32 inst ) -> const char*;

	auto PrintParameterToString( uint32 dwToken, uint32 dwSourceOrDest, char* pRegisterName, int nBufLen, bool bForceScalarSource, int* pARLDestReg ) -> void;

	auto InsertMoveFromAddressRegister( CUtlBuffer* pCode, int nARLComp0, int nARLComp1, int nARLComp2 = ARL_DEST_NONE ) -> void;
	auto InsertMoveInstruction( CUtlBuffer* pCode, int nARLComponent ) -> void;
	auto FlagIndirectRegister( uint32 dwToken, int* pARLDestReg ) -> void;

	// Utilities for decoding tokens in to strings according to GLSL syntax
	auto OpenIntrinsic( uint32 inst, char* buff, int nBufLen, uint32 destDimension, uint32 nArgumentDimension ) -> bool;
	auto PrintIndentation( char* pBuf, int nBufLen ) -> void;

	auto MaintainAttributeMap( uint32 dwToken, uint32 dwRegToken ) -> uint32;

	auto FixGLSLSwizzle( const char* pDestRegisterName, const char* pSrcRegisterName ) -> CUtlString;
	auto WriteGLSLCmp( const char* pDestReg, const char* pSrc0Reg, const char* pSrc1Reg, const char* pSrc2Reg ) -> void;
	auto WriteGLSLSamplerDefinitions() -> void;
	auto WriteGLSLOutputVariableAssignments() -> void;
	auto WriteGLSLInputVariableAssignments() -> void;
	auto NoteTangentInputUsed() -> void;

	auto Handle_DCL() -> void;
	auto Handle_DEF() -> void;
	auto Handle_DEFIB( uint32 nInstruction ) -> void;
	auto Handle_MAD( uint32 nInstruction ) -> void;
	auto Handle_DP2ADD() -> void;
	auto Handle_SINCOS() -> void;
	auto Handle_LRP( uint32 nInstruction ) -> void;
	auto Handle_TEX( uint32 dwToken, bool bIsTexLDL ) -> void;
	auto Handle_TexLDD( uint32 nInstruction ) -> void;
	auto Handle_TexCoord() -> void;
	auto Handle_UnaryOp( uint32 nInstruction ) -> void;
	auto Handle_BREAKC( uint32 dwToken ) -> void;
	auto HandleBinaryOp_GLSL( uint32 nInstruction ) -> void;
	auto HandleBinaryOp_ASM( uint32 nInstruction ) -> void;
	auto Handle_CMP() -> void;
	auto Handle_NRM() -> void;
	auto Handle_DeclarativeNonDclOp( uint32 nInstruction ) -> void;

public:
	D3DToGL();

	auto TranslateShader( uint32* code, CUtlBuffer* pBufDisassembledCode, bool* bVertexShader, uint32 options, int32 nShadowDepthSamplerMask, uint32 nCentroidMask, char* debugLabel ) -> int;
};
