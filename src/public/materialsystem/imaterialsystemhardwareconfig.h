//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $Header: $
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "tier1/interface.h"

//-----------------------------------------------------------------------------
// GL helpers
//-----------------------------------------------------------------------------
ALWAYS_INLINE auto IsEmulatingGL() -> bool {
	static bool bIsEmulatingGL{ Plat_GetCommandLineA() ? strstr( Plat_GetCommandLineA(), "-r_emulate_gl" ) != nullptr : false };
	return bIsEmulatingGL;
}

ALWAYS_INLINE auto IsOpenGL() -> bool {
	return IsPlatformOpenGL() or IsEmulatingGL();
}

//-----------------------------------------------------------------------------
// Material system interface version
//-----------------------------------------------------------------------------
#define MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION "MaterialSystemHardwareConfig012"

// HDRFIXME NOTE: must match common_ps_fxc.h
enum HDRType_t {
	HDR_TYPE_NONE,
	HDR_TYPE_INTEGER,
	HDR_TYPE_FLOAT,
};

// For now, vertex compression is simply "on or off" (for the sake of simplicity
// and MeshBuilder perf.), but later we may support multiple flavours.
enum VertexCompressionType_t {
	// This indicates an uninitialized VertexCompressionType_t value
	VERTEX_COMPRESSION_INVALID = 0xFFFFFFFF,

	// 'VERTEX_COMPRESSION_NONE' means that no elements of a vertex are compressed
	VERTEX_COMPRESSION_NONE = 0,

	// Currently (more stuff may be added as needed), 'VERTEX_COMPRESSION_ON' means:
	//  - if a vertex contains VERTEX_ELEMENT_NORMAL, this is compressed
	//    (see CVertexBuilder::CompressedNormal3f)
	//  - if a vertex contains VERTEX_ELEMENT_USERDATA4 (and a normal - together defining a tangent
	//    frame, with the binormal reconstructed in the vertex shader), this is compressed
	//    (see CVertexBuilder::CompressedUserData)
	//  - if a vertex contains VERTEX_ELEMENT_BONEWEIGHTSx, this is compressed
	//    (see CVertexBuilder::CompressedBoneWeight3fv)
	VERTEX_COMPRESSION_ON = 1
};


// use DEFCONFIGMETHOD to define time-critical methods that we want to make just return constants
// on the 360, so that the checks will happen at compile time. Not all methods are defined this way
// - just the ones that I perceive as being called often in the frame interval.
#define DEFCONFIGMETHOD( $retType, $method, $xboxReturnValue ) \
	virtual auto $method const -> $retType = 0;


//-----------------------------------------------------------------------------
// Material system configuration
//-----------------------------------------------------------------------------
class IMaterialSystemHardwareConfig {
public:
	static constexpr auto INTERFACE_VERSION{ MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION };
public:
	// on xbox, some methods are inlined to return constants

	DEFCONFIGMETHOD( bool, HasDestAlphaBuffer(), true );
	DEFCONFIGMETHOD( bool, HasStencilBuffer(), true );
	virtual auto GetFrameBufferColorDepth() const -> int = 0;
	virtual auto GetSamplerCount() const -> int = 0;
	virtual auto HasSetDeviceGammaRamp() const -> bool = 0;
	DEFCONFIGMETHOD( bool, SupportsCompressedTextures(), true );
	virtual auto SupportsCompressedVertices() const -> VertexCompressionType_t = 0;
	DEFCONFIGMETHOD( bool, SupportsNormalMapCompression(), true );
	DEFCONFIGMETHOD( bool, SupportsVertexAndPixelShaders(), true );
	DEFCONFIGMETHOD( bool, SupportsPixelShaders_1_4(), true );
	DEFCONFIGMETHOD( bool, SupportsStaticControlFlow(), true );
	DEFCONFIGMETHOD( bool, SupportsPixelShaders_2_0(), true );
	DEFCONFIGMETHOD( bool, SupportsVertexShaders_2_0(), true );
	virtual auto MaximumAnisotropicLevel() const -> int = 0;// 0 means no anisotropic filtering
	virtual auto MaxTextureWidth() const -> int = 0;
	virtual auto MaxTextureHeight() const -> int = 0;
	virtual auto TextureMemorySize() const -> int = 0;
	virtual auto SupportsOverbright() const -> bool = 0;
	virtual auto SupportsCubeMaps() const -> bool = 0;
	virtual auto SupportsMipmappedCubemaps() const -> bool = 0;
	virtual auto SupportsNonPow2Textures() const -> bool = 0;

	// The number of texture stages represents the number of computations
	// we can do in the fixed-function pipeline, it is *not* related to the
	// simultaneous number of textures we can use
	virtual auto GetTextureStageCount() const -> int = 0;
	virtual auto NumVertexShaderConstants() const -> int = 0;
	virtual auto NumPixelShaderConstants() const -> int = 0;
	virtual auto MaxNumLights() const -> int = 0;
	virtual auto SupportsHardwareLighting() const -> bool = 0;
	virtual auto MaxBlendMatrices() const -> int = 0;
	virtual auto MaxBlendMatrixIndices() const -> int = 0;
	virtual auto MaxTextureAspectRatio() const -> int = 0;
	virtual auto MaxVertexShaderBlendMatrices() const -> int = 0;
	virtual auto MaxUserClipPlanes() const -> int = 0;
	virtual auto UseFastClipping() const -> bool = 0;

	// This here should be the major item looked at when checking for compat
	// from anywhere other than the material system	shaders
	DEFCONFIGMETHOD( int, GetDXSupportLevel(), 98 );
	virtual auto GetShaderDLLName() const -> const char* = 0;

	virtual auto ReadPixelsFromFrontBuffer() const -> bool = 0;

	// Are dx dynamic textures preferred?
	virtual auto PreferDynamicTextures() const -> bool = 0;

	DEFCONFIGMETHOD( bool, SupportsHDR(), true );

	virtual auto HasProjectedBumpEnv() const -> bool = 0;
	virtual auto SupportsSpheremapping() const -> bool = 0;
	virtual auto NeedsAAClamp() const -> bool = 0;
	virtual auto NeedsATICentroidHack() const -> bool = 0;

	virtual auto SupportsColorOnSecondStream() const -> bool = 0;
	virtual auto SupportsStaticPlusDynamicLighting() const -> bool = 0;

	// Does our card have a hard time with fillrate
	// relative to other cards w/ the same dx level?
	virtual auto PreferReducedFillrate() const -> bool = 0;

	// This is the max dx support level supported by the card
	virtual auto GetMaxDXSupportLevel() const -> int = 0;

	// Does the card specify fog color in linear space when sRGBWrites are enabled?
	virtual auto SpecifiesFogColorInLinearSpace() const -> bool = 0;

	// Does the card support sRGB reads/writes?
	DEFCONFIGMETHOD( bool, SupportsSRGB(), true );
	DEFCONFIGMETHOD( bool, FakeSRGBWrite(), false );
	DEFCONFIGMETHOD( bool, CanDoSRGBReadFromRTs(), true );

	virtual auto SupportsGLMixedSizeTargets() const -> bool = 0;

	virtual auto IsAAEnabled() const -> bool = 0;// Is antialiasing being used?

	// NOTE: Anything after this was added after shipping HL2.
	virtual auto GetVertexTextureCount() const -> int = 0;
	virtual auto GetMaxVertexTextureDimension() const -> int = 0;

	virtual auto MaxTextureDepth() const -> int = 0;

	virtual auto GetHDRType() const -> HDRType_t = 0;
	virtual auto GetHardwareHDRType() const -> HDRType_t = 0;

	DEFCONFIGMETHOD( bool, SupportsPixelShaders_2_b(), true );
	virtual auto SupportsStreamOffset() const -> bool = 0;

	virtual auto StencilBufferBits() const -> int = 0;
	virtual auto MaxViewports() const -> int = 0;

	virtual auto OverrideStreamOffsetSupport( bool bOverrideEnabled, bool bEnableSupport ) -> void = 0;

	virtual auto GetShadowFilterMode() const -> int = 0;

	virtual auto NeedsShaderSRGBConversion() const -> int = 0;

	DEFCONFIGMETHOD( bool, UsesSRGBCorrectBlending(), true );

	virtual auto SupportsShaderModel_3_0() const -> bool = 0;
	virtual auto HasFastVertexTextures() const -> bool = 0;
	virtual auto MaxHWMorphBatchCount() const -> int = 0;

	// Does the board actually support this?
	DEFCONFIGMETHOD( bool, ActuallySupportsPixelShaders_2_b(), true );

	virtual auto SupportsHDRMode( HDRType_t nHDRMode ) const -> bool = 0;

	virtual auto GetHDREnabled() const -> bool = 0;
	virtual auto SetHDREnabled( bool bEnable ) -> void = 0;

	virtual auto SupportsBorderColor() const -> bool = 0;
	virtual auto SupportsFetch4() const -> bool = 0;

	inline auto ShouldAlwaysUseShaderModel2bShaders() const -> bool { return IsOpenGL(); }
	inline auto PlatformRequiresNonNullPixelShaders() const -> bool { return IsOpenGL(); }
};
