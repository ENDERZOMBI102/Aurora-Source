//
// Created by ENDERZOMBI102 on 21/12/2025.
// 
#include "cvtf.hpp"


auto CVTFTexture::Init( const int32 pWidth, const int32 pHeight, const int32 pDepth, ImageFormat pFmt, const int32 pFlags, const int32 pFrameCount, int32 pForceMipCount ) -> bool {
	const vtfpp::VTF::CreationOptions options{
		.flags = pFlags,
		.initialFrameCount = pFrameCount,
		.initialDepth = pDepth,
	};

	// std::vector throws...
	try {
		m_Inner = vtfpp::VTF::create( static_cast<vtfpp::ImageFormat>( pFmt ), pWidth, pHeight, options );
	} catch ( const std::exception& ) {
		return false;
	}
	return true;
}
void CVTFTexture::SetBumpScale( float flScale ) { AssertMsg( false, "void CVTFTexture::SetBumpScale( %f )", flScale ); }
void CVTFTexture::SetReflectivity( const Vector& vecReflectivity ) { AssertMsg( false, "void CVTFTexture::SetReflectivity( %p )", &vecReflectivity ); }
void CVTFTexture::InitLowResImage( int32 nWidth, int32 nHeight, ImageFormat fmt ) { AssertMsg( false, "void CVTFTexture::InitLowResImage( %d, %d, %d )", nWidth, nHeight, fmt ); }
auto CVTFTexture::SetResourceData( uint32 eType, void const* pData, size_t nDataSize ) -> void* { AssertMsg( false, "auto CVTFTexture::SetResourceData( %d, %p, %d ) -> void*", eType, pData, nDataSize ); return {}; }
auto CVTFTexture::GetResourceData( uint32 eType, size_t* pDataSize ) const -> void* { AssertMsg( false, "auto CVTFTexture::GetResourceData( %d, %p ) const -> void*", eType, pDataSize ); return {}; }
auto CVTFTexture::HasResourceEntry( uint32 eType ) const -> bool { AssertMsg( false, "auto CVTFTexture::HasResourceEntry( %d ) const -> bool", eType ); return {}; }
auto CVTFTexture::GetResourceTypes( uint32* arrTypesBuffer, int32 numTypesBufferElems ) const -> uint32 { AssertMsg( false, "auto CVTFTexture::GetResourceTypes( %p, %d ) const -> uint32", arrTypesBuffer, numTypesBufferElems ); return {}; }
auto CVTFTexture::Unserialize( CUtlBuffer& buf, bool bHeaderOnly, int32 nSkipMipLevels ) -> bool { AssertMsg( false, "auto CVTFTexture::Unserialize( %p, %d, %d ) -> bool", &buf, bHeaderOnly, nSkipMipLevels ); return {}; }
auto CVTFTexture::Serialize( CUtlBuffer& buf ) -> bool { AssertMsg( false, "auto CVTFTexture::Serialize( %p ) -> bool", &buf ); return {}; }
void CVTFTexture::LowResFileInfo( int32* pStartLocation, int32* pSizeInBytes ) const { AssertMsg( false, "void CVTFTexture::LowResFileInfo( %p, %p ) const", pStartLocation, pSizeInBytes ); }
void CVTFTexture::ImageFileInfo( int32 nFrame, int32 nFace, int32 nMip, int32* pStartLocation, int32* pSizeInBytes ) const { AssertMsg( false, "void CVTFTexture::ImageFileInfo( %d, %d, %d, %p, %p ) const", nFrame, nFace, nMip, pStartLocation, pSizeInBytes  ); }
auto CVTFTexture::FileSize( int32 nMipSkipCount ) const -> int32 { AssertMsg( false, "auto CVTFTexture::FileSize( %d ) const -> int32", nMipSkipCount ); return {}; }
auto CVTFTexture::Width() const -> int32 { AssertMsg( false, "auto CVTFTexture::Width() const -> int32" ); return {}; }
auto CVTFTexture::Height() const -> int32 { AssertMsg( false, "auto CVTFTexture::Height() const -> int32" ); return {}; }
auto CVTFTexture::Depth() const -> int32 { AssertMsg( false, "auto CVTFTexture::Depth() const -> int32" ); return {}; }
auto CVTFTexture::MipCount() const -> int32 { AssertMsg( false, "auto CVTFTexture::MipCount() const -> int32" ); return {}; }
auto CVTFTexture::RowSizeInBytes( int32 nMipLevel ) const -> int32 { AssertMsg( false, "auto CVTFTexture::RowSizeInBytes( %d ) const -> int32", nMipLevel ); return {}; }
auto CVTFTexture::FaceSizeInBytes( int32 nMipLevel ) const -> int32 { AssertMsg( false, "auto CVTFTexture::FaceSizeInBytes( %d ) const -> int32", nMipLevel ); return {}; }
auto CVTFTexture::Format() const -> ImageFormat { AssertMsg( false, "auto CVTFTexture::Format() const -> ImageFormat" ); return {}; }
auto CVTFTexture::FaceCount() const -> int32 { AssertMsg( false, "auto CVTFTexture::FaceCount() const -> int32" ); return {}; }
auto CVTFTexture::FrameCount() const -> int32 { AssertMsg( false, "auto CVTFTexture::FrameCount() const -> int32" ); return {}; }
auto CVTFTexture::Flags() const -> int32 { AssertMsg( false, "auto CVTFTexture::Flags() const -> int32" ); return {}; }
auto CVTFTexture::BumpScale() const -> float { AssertMsg( false, "auto CVTFTexture::BumpScale() const -> float" ); return {}; }
auto CVTFTexture::LowResWidth() const -> int32 { AssertMsg( false, "auto CVTFTexture::LowResWidth() const -> int32" ); return {}; }
auto CVTFTexture::LowResHeight() const -> int32 { AssertMsg( false, "auto CVTFTexture::LowResHeight() const -> int32" ); return {}; }
auto CVTFTexture::LowResFormat() const -> ImageFormat { AssertMsg( false, "auto CVTFTexture::LowResFormat() const -> ImageFormat" ); return {}; }
auto CVTFTexture::Reflectivity() const -> const Vector& { AssertMsg( false, "auto CVTFTexture::Reflectivity() const -> const Vector&" ); return {}; }
auto CVTFTexture::IsCubeMap() const -> bool { AssertMsg( false, "auto CVTFTexture::IsCubeMap() const -> bool" ); return {}; }
auto CVTFTexture::IsNormalMap() const -> bool { AssertMsg( false, "auto CVTFTexture::IsNormalMap() const -> bool" ); return {}; }
auto CVTFTexture::IsVolumeTexture() const -> bool { AssertMsg( false, "auto CVTFTexture::IsVolumeTexture() const -> bool" ); return {}; }
void CVTFTexture::ComputeMipLevelDimensions( int32 iMipLevel, int32* pMipWidth, int32* pMipHeight, int32* pMipDepth ) const { }
auto CVTFTexture::ComputeMipSize( int32 iMipLevel ) const -> int32 { AssertMsg( false, "auto CVTFTexture::ComputeMipSize( %d ) const -> int32", iMipLevel ); return {}; }
void CVTFTexture::ComputeMipLevelSubRect( Rect_t* pSrcRect, int32 nMipLevel, Rect_t* pSubRect ) const { }
auto CVTFTexture::ComputeFaceSize( int32 iStartingMipLevel ) const -> int32 { AssertMsg( false, "auto CVTFTexture::ComputeFaceSize( %d ) const -> int32", iStartingMipLevel ); return {}; }
auto CVTFTexture::ComputeTotalSize() const -> int32 { AssertMsg( false, "auto CVTFTexture::ComputeTotalSize() const -> int32" ); return {}; }
auto CVTFTexture::ImageData() -> uint8* { AssertMsg( false, "auto CVTFTexture::ImageData() -> uint8*" ); return {}; }
auto CVTFTexture::ImageData( int32 iFrame, int32 iFace, int32 iMipLevel ) -> uint8* { AssertMsg( false, "auto CVTFTexture::ImageData( %d, %d, %d ) -> uint8*", iFrame, iFace, iMipLevel ); return {}; }
auto CVTFTexture::ImageData( int32 iFrame, int32 iFace, int32 iMipLevel, int32 x, int32 y, int32 z ) -> uint8* { AssertMsg( false, "auto CVTFTexture::ImageData( %d, %d, %d, %d, %d, %d ) -> uint8*", iFrame, iFace, iMipLevel, x, y, z  ); return {}; }
auto CVTFTexture::LowResImageData() -> uint8* { AssertMsg( false, "auto CVTFTexture::LowResImageData() -> uint8*" ); return {}; }
void CVTFTexture::ConvertImageFormat( ImageFormat fmt, bool bNormalToDUDV ) { AssertMsg( false, "void CVTFTexture::ConvertImageFormat( %d, %d )", fmt, bNormalToDUDV ); }
void CVTFTexture::GenerateSpheremap( LookDir_t lookDir ) { AssertMsg( false, "void CVTFTexture::GenerateSpheremap( %d )", lookDir ); }
void CVTFTexture::GenerateHemisphereMap( uint8* pSphereMapBitsRGBA, int32 targetWidth, int32 targetHeight, LookDir_t lookDir, int32 iFrame ) { AssertMsg( false, "void CVTFTexture::GenerateHemisphereMap( %p, %d, %d, %d, %d )", pSphereMapBitsRGBA, targetWidth, targetHeight, lookDir, iFrame ); }
void CVTFTexture::FixCubemapFaceOrientation() { AssertMsg( false, "void CVTFTexture::FixCubemapFaceOrientation()" ); }
void CVTFTexture::GenerateMipmaps() { AssertMsg( false, "void CVTFTexture::GenerateMipmaps()" ); }
void CVTFTexture::PutOneOverMipLevelInAlpha() { AssertMsg( false, "void CVTFTexture::PutOneOverMipLevelInAlpha()" ); }
void CVTFTexture::ComputeReflectivity() { AssertMsg( false, "void CVTFTexture::ComputeReflectivity()" ); }
void CVTFTexture::ComputeAlphaFlags() { AssertMsg( false, "void CVTFTexture::ComputeAlphaFlags()" ); }
auto CVTFTexture::ConstructLowResImage() -> bool { AssertMsg( false, "auto CVTFTexture::ConstructLowResImage()" ); return {}; }
void CVTFTexture::PostProcess( bool bGenerateSpheremap, LookDir_t lookDir, bool bAllowFixCubemapOrientation ) { AssertMsg( false, "void CVTFTexture::PostProcess( %d, %d, %d )", bGenerateSpheremap, lookDir, bAllowFixCubemapOrientation ); }
void CVTFTexture::MatchCubeMapBorders( int32 iStage, ImageFormat finalFormat, bool bSkybox ) { AssertMsg( false, "void CVTFTexture::MatchCubeMapBorders( %d, %d, %d )", iStage, finalFormat, bSkybox ); }
void CVTFTexture::SetAlphaTestThreshholds( float flBase, float flHighFreq ) { AssertMsg( false, "void CVTFTexture::SetAlphaTestThreshholds( %f, %f )", flBase, flHighFreq ); }
void CVTFTexture::SetPostProcessingSettings( VtfProcessingOptions const* pOptions ) { AssertMsg( false, "void CVTFTexture::SetPostProcessingSettings( %p )", pOptions ); }
