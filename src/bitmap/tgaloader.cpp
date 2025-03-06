//
// Created by ENDERZOMBI102 on 12/08/2024.
//
#include "bitmap/tgaloader.h"
#include "filesystem.h"
#include "dbg.h"
#include "utlbuffer.h"
#include "tgaspec.hpp"
// This must be the final include in a .cpp or .h file!!!
#include "memdbgon.h"


namespace {
	constexpr int32 TGA_MAX_COLORMAP_SIZE{ 256 * 4 };
	constexpr int32 TGA_MAX_ROW_LENGTH_IN_PIXELS{ IMAGE_MAX_DIM };

	// read a row into an RGBA8888 array.
	using ReadRowFunc_t = void (*)( CUtlBuffer& pBuf, TGA::Header const& pHeader, uint8* pDstMemory );


	// output a RGBA8888 row into the destination format.
	using OutputRowFunc_t = void (*)( CUtlBuffer& pBuf, TGA::Header const& pHeader, uint8* pDstMemory );

	auto OutputRowRGBA8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowABGR8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowRGB888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGR888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowRGB565( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowI8( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowIA88( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowA8( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowRGB888BlueScreen( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGR888BlueScreen( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowARGB8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGRA8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGRX8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGR565( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	auto OutputRowBGRX5551( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads an 8-bit palettized TGA image
	auto ReadRow8BitUncompressedWithColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads an 8-bit greyscale TGA image
	auto ReadRow8BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a 24-bit TGA image
	auto ReadRow24BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a 32-bit TGA image
	auto ReadRow32BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Decompresses a run-length encoded row of bytes
	auto DecompressRow( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a compressed 8-bit palettized TGA image
	auto ReadRow8BitCompressedWithColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a compressed 8-bit greyscale TGA image
	auto ReadRow8BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a compressed 24-bit TGA image
	auto ReadRow24BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;
	// Reads a compressed 32-bit TGA image
	auto ReadRow32BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void;

	// Gets the function used to output a row of data to the given format
	auto GetOutputRowFunc( ImageFormat imageFormat ) -> OutputRowFunc_t;

	// Gets the function used to read a row of data from the provided TGA type
	auto GetReadRowFunc( TGA::Header const& pHeader ) -> ReadRowFunc_t;

	auto InitSourceGammaConversionTable( float32 srcGamma ) -> void;

	auto InitDestGammaConversionTable( float32 dstGamma ) -> void;

	auto ReadColormap( CUtlBuffer& buf, const TGA::Header& header, CUtlBuffer& out ) -> bool;

	auto ReadSourceImage( CUtlBuffer& buf, TGA::Header const& header, CUtlMemory<uint8>& image ) -> bool;

	// FIXME: Horrible horrible code, should be in some "state" struct!!
	uint8 s_ColorMap[TGA_MAX_COLORMAP_SIZE] {};

	// run-length state from row to row for RLE images
	bool s_IsRunLengthPacket{};
	int32 s_PixelsLeftInPacket{};

	uint8 s_SrcGammaTable[256] {};
	uint8 s_DstGammaTable[256] {};
}

namespace TGALoader {
	int32 TGAHeaderSize() {
		return sizeof( TGA::Header );
	}

	bool GetInfo( const char* fileName, int32* width, int32* height, ImageFormat* imageFormat, float* sourceGamma ) {
		const auto handle{ g_pFullFileSystem->Open( fileName, "rb" ) };
		if ( not handle ) {
			return false;
		}

		uint8 header[ sizeof(TGA::Header) ] {};

		// read tga header
		const auto readRes = g_pFullFileSystem->Read( &header, std::size( header ), handle );
		g_pFullFileSystem->Close( handle );
		if ( readRes != std::size( header ) ) {
			return false;
		}

		CUtlBuffer buffer{ header, std::size( header ), CUtlBuffer::READ_ONLY };
		return GetInfo( buffer, width, height, imageFormat, sourceGamma );
	}
	bool GetInfo( CUtlBuffer& buf, int32* width, int32* height, ImageFormat* imageFormat, float* sourceGamma ) {
		// read tga header
		TGA::Header header{};
		if ( buf.GetUpTo( &header, sizeof(header) ) != sizeof(header) ) {
			return false;
		}

		// the data!
		switch ( header.imageType ) {
			case 1:  // 8 bit uncompressed TGA image
			case 3:  // 8 bit monochrome uncompressed TGA image
			case 9:  // 8 bit compressed TGA image
				*imageFormat = IMAGE_FORMAT_I8;
			break;
			case 2:  // 24/32 bit uncompressed TGA image
			case 10: // 24/32 bit compressed TGA image
				if ( header.imageSpec.depth == 32 ) {
					*imageFormat = IMAGE_FORMAT_ABGR8888;
				} else if ( header.imageSpec.depth == 24 ) {
					*imageFormat = IMAGE_FORMAT_BGR888;
				} else {
					return false;
				}
			break;
			default:
				return false;
		}
		*width = header.imageSpec.width;
		*height = header.imageSpec.height;
		*sourceGamma = ARTWORK_GAMMA;

		return true;
	}

	bool Load( unsigned char* imageData, const char* fileName, const int32 width, const int32 height, const ImageFormat imageFormat, const float targetGamma, const bool mipmap ) {
		Assert( imageData and fileName );

		const auto handle{ g_pFullFileSystem->Open( fileName, "rb" ) };
		if ( not handle ) {
			return false;
		}

		// create binary buffer
		CUtlBuffer buffer{};
		buffer.SetBufferType( false, false );

		// read the file
		if ( not g_pFullFileSystem->ReadToBuffer( handle, buffer ) ) {
			g_pFullFileSystem->Close( handle );
			return false;
		}

		// actually load the image
		return Load( imageData, buffer, width, height, imageFormat, targetGamma, mipmap );
	}
	bool Load( unsigned char* imageData, CUtlBuffer& buf, const int32 width, const int32 height, const ImageFormat imageFormat, const float targetGamma, const bool mipmap ) {
		// read the header
		TGA::Header header{};
		if ( buf.GetUpTo( &header, sizeof(header) ) != sizeof(header) ) {
			return false;
		}

		// skip TARGA image comment
		if ( header.idLength != 0 ) {
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, header.idLength );
		}

		// read the color map for palettized images
		CUtlBuffer colormapBuffer{};
		if ( header.colorMapSpec.entryLength != 0 and not ReadColormap( buf, header, colormapBuffer ) ) {
			return false;
		}

		// Stores the RGBA8888 temp version of the image which we'll use to do mipmapping...
		CUtlMemory<uint8> tmpImage;
		if ( not ReadSourceImage( buf, header, tmpImage ) ) {
			return false;
		}

		// Erg... what if header.imageSpec.width * header.height > width * height?
		// Then don't do anything, this is an error condition...
		if ( width * height < header.imageSpec.width * header.imageSpec.height ) {
			return false;
		}

		// Now that we've got the source image, generate the mip-map levels
		ImageLoader::GenerateMipmapLevels(
			tmpImage.Base(), imageData, header.imageSpec.width, header.imageSpec.height,
			ARTWORK_GAMMA, imageFormat, targetGamma, mipmap ? 0 : 1
		);

		return true;
	}

	bool LoadRGBA8888( const char* pFileName, CUtlMemory<unsigned char>& outputData, int32& outWidth, int32& outHeight ) {
		Assert( pFileName );

		const auto handle{ g_pFullFileSystem->Open( pFileName, "rb" ) };
		if ( not handle ) {
			return false;
		}

		// create binary buffer
		CUtlBuffer buffer{};
		buffer.SetBufferType( false, false );

		// read the file
		if ( not g_pFullFileSystem->ReadToBuffer( handle, buffer ) ) {
			g_pFullFileSystem->Close( handle );
			return false;
		}

		// actually load the image
		return LoadRGBA8888( buffer, outputData, outWidth, outHeight );
	}
	bool LoadRGBA8888( CUtlBuffer& buf, CUtlMemory<unsigned char>& outputData, int32& outWidth, int32& outHeight ) {
		// read the header
		TGA::Header header{};
		if ( buf.GetUpTo( &header, sizeof(header) ) != sizeof(header) ) {
			return false;
		}

		// skip TARGA image comment
		if ( header.idLength != 0 ) {
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, header.idLength );
		}

		// read the color map for palettized images
		CUtlBuffer colormapBuffer{};
		if ( header.colorMapSpec.entryLength != 0 and not ReadColormap( buf, header, colormapBuffer ) ) {
			return false;
		}

		// Stores the RGBA8888 temp version of the image which we'll use to do mipmapping...
		const int memSize{ ImageLoader::GetMemRequired( header.imageSpec.width, header.imageSpec.height, ARTWORK_GAMMA, IMAGE_FORMAT_RGBA8888, false ) };

		outputData.EnsureCapacity( memSize );
		if ( not ReadSourceImage( buf, header, outputData ) ) {
			return false;
		}

		outWidth = header.imageSpec.width;
		outHeight = header.imageSpec.height;
		return true;
	}
}

namespace {
	#pragma region "OutputRow funcs"
	auto OutputRowRGBA8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[0];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[2];
			pDst[3] = pSrc[3];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowABGR8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[3] = pSrc[0];
			pDst[2] = pSrc[1];
			pDst[1] = pSrc[2];
			pDst[0] = pSrc[3];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowRGB888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 3 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[0];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[2];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGR888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 3 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[2] = pSrc[0];
			pDst[1] = pSrc[1];
			pDst[0] = pSrc[2];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowRGB565( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		Assert( 0 );
	}

	auto OutputRowI8( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, ++pDst ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();

			if ( ( pSrc[0] == pSrc[1] ) && ( pSrc[1] == pSrc[2] ) ) {
				pDst[0] = pSrc[0];
			} else {
				pDst[0] = (unsigned char) ( 0.299f * pSrc[0] + 0.587f * pSrc[1] + 0.114f * pSrc[2] );
			}

			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowIA88( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 2 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();

			if ( ( pSrc[0] == pSrc[1] ) && ( pSrc[1] == pSrc[2] ) ) {
				pDst[0] = pSrc[0];
			} else {
				pDst[0] = (unsigned char) ( 0.299f * pSrc[0] + 0.587f * pSrc[1] + 0.114f * pSrc[2] );
			}
			pDst[1] = pSrc[3];

			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowA8( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, ++pDst ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[3];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowRGB888BlueScreen( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 3 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = (unsigned char) ( ( (int) pSrc[0] * (int) pSrc[3] ) >> 8 );
			pDst[1] = (unsigned char) ( ( (int) pSrc[1] * (int) pSrc[3] ) >> 8 );
			pDst[2] = ( ( ( ( (int) pSrc[2] * (int) pSrc[3] ) ) >> 8 ) + ( 255 - pSrc[3] ) );
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGR888BlueScreen( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 3 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[2] = (unsigned char) ( ( (int) pSrc[0] * (int) pSrc[3] ) >> 8 );
			pDst[1] = (unsigned char) ( ( (int) pSrc[1] * (int) pSrc[3] ) >> 8 );
			pDst[0] = (unsigned char) ( ( ( ( (int) pSrc[2] * (int) pSrc[3] ) ) >> 8 ) + ( 255 - pSrc[3] ) );
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowARGB8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[3];
			pDst[1] = pSrc[0];
			pDst[2] = pSrc[1];
			pDst[3] = pSrc[2];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGRA8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[2];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[0];
			pDst[3] = pSrc[3];
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGRX8888( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			pDst[0] = pSrc[2];
			pDst[1] = pSrc[1];
			pDst[2] = pSrc[0];
			pDst[3] = 255;
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGR565( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 2 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			unsigned short rgba = ( pSrc[2] & 0x1F ) | ( ( pSrc[1] & 0x3F ) << 5 ) |
								  ( ( pSrc[0] & 0x1F ) << 11 );

			pDst[0] = rgba & 0xFF;
			pDst[1] = rgba >> 8;
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}

	auto OutputRowBGRX5551( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 2 ) {
			unsigned char* pSrc = (unsigned char*) buf.PeekGet();
			unsigned short rgba = ( pSrc[2] & 0x1F ) | ( ( pSrc[1] & 0x1F ) << 5 ) |
								  ( ( pSrc[0] & 0x1F ) << 10 ) | 0x8000;

			pDst[0] = rgba & 0xFF;
			pDst[1] = rgba >> 8;
			buf.SeekGet( CUtlBuffer::SEEK_CURRENT, 4 );
		}
	}
	#pragma endregion

	#pragma region "ReadRow funcs"
	auto ReadRow8BitUncompressedWithColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		int i;
		unsigned char* colormapEntry;

		switch ( header.colorMapSpec.size ) {
			case 8:
				for ( i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
					int pal = buf.GetUnsignedChar();

					colormapEntry = &s_ColorMap[pal];
					pDst[0] = colormapEntry[0];
					pDst[1] = colormapEntry[0];
					pDst[2] = colormapEntry[0];
					pDst[3] = 255;
				}
				break;

			case 24:
				for ( i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
					int pal = buf.GetUnsignedChar();

					colormapEntry = &s_ColorMap[pal * 3];
					pDst[0] = colormapEntry[2];
					pDst[1] = colormapEntry[1];
					pDst[2] = colormapEntry[0];
					pDst[3] = 255;
				}
				break;

			case 32:
				for ( i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
					int pal = buf.GetUnsignedChar();

					colormapEntry = &s_ColorMap[pal * 4];
					pDst[0] = colormapEntry[3];
					pDst[1] = colormapEntry[2];
					pDst[2] = colormapEntry[1];
					pDst[3] = colormapEntry[0];
				}
				break;

			default:
				Assert( 0 );
				break;
		}
	}

	auto ReadRow8BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			pDst[0] = pDst[1] = pDst[2] = buf.GetUnsignedChar();
			pDst[3] = 255;
		}
	}

	auto ReadRow24BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			pDst[2] = buf.GetUnsignedChar();
			pDst[1] = buf.GetUnsignedChar();
			pDst[0] = buf.GetUnsignedChar();
			pDst[3] = 255;
		}
	}

	auto ReadRow32BitUncompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		for ( int i = 0; i < header.imageSpec.width; ++i, pDst += 4 ) {
			pDst[2] = buf.GetUnsignedChar();
			pDst[1] = buf.GetUnsignedChar();
			pDst[0] = buf.GetUnsignedChar();
			pDst[3] = buf.GetUnsignedChar();
		}
	}

	auto DecompressRow( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		int bytesPerPixel = header.imageSpec.depth >> 3;
		int pixelsLeftInRow = header.imageSpec.width;
		int numPixelsToProcess;

#ifdef _DEBUG
		unsigned char* pLast = pDst + header.imageSpec.width * bytesPerPixel;
#endif

		unsigned char repeat[4];
		do {
			if ( !s_PixelsLeftInPacket ) {
				// start a new packet.
				unsigned char packetHeader = buf.GetUnsignedChar();
				s_PixelsLeftInPacket = 1 + ( packetHeader & 0x7f );
				if ( packetHeader & 0x80 ) {
					s_IsRunLengthPacket = true;

					// Read what I'm supposed to repeat
					for ( int i = 0; i < bytesPerPixel; ++i ) {
						repeat[i] = buf.GetUnsignedChar();
					}
				} else {
					s_IsRunLengthPacket = false;
				}
			}

			// already in the middle of a packet of data.
			numPixelsToProcess = s_PixelsLeftInPacket;
			if ( numPixelsToProcess > pixelsLeftInRow ) {
				numPixelsToProcess = pixelsLeftInRow;
			}
			if ( s_IsRunLengthPacket ) {
				for ( int i = numPixelsToProcess; --i >= 0; pDst += bytesPerPixel ) {
					for ( int j = 0; j < bytesPerPixel; ++j ) {
						pDst[j] = repeat[j];
					}
				}
			} else {
				buf.Get( pDst, numPixelsToProcess * bytesPerPixel );
				pDst += numPixelsToProcess * bytesPerPixel;
			}

			s_PixelsLeftInPacket -= numPixelsToProcess;
			pixelsLeftInRow -= numPixelsToProcess;

		} while ( pixelsLeftInRow );

		Assert( pDst == pLast );
	}

	auto ReadRow8BitCompressedWithColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		unsigned char rowI_8[TGA_MAX_ROW_LENGTH_IN_PIXELS];

		DecompressRow( buf, header, rowI_8 );

		CUtlBuffer uncompressedBuf( rowI_8, TGA_MAX_ROW_LENGTH_IN_PIXELS );
		ReadRow8BitUncompressedWithColormap( uncompressedBuf, header, pDst );
	}

	auto ReadRow8BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		unsigned char rowI_8[TGA_MAX_ROW_LENGTH_IN_PIXELS];

		DecompressRow( buf, header, rowI_8 );

		CUtlBuffer uncompressedBuf( rowI_8, TGA_MAX_ROW_LENGTH_IN_PIXELS );
		ReadRow8BitUncompressedWithoutColormap( uncompressedBuf, header, pDst );
	}

	auto ReadRow24BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		unsigned char rowBGR_888[TGA_MAX_ROW_LENGTH_IN_PIXELS * 3];

		DecompressRow( buf, header, rowBGR_888 );

		CUtlBuffer uncompressedBuf( rowBGR_888, TGA_MAX_ROW_LENGTH_IN_PIXELS * 3 );
		ReadRow24BitUncompressedWithoutColormap( uncompressedBuf, header, pDst );
	}

	auto ReadRow32BitCompressedWithoutColormap( CUtlBuffer& buf, TGA::Header const& header, unsigned char* pDst ) -> void {
		unsigned char rowBGRA_8888[TGA_MAX_ROW_LENGTH_IN_PIXELS << 2];

		DecompressRow( buf, header, rowBGRA_8888 );

		CUtlBuffer uncompressedBuf( rowBGRA_8888, TGA_MAX_ROW_LENGTH_IN_PIXELS << 2 );
		ReadRow32BitUncompressedWithoutColormap( uncompressedBuf, header, pDst );
	}
	#pragma endregion

	auto GetOutputRowFunc( const ImageFormat imageFormat ) -> OutputRowFunc_t {
		switch ( imageFormat ) {
			case IMAGE_FORMAT_RGBA8888:
				return &OutputRowRGBA8888;
			case IMAGE_FORMAT_ABGR8888:
				return &OutputRowABGR8888;
			case IMAGE_FORMAT_RGB888:
				return &OutputRowRGB888;
			case IMAGE_FORMAT_BGR888:
				return &OutputRowBGR888;
			case IMAGE_FORMAT_RGB565:
				return &OutputRowRGB565;
			case IMAGE_FORMAT_I8:
				return &OutputRowI8;
			case IMAGE_FORMAT_IA88:
				return &OutputRowIA88;
			case IMAGE_FORMAT_A8:
				return &OutputRowA8;
			case IMAGE_FORMAT_RGB888_BLUESCREEN:
				return &OutputRowRGB888BlueScreen;
			case IMAGE_FORMAT_BGR888_BLUESCREEN:
				return &OutputRowBGR888BlueScreen;
			case IMAGE_FORMAT_ARGB8888:
				return &OutputRowARGB8888;
			case IMAGE_FORMAT_BGRA8888:
				return &OutputRowBGRA8888;
			case IMAGE_FORMAT_BGRX8888:
				return &OutputRowBGRX8888;
			case IMAGE_FORMAT_BGR565:
				return &OutputRowBGR565;
			case IMAGE_FORMAT_BGRX5551:
				return &OutputRowBGRX5551;
			default:
				return nullptr;
		}
	}

	auto GetReadRowFunc( TGA::Header const& pHeader ) -> ReadRowFunc_t {
		switch ( pHeader.imageType ) {
			case 1: // 8 bit uncompressed TGA image
			case 3: {  // 8 bit monochrome uncompressed TGA image
				if ( pHeader.colorMapSpec.entryLength ) {
					return &ReadRow8BitUncompressedWithColormap;
				}
				return &ReadRow8BitUncompressedWithoutColormap;
			}
			case 9: {  // 8 bit compressed TGA image
				if ( pHeader.colorMapSpec.entryLength ) {
					return &ReadRow8BitCompressedWithColormap;
				}
				return &ReadRow8BitCompressedWithoutColormap;
			}
			case 2: {  // 24/32 bit uncompressed TGA image
				if ( pHeader.colorMapSpec.entryLength ) {
					// Error( "colormaps not support with 24/32 bit TGAs." );
					return nullptr;
				}
				switch ( pHeader.imageSpec.depth ) {
					case 24:
						return &ReadRow24BitUncompressedWithoutColormap;
					case 32:
						return &ReadRow32BitUncompressedWithoutColormap;
					default:
						//Error( "unsupported tga colordepth: %d", TGA::Header.pixel_size" );
							return nullptr;
				}
			}
			case 10: {  // 24/32 bit compressed TGA image
				if ( pHeader.colorMapSpec.entryLength ) {
					// Error( "colormaps not support with 24/32 bit TGAs." );
					return nullptr;
				}
				switch ( pHeader.imageSpec.depth ) {
					case 24:
						return &ReadRow24BitCompressedWithoutColormap;
					case 32:
						return &ReadRow32BitCompressedWithoutColormap;
					default:
						//Error( "unsupported tga colordepth: %d", TGA::Header.pixel_size" );
							return nullptr;
				}
			}
			default:
				// Error( "unsupported tga pixel format" );
					return nullptr;
		}
	}

	auto InitSourceGammaConversionTable( const float srcGamma ) -> void {
		static float lastSrcGamma = -1;
		if ( lastSrcGamma == srcGamma )
			return;

		lastSrcGamma = srcGamma;
		ImageLoader::ConstructGammaTable( s_SrcGammaTable, srcGamma, 1.0f );
	}

	auto InitDestGammaConversionTable( const float dstGamma ) -> void {
		static float lastDstGamma = -1;
		if ( lastDstGamma == dstGamma )
			return;

		lastDstGamma = dstGamma;
		ImageLoader::ConstructGammaTable( s_DstGammaTable, 1.0f, dstGamma );
	}

	auto ReadColormap( CUtlBuffer& buf, const TGA::Header& header, CUtlBuffer& out ) -> bool {
		const int32 byteCount{ header.colorMapSpec.entryLength * (header.colorMapSpec.size >> 3) };

		if ( byteCount > TGA_MAX_COLORMAP_SIZE ) {
			return false;
		}

		out.EnsureCapacity( byteCount );
		buf.Get( out.Base(), byteCount );

		return true;
	}

	auto ReadSourceImage( CUtlBuffer& buf, TGA::Header const& header, CUtlMemory<uint8>& image ) -> bool {
		// Figure out our reading and writing
		const ReadRowFunc_t ReadRowFunc{ GetReadRowFunc( header ) };
		if ( not ReadRowFunc ) {
			return false;
		}

		// Init RLE vars
		s_PixelsLeftInPacket = 0;

		// Only allocate the memory once
		const int32 memRequired{ ImageLoader::GetMemRequired( header.imageSpec.width, header.imageSpec.height, header.imageSpec.depth, IMAGE_FORMAT_RGBA8888, false ) };
		image.EnsureCapacity( memRequired );

		// read each row and process it. Note the image is upside-down from the way we want it.
		const int32 formatSize{ ImageLoader::SizeInBytes( IMAGE_FORMAT_RGBA8888 ) };
		if ( header.imageSpec.imageDesc.orderTopToBottom ) {
			// image is already how we want it, no need to flip
			for ( int row = 0; row < header.imageSpec.height; row += 1 ) {
				uint8* dstBits{ image.Base() + row * header.imageSpec.width * formatSize };
				ReadRowFunc( buf, header, dstBits );
			}
		} else {
			// flip the image vertically
			for ( int row = header.imageSpec.height; --row >= 0; ) {
				uint8* dstBits{ image.Base() + row * header.imageSpec.width * formatSize };
				ReadRowFunc( buf, header, dstBits );
			}
		}

		return true;
	}
}

