//
// Created by ENDERZOMBI102 on 12/08/2024.
//
#include "bitmap/tgawriter.h"
#include "dbg.h"
#include "filesystem.h"
#include "tgaspec.hpp"
#include "utlbuffer.h"
// This must be the final include in a .cpp or .h file!!!
#include "memdbgon.h"


namespace TGAWriter {
	bool WriteToBuffer( uint8* pImageData, CUtlBuffer& buffer, const int32 width, const int32 height, const ImageFormat srcFormat, const ImageFormat dstFormat ) {
		TGA::Header header;
		int32 x;
		int32 y;

		// FIXME: need to handle conversion here.
		if ( srcFormat != dstFormat ) {
			return false;
		}

		header.idLength = 0;  // comment length
		header.colorMapType = TGA::ColorMapType::None;  // ???

		// Brian?: FIXME: should use BGR, etc, so that we can just fwrite the data.
		// Gary: TGA doesn't support BGR.
		switch ( dstFormat ) {
			case IMAGE_FORMAT_RGB888:
				header.imageType = TGA::ImageType::UncompressedRGB;  // 24/32 bit uncompressed TGA
				header.imageSpec.depth = 24;
				break;
			case IMAGE_FORMAT_RGBA8888:
				header.imageType = TGA::ImageType::UncompressedRGB;  // 24/32 bit uncompressed TGA
				header.imageSpec.depth = 32;
				break;
			case IMAGE_FORMAT_I8:
				header.imageType = TGA::ImageType::UncompressedColorMapped;  // 8 bit uncompressed TGA
				header.imageSpec.depth = 8;
				break;
			default:
				return false;
		}

		header.colorMapSpec.entryIndex = 0;
		header.colorMapSpec.entryLength = 0;
		header.colorMapSpec.size = 0;
		// can I flip this so that I can write the image out directly?
		header.imageSpec.xOrigin = 0;
		header.imageSpec.yOrigin = 0;
		header.imageSpec.width = static_cast<uint16>( width );
		header.imageSpec.height = static_cast<uint16>( height );
		header.imageSpec.imageDesc = { };

		auto pbuf = static_cast<uint8*>( _alloca( width * 4 ) );
		switch ( dstFormat ) {
			case IMAGE_FORMAT_RGB888:
				for ( y = height - 1; y >= 0; y-- ) {
					int32 start = y * width * 3;
					int32 out = 0;
					for ( x = 0; x < width; x++ ) {
						pbuf[out++] = pImageData[start + 2];
						pbuf[out++] = pImageData[start + 1];
						pbuf[out++] = pImageData[start + 0];
						start += 3;
					}
					buffer.Put( pbuf, width * 3 );  // write a line
				}
				break;
			case IMAGE_FORMAT_RGBA8888:
				for ( y = height - 1; y >= 0; y-- ) {
					int32 start = y * width * 4;
					int32 out = 0;
					for ( x = 0; x < width; x++ ) {
						pbuf[out++] = pImageData[start + 2];
						pbuf[out++] = pImageData[start + 1];
						pbuf[out++] = pImageData[start + 0];
						pbuf[out++] = pImageData[start + 3];
						start += 4;
					}
					buffer.Put( pbuf, width * 4 );  // write a line
				}
				break;
			// FIXME: some programs don't understand our I8 files.. probably need to put a linear ramp palette in the file.
			case IMAGE_FORMAT_I8:
				for ( y = height - 1; y >= 0; y-- ) {
					buffer.Put( &pImageData[y * width], width );
				}
				break;
			default:
				return false;
		}
		return true;
	}

	// write out a simple tga file from a memory buffer.
	bool WriteTGAFile( const char* fileName, int32 width, int32 height, ImageFormat srcFormat, uint8 const* srcData, int32 nStride ) {
		CUtlBuffer buffer{};
		// TODO: Eww, bad cast!
		if ( not WriteToBuffer( const_cast<uint8*>( srcData ), buffer, width, height, srcFormat, srcFormat ) ) {
			return false;
		}

		return g_pFullFileSystem->WriteFile( fileName, nullptr, buffer );
	}

	// A pair of routines for writing to files without allocating any memory in the TGA writer
	// Useful for very large files such as posters, which are rendered as sub-rects anyway
	bool WriteDummyFileNoAlloc( const char* fileName, int32 width, int32 height, ImageFormat dstFormat ) {
		AssertUnreachable();
		return {};
	}
	bool WriteRectNoAlloc( uint8* pImageData, const char* fileName, int32 nXOrigin, int32 nYOrigin, int32 width, int32 height, int32 nStride, ImageFormat srcFormat ) {
		AssertUnreachable();
		return {};
	}
}
