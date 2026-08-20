//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "bitmap/imageformat.h"
#include "tier1/interface.h"

class CUtlBuffer;


namespace TGAWriter {
	bool WriteToBuffer( uint8* pImageData, CUtlBuffer& buffer, int32 width, int32 height, ImageFormat srcFormat, ImageFormat dstFormat );

	// write out a simple tga file from a memory buffer.
	bool WriteTGAFile( const char* fileName, int32 width, int32 height, ImageFormat srcFormat, uint8 const* srcData, int32 nStride );

	// A pair of routines for writing to files without allocating any memory in the TGA writer
	// Useful for very large files such as posters, which are rendered as sub-rects anyway
	bool WriteDummyFileNoAlloc( const char* fileName, int32 width, int32 height, ImageFormat dstFormat );
	bool WriteRectNoAlloc( unsigned char* pImageData, const char* fileName, int32 nXOrigin, int32 nYOrigin, int32 width, int32 height, int32 nStride, ImageFormat srcFormat );
}
