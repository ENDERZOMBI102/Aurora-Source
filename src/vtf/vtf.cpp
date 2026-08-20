//
// Created by ENDERZOMBI102 on 13/07/2026.
//
#include "vtf/vtf.h"
#include "cvtf.hpp"


auto CreateVTFTexture() -> IVTFTexture* {
	return new CVTFTexture{};
}
void DestroyVTFTexture( IVTFTexture* pTexture ) {
	delete dynamic_cast<CVTFTexture*>( pTexture );
}

auto VTFFileHeaderSize( int32 pMajorVersion, int32 pMinorVersion ) -> int32 {
	int32 size{};
	if ( pMajorVersion == vtfpp::VTF::PLATFORM_PC ) {
		size += 4;  // magic (VTF\0)
		size += 8;  // version
		size += 4;  // headerSize
		size += 2;  // width
		size += 2;  // height
		size += 4;  // height
		size += 4;  // frameCount
		size += 4;  // -
		size += 36; // reflectivity
		size += 4;  // -
		size += 4;  // bumpMapScale
		size += 4;  // format
		size += 1;  // mipCount
		size += 4;  // lowResFormat (DXT1)
		size += 1;  // thumbnailWidth
		size += 1;  // thumbnailHeight // 87
		if ( pMinorVersion >= 2 ) {
			size += 2;  // depth // 89
		}
		if ( pMinorVersion >= 3 ) {
			size += 3;  // -
			size += 4;  // resourceCount
			size += 8;  // - // 104
		}
	}
	return size;

	AssertMsg( false, "VTFFileHeaderSize(%d, %d)", pMajorVersion, pMinorVersion );
	return {};
}

auto ConvertVTFTo360Format( const char* pDebugName, CUtlBuffer& sourceBuf, CUtlBuffer& targetBuf, CompressFunc_t pCompressFunc ) -> bool {
	AssertMsg( false, "ConvertVTFTo360Format(%s, %p, %p, %p)",pDebugName, &sourceBuf, &targetBuf, pCompressFunc );
	return {};
}

auto GetVTFPreload360Data( const char* pDebugName, CUtlBuffer& fileBufferIn, CUtlBuffer& preloadBufferOut ) -> bool {
	AssertMsg( false, "GetVTFPreload360Data(%s, %p, %p)", pDebugName, &fileBufferIn, &preloadBufferOut );
	return {};
}
