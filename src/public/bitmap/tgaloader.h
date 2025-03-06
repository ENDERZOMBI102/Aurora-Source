//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "bitmap/imageformat.h"
#include "tier1/utlmemory.h"


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CUtlBuffer;


namespace TGALoader {
	int32 TGAHeaderSize();

	// Gets info about a TGA file
	bool GetInfo( const char* fileName, int32* width, int32* height, ImageFormat* imageFormat, float* sourceGamma );
	// Figures out TGA information
	bool GetInfo( CUtlBuffer& buf, int32* width, int32* height, ImageFormat* imageFormat, float* sourceGamma );

	// Reads a TGA image from a file
	bool Load( unsigned char* imageData, const char* fileName, int32 width, int32 height, ImageFormat imageFormat, float targetGamma, bool mipmap );
	// Parses the lovely bits previously read from disk
	bool Load( unsigned char* imageData, CUtlBuffer& buf, int32 width, int32 height, ImageFormat imageFormat, float targetGamma, bool mipmap );

	// Reads a TGA, keeps it in RGBA8888
	bool LoadRGBA8888( const char* pFileName, CUtlMemory<unsigned char>& outputData, int32& outWidth, int32& outHeight );
	// Creates a map in linear space
	bool LoadRGBA8888( CUtlBuffer& buf, CUtlMemory<unsigned char>& outputData, int32& outWidth, int32& outHeight );
}
