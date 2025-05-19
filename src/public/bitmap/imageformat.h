//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//===========================================================================//
#pragma once
#include <cstdio>
#include "platform.h"

enum NormalDecodeMode_t {
	NORMAL_DECODE_NONE = 0,
	NORMAL_DECODE_ATI2N = 1,
	NORMAL_DECODE_ATI2N_ALPHA = 2
};


// don't bitch that inline functions aren't used!!!!
#if _MSC_VER
	#pragma warning( push )
	#pragma warning( disable : 4514 )
#endif
//-----------------------------------------------------------------------------
// The various image format types
//-----------------------------------------------------------------------------
enum ImageFormat {
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,  // Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,   //
	IMAGE_FORMAT_NV_DST24,   //
	IMAGE_FORMAT_NV_INTZ,    // Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,    // formats for shadow depth mapping
	IMAGE_FORMAT_ATI_DST16,  //
	IMAGE_FORMAT_ATI_DST24,  //
	IMAGE_FORMAT_NV_NULL,    // Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,  // One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,  // Two-surface ATI1N format

	IMAGE_FORMAT_DXT1_RUNTIME,
	IMAGE_FORMAT_DXT5_RUNTIME,

	NUM_IMAGE_FORMATS
};

#if IsPosix() || defined( DX_TO_GL_ABSTRACTION )
	typedef enum _D3DFORMAT {
	    D3DFMT_UNKNOWN              =  0,

	    D3DFMT_R8G8B8               = 20,
	    D3DFMT_A8R8G8B8             = 21,
	    D3DFMT_X8R8G8B8             = 22,
	    D3DFMT_R5G6B5               = 23,
	    D3DFMT_X1R5G5B5             = 24,
	    D3DFMT_A1R5G5B5             = 25,
	    D3DFMT_A4R4G4B4             = 26,
	    D3DFMT_R3G3B2               = 27,
	    D3DFMT_A8                   = 28,
	    D3DFMT_A8R3G3B2             = 29,
	    D3DFMT_X4R4G4B4             = 30,
	    D3DFMT_A2B10G10R10          = 31,
	    D3DFMT_A8B8G8R8             = 32,
	    D3DFMT_X8B8G8R8             = 33,
	    D3DFMT_G16R16               = 34,
	    D3DFMT_A2R10G10B10          = 35,
	    D3DFMT_A16B16G16R16         = 36,

	    D3DFMT_A8P8                 = 40,
	    D3DFMT_P8                   = 41,

	    D3DFMT_L8                   = 50,
	    D3DFMT_A8L8                 = 51,
	    D3DFMT_A4L4                 = 52,

	    D3DFMT_V8U8                 = 60,
	    D3DFMT_L6V5U5               = 61,
	    D3DFMT_X8L8V8U8             = 62,
	    D3DFMT_Q8W8V8U8             = 63,
	    D3DFMT_V16U16               = 64,
	    D3DFMT_A2W10V10U10          = 67,

	    D3DFMT_UYVY                 = MAKEID_REV('U', 'Y', 'V', 'Y'),
	    D3DFMT_R8G8_B8G8            = MAKEID_REV('R', 'G', 'B', 'G'),
	    D3DFMT_YUY2                 = MAKEID_REV('Y', 'U', 'Y', '2'),
	    D3DFMT_G8R8_G8B8            = MAKEID_REV('G', 'R', 'G', 'B'),
	    D3DFMT_DXT1                 = MAKEID_REV('D', 'X', 'T', '1'),
	    D3DFMT_DXT2                 = MAKEID_REV('D', 'X', 'T', '2'),
	    D3DFMT_DXT3                 = MAKEID_REV('D', 'X', 'T', '3'),
	    D3DFMT_DXT4                 = MAKEID_REV('D', 'X', 'T', '4'),
	    D3DFMT_DXT5                 = MAKEID_REV('D', 'X', 'T', '5'),

	    D3DFMT_D16_LOCKABLE         = 70,
	    D3DFMT_D32                  = 71,
	    D3DFMT_D15S1                = 73,
	    D3DFMT_D24S8                = 75,
	    D3DFMT_D24X8                = 77,
	    D3DFMT_D24X4S4              = 79,
	    D3DFMT_D16                  = 80,

	    D3DFMT_D32F_LOCKABLE        = 82,
	    D3DFMT_D24FS8               = 83,

		/* D3D9Ex only -- */
		#if !defined(D3D_DISABLE_9EX)
		    /* Z-Stencil formats valid for CPU access */
		    D3DFMT_D32_LOCKABLE         = 84,
		    D3DFMT_S8_LOCKABLE          = 85,
		#endif // !D3D_DISABLE_9EX
		/* -- D3D9Ex only */


	    D3DFMT_L16                  = 81,

	    D3DFMT_VERTEXDATA           =100,
	    D3DFMT_INDEX16              =101,
	    D3DFMT_INDEX32              =102,

	    D3DFMT_Q16W16V16U16         =110,

	    D3DFMT_MULTI2_ARGB8         = MAKEID_REV('M','E','T','1'),

	    // Floating point surface formats

	    // s10e5 formats (16-bits per channel)
	    D3DFMT_R16F                 = 111,
	    D3DFMT_G16R16F              = 112,
	    D3DFMT_A16B16G16R16F        = 113,

	    // IEEE s23e8 formats (32-bits per channel)
	    D3DFMT_R32F                 = 114,
	    D3DFMT_G32R32F              = 115,
	    D3DFMT_A32B32G32R32F        = 116,

	    D3DFMT_CxV8U8               = 117,

	/* D3D9Ex only -- */
	#if !defined(D3D_DISABLE_9EX)

	    // Monochrome 1 bit per pixel format
	    D3DFMT_A1                   = 118,

	    // 2.8 biased fixed point
	    D3DFMT_A2B10G10R10_XR_BIAS  = 119,


	    // Binary format indicating that the data has no inherent type
	    D3DFMT_BINARYBUFFER         = 199,

	#endif // !D3D_DISABLE_9EX
	/* -- D3D9Ex only */

	    //////////
	    // TOGL DEFINITIONS:
	    /////////

		// NV shadow depth tex
		D3DFMT_NV_INTZ		= MAKEID_REV('I','N','T','Z'),
		D3DFMT_NV_RAWZ		= MAKEID_REV('R','A','W','Z'),

		// NV null tex
		D3DFMT_NV_NULL		= MAKEID_REV('N','U','L','L'),

		// ATI shadow depth tex
		D3DFMT_ATI_D16		= MAKEID_REV('D','F','1','6'),
		D3DFMT_ATI_D24S8	= MAKEID_REV('D','F','2','4'),

		// ATI 1N and 2N compressed tex
		D3DFMT_ATI_2N		= MAKEID_REV('A', 'T', 'I', '2'),
		D3DFMT_ATI_1N		= MAKEID_REV('A', 'T', 'I', '1'),

	    D3DFMT_FORCE_DWORD  = 0x7fffffff
	} D3DFORMAT;
#elif IsWindows()
	// Forward declaration
	typedef enum _D3DFORMAT D3DFORMAT;
#endif

//-----------------------------------------------------------------------------
// Color structures
//-----------------------------------------------------------------------------

struct BGRA8888_t {
	uint8 b;// change the order of names to change the
	uint8 g;//  order of the output ARGB or BGRA, etc...
	uint8 r;//  Last one is MSB, 1st is LSB.
	uint8 a;

	inline BGRA8888_t& operator=( const BGRA8888_t& in ) {
		*reinterpret_cast<uint32*>( this ) = *reinterpret_cast<const uint32*>( &in );
		return *this;
	}
};

struct RGBA8888_t {
	uint8 r;// change the order of names to change the
	uint8 g;//  order of the output ARGB or BGRA, etc...
	uint8 b;//  Last one is MSB, 1st is LSB.
	uint8 a;

	inline RGBA8888_t& operator=( const BGRA8888_t& in ) {
		r = in.r;
		g = in.g;
		b = in.b;
		a = in.a;
		return *this;
	}
};

struct RGB888_t {
	uint8 r;
	uint8 g;
	uint8 b;

	inline RGB888_t& operator=( const BGRA8888_t& in ) {
		r = in.r;
		g = in.g;
		b = in.b;
		return *this;
	}
	inline bool operator==( const RGB888_t& in ) const {
		return ( r == in.r ) && ( g == in.g ) && ( b == in.b );
	}
	inline bool operator!=( const RGB888_t& in ) const {
		return ( r != in.r ) || ( g != in.g ) || ( b != in.b );
	}
};

struct BGR888_t {
	uint8 b;
	uint8 g;
	uint8 r;

	inline BGR888_t& operator=( const BGRA8888_t& in ) {
		r = in.r;
		g = in.g;
		b = in.b;
		return *this;
	}
};

struct BGR565_t {
	uint16 b : 5;// order of names changes
	uint16 g : 6;//  byte order of output to 32 bit
	uint16 r : 5;

	inline BGR565_t& operator=( const BGRA8888_t& in ) {
		r = in.r >> 3;
		g = in.g >> 2;
		b = in.b >> 3;
		return *this;
	}
	inline BGR565_t& Set( int32 red, int32 green, int32 blue ) {
		r = red >> 3;
		g = green >> 2;
		b = blue >> 3;
		return *this;
	}
};

struct BGRA5551_t {
	uint16 b : 5;// order of names changes
	uint16 g : 5;//  byte order of output to 32 bit
	uint16 r : 5;
	uint16 a : 1;

	inline BGRA5551_t& operator=( const BGRA8888_t& in ) {
		r = in.r >> 3;
		g = in.g >> 3;
		b = in.b >> 3;
		a = in.a >> 7;
		return *this;
	}
};

struct BGRA4444_t {
	uint16 b : 4;// order of names changes
	uint16 g : 4;//  byte order of output to 32 bit
	uint16 r : 4;
	uint16 a : 4;

	inline BGRA4444_t& operator=( const BGRA8888_t& in ) {
		r = in.r >> 4;
		g = in.g >> 4;
		b = in.b >> 4;
		a = in.a >> 4;
		return *this;
	}
};

struct RGBX5551_t {
	uint16 r : 5;
	uint16 g : 5;
	uint16 b : 5;
	uint16 x : 1;

	inline RGBX5551_t& operator=( const BGRA8888_t& in ) {
		r = in.r >> 3;
		g = in.g >> 3;
		b = in.b >> 3;
		return *this;
	}
};

//-----------------------------------------------------------------------------
// some important constants
//-----------------------------------------------------------------------------
constexpr auto ARTWORK_GAMMA{ 2.2f };
constexpr auto IMAGE_MAX_DIM{ 2048 };


//-----------------------------------------------------------------------------
// information about each image format
//-----------------------------------------------------------------------------
struct ImageFormatInfo_t {
	const char* m_pName;
	int32 m_NumBytes;
	int32 m_NumRedBits;
	int32 m_NumGreeBits;
	int32 m_NumBlueBits;
	int32 m_NumAlphaBits;
	bool m_IsCompressed;
};


//-----------------------------------------------------------------------------
// Various methods related to pixelmaps and color formats
//-----------------------------------------------------------------------------
namespace ImageLoader {
	bool GetInfo( const char* fileName, int* width, int* height, ImageFormat* imageFormat, float* sourceGamma );
	int32 GetMemRequired( int32 width, int32 height, int32 depth, ImageFormat imageFormat, bool mipmap );
	int32 GetMipMapLevelByteOffset( int32 width, int32 height, ImageFormat imageFormat, int32 skipMipLevels );
	void GetMipMapLevelDimensions( int* width, int* height, int32 skipMipLevels );
	int32 GetNumMipMapLevels( int32 width, int32 height, int32 depth = 1 );
	bool Load( unsigned char* imageData, const char* fileName, int32 width, int32 height, ImageFormat imageFormat, float targetGamma, bool mipmap );
	bool Load( unsigned char* imageData, FILE* fp, int32 width, int32 height, ImageFormat imageFormat, float targetGamma, bool mipmap );

	// convert from any image format to any other image format.
	// return false if the conversion cannot be performed.
	// Strides denote the number of bytes per each line,
	// by default assumes width * # of bytes per pixel
	bool ConvertImageFormat( const unsigned char* src, ImageFormat srcImageFormat, unsigned char* dst, ImageFormat dstImageFormat,
							 int32 width, int32 height, int32 srcStride = 0, int32 dstStride = 0 );

	// must be used in conjunction with ConvertImageFormat() to pre-swap and post-swap
	void PreConvertSwapImageData( unsigned char* pImageData, int32 nImageSize, ImageFormat imageFormat, int32 width = 0, int32 stride = 0 );
	void PostConvertSwapImageData( unsigned char* pImageData, int32 nImageSize, ImageFormat imageFormat, int32 width = 0, int32 stride = 0 );
	void ByteSwapImageData( unsigned char* pImageData, int32 nImageSize, ImageFormat imageFormat, int32 width = 0, int32 stride = 0 );
	bool IsFormatValidForConversion( ImageFormat fmt );

	//-----------------------------------------------------------------------------
	// convert back and forth from D3D format to ImageFormat, regardless of
	// whether it's supported or not
	//-----------------------------------------------------------------------------
	ImageFormat D3DFormatToImageFormat( D3DFORMAT format );
	D3DFORMAT ImageFormatToD3DFormat( ImageFormat format );

	// Flags for ResampleRGBA8888
	enum {
		RESAMPLE_NORMALMAP = 0x1,
		RESAMPLE_ALPHATEST = 0x2,
		RESAMPLE_NICE_FILTER = 0x4,
		RESAMPLE_CLAMPS = 0x8,
		RESAMPLE_CLAMPT = 0x10,
		RESAMPLE_CLAMPU = 0x20,
	};

	struct ResampleInfo_t {
		ResampleInfo_t() = default;

		unsigned char* m_pSrc;
		unsigned char* m_pDest;

		int32 m_nSrcWidth;
		int32 m_nSrcHeight;
		int32 m_nSrcDepth{1};

		int32 m_nDestWidth;
		int32 m_nDestHeight;
		int32 m_nDestDepth{1};

		float m_flSrcGamma;
		float m_flDestGamma;

		float m_flColorScale[4] { 1.0f };  // Color scale factors RGBA
		float m_flColorGoal[4] { 0.0f };   // Color goal values RGBA    DestColor = ColorGoal + scale * (SrcColor - ColorGoal)

		float m_flAlphaThreshhold{ 0.4f };
		float m_flAlphaHiFreqThreshhold{ 0.4f };

		int32 m_nFlags{0};
	};

	bool ResampleRGBA8888( const ResampleInfo_t& info );
	bool ResampleRGBA16161616( const ResampleInfo_t& info );
	bool ResampleRGB323232F( const ResampleInfo_t& info );

	void ConvertNormalMapRGBA8888ToDUDVMapUVLX8888( const unsigned char* src, int32 width, int32 height, unsigned char* dst_ );
	void ConvertNormalMapRGBA8888ToDUDVMapUVWQ8888( const unsigned char* src, int32 width, int32 height, unsigned char* dst_ );
	void ConvertNormalMapRGBA8888ToDUDVMapUV88( const unsigned char* src, int32 width, int32 height, unsigned char* dst_ );

	void ConvertIA88ImageToNormalMapRGBA8888( const unsigned char* src, int32 width, int32 height, unsigned char* dst, float bumpScale );

	void NormalizeNormalMapRGBA8888( unsigned char* src, int32 numTexels );


	//-----------------------------------------------------------------------------
	// Gamma correction
	//-----------------------------------------------------------------------------
	void GammaCorrectRGBA8888( unsigned char* src, unsigned char* dst, int32 width, int32 height, int32 depth, float srcGamma, float dstGamma );


	//-----------------------------------------------------------------------------
	// Makes a gamma table
	//-----------------------------------------------------------------------------
	void ConstructGammaTable( unsigned char* pTable, float srcGamma, float dstGamma );


	//-----------------------------------------------------------------------------
	// Gamma corrects using a previously constructed gamma table
	//-----------------------------------------------------------------------------
	void GammaCorrectRGBA8888( unsigned char* pSrc, unsigned char* pDst, int32 width, int32 height, int32 depth, unsigned char* pGammaTable );


	//-----------------------------------------------------------------------------
	// Generates a number of mipmap levels
	//-----------------------------------------------------------------------------
	void GenerateMipmapLevels( unsigned char* pSrc, unsigned char* pDst, int32 width, int32 height, int32 depth,
		                       ImageFormat imageFormat, float srcGamma, float dstGamma, int32 numLevels = 0 );

	// Low quality mipmap generation, but way faster.
	void GenerateMipmapLevelsLQ( unsigned char* pSrc, unsigned char* pDst, int32 width, int32 height, ImageFormat imageFormat, int32 numLevels );

	//-----------------------------------------------------------------------------
	// operations on square images (src and dst can be the same)
	//-----------------------------------------------------------------------------
	bool RotateImageLeft( const unsigned char* src, unsigned char* dst, int32 widthHeight, ImageFormat imageFormat );
	bool RotateImage180( const unsigned char* src, unsigned char* dst, int32 widthHeight, ImageFormat imageFormat );
	bool FlipImageVertically( void* pSrc, void* pDst, int32 nWidth, int32 nHeight, ImageFormat imageFormat, int32 nDstStride = 0 );
	bool FlipImageHorizontally( void* pSrc, void* pDst, int32 nWidth, int32 nHeight, ImageFormat imageFormat, int32 nDstStride = 0 );
	bool SwapAxes( unsigned char* src, int32 widthHeight, ImageFormat imageFormat );


	//-----------------------------------------------------------------------------
	// Returns info about each image format
	//-----------------------------------------------------------------------------
	ImageFormatInfo_t const& ImageFormatInfo( ImageFormat fmt );


	//-----------------------------------------------------------------------------
	// Gets the name of the image format
	//-----------------------------------------------------------------------------
	inline char const* GetName( ImageFormat fmt ) {
		return ImageFormatInfo( fmt ).m_pName;
	}


	//-----------------------------------------------------------------------------
	// Gets the size of the image format in bytes
	//-----------------------------------------------------------------------------
	inline int32 SizeInBytes( ImageFormat fmt ) {
		return ImageFormatInfo( fmt ).m_NumBytes;
	}

	//-----------------------------------------------------------------------------
	// Does the image format support transparency?
	//-----------------------------------------------------------------------------
	inline bool IsTransparent( const ImageFormat fmt ) {
		return ImageFormatInfo( fmt ).m_NumAlphaBits > 0;
	}


	//-----------------------------------------------------------------------------
	// Is the image format compressed?
	//-----------------------------------------------------------------------------
	inline bool IsCompressed( const ImageFormat fmt ) {
		return ImageFormatInfo( fmt ).m_IsCompressed;
	}

	//-----------------------------------------------------------------------------
	// Is any channel > 8 bits?
	//-----------------------------------------------------------------------------
	inline bool HasChannelLargerThan8Bits( const ImageFormat fmt ) {
		const ImageFormatInfo_t info = ImageFormatInfo( fmt );
		return info.m_NumRedBits > 8 or info.m_NumGreeBits > 8 or info.m_NumBlueBits > 8 or info.m_NumAlphaBits > 8;
	}

	inline bool IsRuntimeCompressed( const ImageFormat fmt ) {
		return fmt == IMAGE_FORMAT_DXT1_RUNTIME or fmt == IMAGE_FORMAT_DXT5_RUNTIME;
	}
}

#if _MSC_VER
	#pragma warning( pop )
#endif
