//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $Header: $
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "Color.h"
#include "bitmap/imageformat.h"
#include "dbg.h"


class CUtlBuffer;

//-----------------------------------------------------------------------------
// A Bitmap
//-----------------------------------------------------------------------------
struct Bitmap_t {
	Bitmap_t() { Reset(); } // NOLINT(*-pro-type-member-init)
	~Bitmap_t() { Clear(); }

	//
	// Accessors
	//
	[[nodiscard]]
	inline int32 Width() const { return m_nWidth; }
	[[nodiscard]]
	inline int32 Height() const { return m_nHeight; }
	[[nodiscard]]
	inline ImageFormat Format() const { return m_ImageFormat; }
	[[nodiscard]]
	inline unsigned char* GetBits() const { return m_pBits; }
	[[nodiscard]]
	inline int32 Stride() const { return m_nStride; }
	[[nodiscard]]
	inline bool GetOwnsBuffer() const { return m_bOwnsBuffer; }

	/// Allocate the buffer.  Discards existing data, freeing it if we own it
	void Init( int32 nWidth, int32 nHeight, ImageFormat imageFormat, int32 nStride = 0 );

	/// Set the bitmap to the specified buffer.  Any existing data is discarded/freed
	/// as appropriate.
	void SetBuffer( int32 nWidth, int32 nHeight, ImageFormat imageFormat, unsigned char* pBits, bool bAssumeOwnership, int32 nStride = 0 );

	/// Sets / releases ownershp of the buffer.  This does not otherwise alter the
	/// state of the bitmap.
	void SetOwnsBuffer( bool bOwnsBuffer ) {
		Assert( m_pBits );
		m_bOwnsBuffer = bOwnsBuffer;
	}

	/// Free up all memory and reset to default state
	void Clear();

	/// Return true if we have a valid size and buffer
	[[nodiscard]]
	bool IsValid() const;

	/// Get pointer to raw pixel data.
	uint8* GetPixel( int32 x, int32 y );
	[[nodiscard]]
	const uint8* GetPixel( int32 x, int32 y ) const;

	/// Get pixel value at specified coordinates
	[[nodiscard]]
	Color GetColor( int32 x, int32 y ) const;

	/// Set pixel value at specified coordinates
	void SetColor( int32 x, int32 y, Color c );

	/// Set this bitmap to be a logical copy of the specified
	/// bitmap.  No memory is allocated or copied, just copying
	/// some pointers.  We can also optionally transfer ownership
	/// of the buffer.
	void MakeLogicalCopyOf( Bitmap_t& src, bool bTransferBufferOwnership = false );

	/// Set this bitmap to be a cropped rectangle from the given bitmap.
	/// The source pointer can be NULL or point32 to this, which means to do
	/// the crop in place.
	void Crop( int32 x0, int32 y0, int32 nWidth, int32 nHeight, const Bitmap_t* pImgSource = nullptr );

	/// Blit a rectangle of pixel data into this image.
	void SetPixelData( const Bitmap_t& src, int32 nSrcX1, int32 nSrcY1, int32 nCopySizeX, int32 nCopySizeY, int32 nDestX1, int32 nDestY1 );

	/// Blit the entire source image into this image, at the specified offset.
	/// the rectangle is clipped if necessary
	void SetPixelData( const Bitmap_t& src, int32 nDestX1 = 0, int32 nDestY1 = 0 );

private:
	void Reset();

	/// Dimensions
	int32 m_nWidth{};
	int32 m_nHeight{};

	/// Size, in bytes, of one pixel
	int32 m_nPixelSize{};

	/// Image row stride, in bytes
	int32 m_nStride{};

	// Do we own this buffer?
	bool m_bOwnsBuffer{ false };

	/// Pixel format
	ImageFormat m_ImageFormat{ IMAGE_FORMAT_UNKNOWN };

	/// Bitmap data.  Must be allocated with malloc/free.  Don't use new/delete
	unsigned char* m_pBits{ nullptr };
};

inline void Bitmap_t::Reset() {
	m_nWidth = 0;
	m_nHeight = 0;
	m_nPixelSize = 0;
	m_nStride = 0;
	m_bOwnsBuffer = false;
	m_ImageFormat = IMAGE_FORMAT_UNKNOWN;
	m_pBits = nullptr;
}

inline unsigned char* Bitmap_t::GetPixel( const int32 x, const int32 y ) {
	if ( not m_pBits ) {
		return nullptr;
	}

	return m_pBits + y * m_nStride + x * m_nPixelSize;
}

inline const unsigned char* Bitmap_t::GetPixel( const int32 x, const int32 y ) const {
	if ( not m_pBits ) {
		return nullptr;
	}

	return m_pBits + y * m_nStride + x * m_nPixelSize;
}
