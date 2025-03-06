//
// Created by ENDERZOMBI102 on 30/08/2024.
//
#pragma once


namespace TGA {
	struct [[gnu::packed]] ColorMapSpec {
		uint16 entryIndex{};
		uint16 entryLength{};
		uint8 size{}; // bpp
	};

	struct [[gnu::packed]] ImageDesc {
		int32 alphaDepth : 4 {};
		int32 orderRightToLeft : 1 {};
		int32 orderTopToBottom : 1 {};
		int32 padding : 2 {};
	};

	struct [[gnu::packed]] ImageSpec {
		uint16 xOrigin{};
		uint16 yOrigin{};
		uint16 width{};
		uint16 height{};
		uint8 depth{}; // pixel size
		ImageDesc imageDesc{};
	};

	enum class ColorMapType : uint8 {
		None,
		ColorPalette,
	};

	enum class ImageType : uint8 {
		NoData,
		UncompressedColorMapped,
		UncompressedRGB,
		UncompressedGreyscale,
		RLEColorMapped = 9,
		RLERGB,
		RLEGreyscale,
		// huffman + delta + rle
		CompressedColorMapped = 32,
		// huffman + delta + rle, 4-pass quadtree-type
		CompressedColorMapped4Pass,
	};

	struct [[gnu::packed]] Header {
		uint8 idLength{};               // id_length
		ColorMapType colorMapType{};    // colormap_type
		ImageType imageType{};          // image_type
		ColorMapSpec colorMapSpec{};    // colormap_index, colormap_length, colormap_size
		ImageSpec imageSpec{};          // x_origin, y_origin, width, height, pixel_size, attributes
	};

	static_assert( sizeof( Header ) == 18, "The TGA header is 18 bytes" );
}
