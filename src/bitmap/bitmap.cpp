//
// Created by ENDERZOMBI102 on 12/08/2024.
//
#include "bitmap/bitmap.h"
#include "filesystem.h"
#include "dbg.h"
// This must be the final include in a .cpp or .h file!!!
#include "memdbgon.h"


void Bitmap_t::Init( const int32 nWidth, const int32 nHeight, const ImageFormat imageFormat, const int32 nStride ) {
	if ( m_bOwnsBuffer ) {
		free( m_pBits );
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_ImageFormat = imageFormat;
	m_pBits = nullptr;
	m_bOwnsBuffer = false;
	m_nStride = nStride;
	m_nPixelSize = ImageLoader::SizeInBytes( imageFormat );
}

void Bitmap_t::SetBuffer( const int32 nWidth, const int32 nHeight, const ImageFormat imageFormat, unsigned char* pBits, const bool bAssumeOwnership, const int32 nStride ) {
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_ImageFormat = imageFormat;
	m_pBits = pBits;
	m_bOwnsBuffer = bAssumeOwnership;
	m_nStride = nStride;
	m_nPixelSize = ImageLoader::SizeInBytes( imageFormat );
}

void Bitmap_t::Clear() {
	AssertFatalMsg( m_bOwnsBuffer, "Only owned buffers can be cleared" );

	// "Must be allocated with malloc/free.  Don't use new/delete"
	free( m_pBits );
	Reset();
}

bool Bitmap_t::IsValid() const {
	return m_nWidth > 0 and m_nHeight > 0 and m_pBits != nullptr and m_ImageFormat != IMAGE_FORMAT_UNKNOWN;
}

Color Bitmap_t::GetColor( int32 x, int32 y ) const {
	const auto pix{ m_pBits + ( y * m_nStride ) + x * m_nPixelSize };

	AssertUnreachable();
	return {};
}

void Bitmap_t::SetColor( int32 x, int32 y, Color c ) {
	auto pix{ m_pBits + ( y * m_nStride ) + x * m_nPixelSize };

	AssertUnreachable();
}

void Bitmap_t::MakeLogicalCopyOf( Bitmap_t& src, const bool bTransferBufferOwnership ) {
	m_nWidth = src.m_nWidth;
	m_nHeight = src.m_nHeight;
	m_nPixelSize = src.m_nPixelSize;
	m_nStride = src.m_nStride;
	if ( bTransferBufferOwnership ) {
		m_bOwnsBuffer = src.m_bOwnsBuffer;
		src.m_bOwnsBuffer = false;
	} else {
		m_bOwnsBuffer = false;
	}
	m_ImageFormat = src.m_ImageFormat;
	m_pBits = src.m_pBits;
}

void Bitmap_t::Crop( int32 x0, int32 y0, int32 nWidth, int32 nHeight, const Bitmap_t* pImgSource ) {
	AssertUnreachable();
}

void Bitmap_t::SetPixelData( const Bitmap_t& src, int32 nSrcX1, int32 nSrcY1, int32 nCopySizeX, int32 nCopySizeY, int32 nDestX1, int32 nDestY1 ) {
	AssertUnreachable();
}

void Bitmap_t::SetPixelData( const Bitmap_t& src, int32 nDestX1, int32 nDestY1 ) {
	AssertUnreachable();
}
