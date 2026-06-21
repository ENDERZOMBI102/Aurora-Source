//
// Created by ENDERZOMBI102 on 21/12/2025.
// 
#pragma once
#include "vtf/vtf.h"
#include "vtfpp/vtfpp.h"


class CVTFTexture : public IVTFTexture {
public:
	CVTFTexture() = default;
	~CVTFTexture() override = default;

	// Initializes the texture and allocates space for the bits
	// In most cases, you shouldn't force the mip count.
	auto Init( int32 pWidth, int32 pHeight, int32 pDepth, ImageFormat pFmt, int32 pFlags, int32 pFrameCount, int32 pForceMipCount = -1 ) -> bool override;

	// Methods to set other texture fields
	void SetBumpScale( float flScale ) override;
	void SetReflectivity( const Vector& vecReflectivity ) override;

	// Methods to initialize the low-res image
	void InitLowResImage( int32 nWidth, int32 nHeight, ImageFormat fmt ) override;

	// set the resource data (for writers). pass size=0 to delete data. if pdata is not null,
	// the resource data will be copied from *pData
	auto SetResourceData( uint32 eType, void const* pData, size_t nDataSize ) -> void*  override;

	// find the resource data and return a pointer to it. The data pointed to by this pointer will
	// go away when the ivtftexture does. retruns null if resource not present
	auto GetResourceData( uint32 eType, size_t* pDataSize ) const -> void*  override;

	// Locates the resource entry info if it's present, easier than crawling array types
	auto HasResourceEntry( uint32 eType ) const -> bool  override;

	// Retrieve available resource types of this IVTFTextures
	//		arrTypesBuffer			buffer to be filled with resource types available.
	//		numTypesBufferElems		how many resource types the buffer can accomodate.
	// Returns:
	//		number of resource types available (can be greater than "numTypesBufferElems"
	//		in which case only first "numTypesBufferElems" are copied to "arrTypesBuffer")
	auto GetResourceTypes( uint32* arrTypesBuffer, int32 numTypesBufferElems ) const -> uint32  override;

	// When unserializing, we can skip a certain number of mip levels,
	// and we also can just load everything but the image data
	// NOTE: If you load only the buffer header, you'll need to use the
	// VTFBufferHeaderSize() method below to only read that much from the file
	// NOTE: If you skip mip levels, the height + width of the texture will
	// change to reflect the size of the largest read in mip level
	auto Unserialize( CUtlBuffer& buf, bool bHeaderOnly = false, int32 nSkipMipLevels = 0 ) -> bool  override;
	auto Serialize( CUtlBuffer& buf ) -> bool  override;

	// These are methods to help with optimization:
	// Once the header is read in, they indicate where to start reading
	// other data (measured from file start), and how many bytes to read....
	void LowResFileInfo( int32* pStartLocation, int32* pSizeInBytes ) const override;
	void ImageFileInfo( int32 nFrame, int32 nFace, int32 nMip, int32* pStartLocation, int32* pSizeInBytes ) const override;
	auto FileSize( int32 nMipSkipCount = 0 ) const -> int32  override;

	// Attributes...
	auto Width() const -> int32  override;
	auto Height() const -> int32  override;
	auto Depth() const -> int32  override;
	auto MipCount() const -> int32  override;

	// returns the size of one row of a particular mip level
	auto RowSizeInBytes( int32 nMipLevel ) const -> int32  override;

	// returns the size of one face of a particular mip level
	auto FaceSizeInBytes( int32 nMipLevel ) const -> int32  override;

	auto Format() const -> ImageFormat  override;
	auto FaceCount() const -> int32  override;
	auto FrameCount() const -> int32  override;
	auto Flags() const -> int32  override;

	auto BumpScale() const -> float  override;

	auto LowResWidth() const -> int32  override;
	auto LowResHeight() const -> int32  override;
	auto LowResFormat() const -> ImageFormat  override;

	// NOTE: reflectivity[0] = blue, [1] = greem, [2] = red
	auto Reflectivity() const -> const Vector& override;

	auto IsCubeMap() const -> bool  override;
	auto IsNormalMap() const -> bool  override;
	auto IsVolumeTexture() const -> bool  override;

	// Computes the dimensions of a particular mip level
	void ComputeMipLevelDimensions( int32 iMipLevel, int32* pMipWidth, int32* pMipHeight, int32* pMipDepth ) const override;

	// Computes the size (in bytes) of a single mipmap of a single face of a single frame
	auto ComputeMipSize( int32 iMipLevel ) const -> int32  override;

	// Computes the size of a subrect (specified at the top mip level) at a particular lower mip level
	void ComputeMipLevelSubRect( Rect_t* pSrcRect, int32 nMipLevel, Rect_t* pSubRect ) const override;

	// Computes the size (in bytes) of a single face of a single frame
	// All mip levels starting at the specified mip level are included
	auto ComputeFaceSize( int32 iStartingMipLevel = 0 ) const -> int32  override;

	// Computes the total size (in bytes) of all faces, all frames
	auto ComputeTotalSize() const -> int32  override;

	// Returns the base address of the image data
	auto ImageData() -> uint8*  override;

	// Returns a pointer to the data associated with a particular frame, face, and mip level
	auto ImageData( int32 iFrame, int32 iFace, int32 iMipLevel ) -> uint8*  override;

	// Returns a pointer to the data associated with a particular frame, face, mip level, and offset
	auto ImageData( int32 iFrame, int32 iFace, int32 iMipLevel, int32 x, int32 y, int32 z = 0 ) -> uint8*  override;

	// Returns the base address of the low-res image data
	auto LowResImageData() -> uint8*  override;

	// Converts the textures image format. Use IMAGE_FORMAT_DEFAULT
	// if you want to be able to use various tool functions below
	void ConvertImageFormat( ImageFormat fmt, bool bNormalToDUDV ) override;

	// NOTE: The following methods only work on textures using the
	// IMAGE_FORMAT_DEFAULT!

	// Generate spheremap based on the current cube faces (only works for cubemaps)
	// The look dir indicates the direction of the center of the sphere
	// NOTE: Only call this *after* cube faces have been correctly
	// oriented (using FixCubemapFaceOrientation)
	void GenerateSpheremap( LookDir_t lookDir = LOOK_DOWN_Z ) override;

	// Generate spheremap based on the current cube faces (only works for cubemaps)
	// The look dir indicates the direction of the center of the sphere
	// NOTE: Only call this *after* cube faces have been correctly
	// oriented (using FixCubemapFaceOrientation)
	void GenerateHemisphereMap( uint8* pSphereMapBitsRGBA, int32 targetWidth, int32 targetHeight, LookDir_t lookDir, int32 iFrame ) override;

	// Fixes the cubemap faces orientation from our standard to the
	// standard the material system needs.
	void FixCubemapFaceOrientation() override;

	// Generates mipmaps from the base mip levels
	void GenerateMipmaps() override;

	// Put 1/miplevel (1..n) into alpha.
	void PutOneOverMipLevelInAlpha() override;

	// Computes the reflectivity
	void ComputeReflectivity() override;

	// Computes the alpha flags
	void ComputeAlphaFlags() override;

	// Generate the low-res image bits
	auto ConstructLowResImage() -> bool  override;

	// Gets the texture all internally consistent assuming you've loaded
	// mip 0 of all faces of all frames
	void PostProcess( bool bGenerateSpheremap, LookDir_t lookDir = LOOK_DOWN_Z, bool bAllowFixCubemapOrientation = true ) override;

	// Blends adjacent pixels on cubemap borders, since the card doesn't do it. If the texture
	// is S3TC compressed, then it has to do it AFTER the texture has been compressed to prevent
	// artifacts along the edges.
	//
	// If bSkybox is true, it assumes the faces are oriented in the way the engine draws the skybox
	// (which happens to be different from the way cubemaps have their faces).
	void MatchCubeMapBorders( int32 iStage, ImageFormat finalFormat, bool bSkybox ) override;

	// Sets threshhold values for alphatest mipmapping
	void SetAlphaTestThreshholds( float flBase, float flHighFreq ) override;

	// Sets post-processing flags (settings are copied, pointer passed to distinguish between structure versions)
	void SetPostProcessingSettings( VtfProcessingOptions const* pOptions ) override;
private:
	vtfpp::VTF m_Inner{};
};
