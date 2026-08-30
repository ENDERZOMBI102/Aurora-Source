//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//=============================================================================//
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include "bitmap/imageformat.h"
#include "mathlib/vector.h"
#include "tier1/utlbuffer.h"
#include "tier1/utlmap.h"
#include "vtf/vtf.h"


static void Usage() {
	printf( "Usage: vtfdiff file1.vtf file2.vtf\n" );
}

static bool LoadFileIntoBuffer( const char* pFileName, CUtlBuffer& buf ) {
	struct stat statBuf{};
	if ( stat( pFileName, &statBuf ) != 0 ) {
		printf( "Can't find file %s\n", pFileName );
		return false;
	}

	buf.EnsureCapacity( statBuf.st_size );
	FILE* fp = fopen( pFileName, "rb" );
	if ( not fp ) {
		printf( "Can't open file %s for reading\n", pFileName );
		return false;
	}

	const int nBytesRead = static_cast<int>( fread( buf.Base(), 1, statBuf.st_size, fp ) );
	fclose( fp );

	buf.SeekPut( CUtlBuffer::SEEK_HEAD, nBytesRead );
	return true;
}

static char const* ResourceToString( const uint32 uiResType ) {
	static char chBuffer[ 256 ];

	switch ( uiResType ) {
		case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
			return "VTF_LEGACY_RSRC_LOW_RES_IMAGE";
		case VTF_LEGACY_RSRC_IMAGE:
			return "VTF_LEGACY_RSRC_IMAGE";
		case VTF_RSRC_SHEET:
			return "VTF_RSRC_SHEET";
		case MK_VTF_RSRC_ID( 'C', 'R', 'C' ):
			return "CRC";
		case VTF_RSRC_TEXTURE_LOD_SETTINGS:
			return "VTF_RSRC_TEXTURE_LOD_SETTINGS";

		default:
			sprintf( chBuffer, "0x%08X", uiResType );
			return chBuffer;
	}

	return chBuffer;
}

void PrintFlags( int flags ) {
	#define PRNFLAG( flagname )                                                        \
		if ( (flags & flagname) == flagname ) {                                        \
			flags &= ~( flagname );                                                    \
			printf( "%s%s", #flagname + strlen( "TEXTUREFLAGS_" ), flags ? "|" : "" ); \
		}


	PRNFLAG( TEXTUREFLAGS_POINTSAMPLE )
	PRNFLAG( TEXTUREFLAGS_TRILINEAR )
	PRNFLAG( TEXTUREFLAGS_CLAMPS )
	PRNFLAG( TEXTUREFLAGS_CLAMPT )
	PRNFLAG( TEXTUREFLAGS_ANISOTROPIC )
	PRNFLAG( TEXTUREFLAGS_HINT_DXT5 )
	PRNFLAG( TEXTUREFLAGS_SRGB )
	PRNFLAG( TEXTUREFLAGS_NORMAL )
	PRNFLAG( TEXTUREFLAGS_NOMIP )
	PRNFLAG( TEXTUREFLAGS_NOLOD )
	PRNFLAG( TEXTUREFLAGS_ALL_MIPS )
	PRNFLAG( TEXTUREFLAGS_PROCEDURAL )
	PRNFLAG( TEXTUREFLAGS_ONEBITALPHA )
	PRNFLAG( TEXTUREFLAGS_EIGHTBITALPHA )
	PRNFLAG( TEXTUREFLAGS_ENVMAP )
	PRNFLAG( TEXTUREFLAGS_RENDERTARGET )
	PRNFLAG( TEXTUREFLAGS_DEPTHRENDERTARGET )
	PRNFLAG( TEXTUREFLAGS_NODEBUGOVERRIDE )
	PRNFLAG( TEXTUREFLAGS_SINGLECOPY )
	PRNFLAG( TEXTUREFLAGS_STAGING_MEMORY )
	PRNFLAG( TEXTUREFLAGS_IMMEDIATE_CLEANUP )
	PRNFLAG( TEXTUREFLAGS_IGNORE_PICMIP )
	PRNFLAG( TEXTUREFLAGS_UNUSED_00400000 )
	PRNFLAG( TEXTUREFLAGS_NODEPTHBUFFER )
	PRNFLAG( TEXTUREFLAGS_UNUSED_01000000 )
	PRNFLAG( TEXTUREFLAGS_CLAMPU )
	PRNFLAG( TEXTUREFLAGS_VERTEXTEXTURE )
	PRNFLAG( TEXTUREFLAGS_SSBUMP )
	PRNFLAG( TEXTUREFLAGS_UNUSED_10000000 )
	PRNFLAG( TEXTUREFLAGS_BORDER )
	PRNFLAG( TEXTUREFLAGS_UNUSED_40000000 )
	PRNFLAG( TEXTUREFLAGS_UNUSED_80000000 )

	#undef PRNFLAG

	if ( flags ) {
		printf( "0x%08X", flags );
	}
}

int main( int argc, char** argv ) {
	if ( argc != 3 ) {
		Usage();
		return 10;
	}

	CUtlBuffer file1;
	CUtlBuffer file2;

	if ( not LoadFileIntoBuffer( argv[ 1 ], file1 ) ) {
		return 21;
	}
	if ( not LoadFileIntoBuffer( argv[ 2 ], file2 ) ) {
		return 22;
	}

	IVTFTexture* pTexture1 = CreateVTFTexture();
	IVTFTexture* pTexture2 = CreateVTFTexture();

	IVTFTexture* arrTextures[ 2 ] = { pTexture1, pTexture2 };

	bool bMatch = true;

	if ( not pTexture1->Unserialize( file1 ) ) {
		printf( "error loading %s\n", argv[ 1 ] );
		return 31;
	}
	if ( not pTexture2->Unserialize( file2 ) ) {
		printf( "error loading %s\n", argv[ 2 ] );
		return 32;
	}

	if ( pTexture1->Width() != pTexture2->Width() or pTexture1->Height() != pTexture2->Height() or pTexture1->Depth() != pTexture2->Depth() ) {
		printf(
			"%s dimensions differ: %dx%dx%d != %dx%dx%d\n",
			argv[ 1 ],
			static_cast<int>( pTexture1->Width() ), static_cast<int>( pTexture1->Height() ), static_cast<int>( pTexture1->Depth() ),
			static_cast<int>( pTexture2->Width() ), static_cast<int>( pTexture2->Height() ), static_cast<int>( pTexture2->Depth() )
		);
		bMatch = false;
	}

	if ( pTexture1->LowResWidth() != pTexture2->LowResWidth() or pTexture1->LowResHeight() != pTexture2->LowResHeight() ) {
		printf(
			"%s lowres dimensions differ: %dx%d != %dx%d\n",
			argv[ 1 ],
			static_cast<int>( pTexture1->LowResWidth() ), static_cast<int>( pTexture1->LowResHeight() ),
			static_cast<int>( pTexture2->LowResWidth() ), static_cast<int>( pTexture2->LowResHeight() )
		);
		bMatch = false;
	}

	if ( pTexture1->MipCount() != pTexture2->MipCount() ) {
		printf( "%s differing mipcounts: %d != %d\n", argv[ 1 ], static_cast<int>( pTexture1->MipCount() ), static_cast<int>( pTexture2->MipCount() ) );
		bMatch = false;
	}

	if ( pTexture1->FaceCount() != pTexture2->FaceCount() ) {
		printf( "%s differing facecount: %d != %d\n", argv[ 1 ], static_cast<int>( pTexture1->FaceCount() ), static_cast<int>( pTexture2->FaceCount() ) );
		bMatch = false;
	}

	if ( pTexture1->FrameCount() != pTexture2->FrameCount() ) {
		printf( "%s differing framecount: %d != %d\n", argv[ 1 ], static_cast<int>( pTexture1->FrameCount() ), static_cast<int>( pTexture2->FrameCount() ) );
		bMatch = false;
	}

	if ( pTexture1->Flags() != pTexture2->Flags() ) {
		printf( "%s differing flags: \"", argv[ 1 ] );
		PrintFlags( pTexture1->Flags() );
		printf( "\" != \"" );
		PrintFlags( pTexture2->Flags() );
		printf( "\"\n" );
		bMatch = false;
	}

	if ( pTexture1->BumpScale() != pTexture2->BumpScale() ) {
		printf( "%s differing bumpscale: %f != %f\n", argv[ 1 ], static_cast<float>( pTexture1->BumpScale() ), static_cast<float>( pTexture2->BumpScale() ) );
		bMatch = false;
	}

	if ( pTexture1->Format() != pTexture2->Format() ) {
		printf( "%s differing image format: %s != %s\n", argv[ 1 ], ImageLoader::GetName( pTexture1->Format() ), ImageLoader::GetName( pTexture2->Format() ) );
		bMatch = false;
	}

	if ( pTexture1->LowResFormat() != pTexture2->LowResFormat() ) {
		Assert( 0 );
		printf( "%s differing lowres image format: %s != %s\n", argv[ 1 ], ImageLoader::GetName( pTexture1->LowResFormat() ), ImageLoader::GetName( pTexture2->LowResFormat() ) );
		bMatch = false;
	}

	const Vector& vReflectivity1 = pTexture1->Reflectivity();
	const Vector& vReflectivity2 = pTexture2->Reflectivity();
	if ( not VectorsAreEqual( vReflectivity1, vReflectivity2, 0.0001f ) ) {
		printf(
			"%s differing reflectivity: [%f,%f,%f] != [%f,%f,%f]\n",
			argv[ 1 ],
			static_cast<float>( pTexture1->Reflectivity()[ 0 ] ),
			static_cast<float>( pTexture1->Reflectivity()[ 1 ] ),
			static_cast<float>( pTexture1->Reflectivity()[ 2 ] ),
			static_cast<float>( pTexture2->Reflectivity()[ 0 ] ),
			static_cast<float>( pTexture2->Reflectivity()[ 1 ] ),
			static_cast<float>( pTexture2->Reflectivity()[ 2 ] )
		);
		bMatch = false;
	}

	if ( pTexture1->ComputeTotalSize() != pTexture2->ComputeTotalSize() ) {
		printf( "%s differing image data size: %d != %d\n", argv[ 1 ], static_cast<int>( pTexture1->ComputeTotalSize() ), static_cast<int>( pTexture2->ComputeTotalSize() ) );
		bMatch = false;
	}

	if ( bMatch ) {
		uint8 const* pData1 = pTexture1->ImageData();
		uint8 const* pData2 = pTexture2->ImageData();

		int const iSize = pTexture1->ComputeTotalSize();
		if ( memcmp( pData1, pData2, iSize ) != 0 ) {
			printf( "%s image data different\n", argv[ 1 ] );

			if ( pTexture1->Format() == IMAGE_FORMAT_DXT1 or pTexture1->Format() == IMAGE_FORMAT_DXT3 or pTexture1->Format() == IMAGE_FORMAT_DXT5 or pTexture1->Format() == IMAGE_FORMAT_ATI2N or pTexture1->Format() == IMAGE_FORMAT_ATI1N ) {
				int i, numOffsetsComplained = 0;
				for ( i = 0; i < iSize; i += 1 ) {
					if ( pData1[ i ] != pData2[ i ] ) {
						printf( "image data at offset %d different\n", i );
						if ( numOffsetsComplained++ > 10 ) {
							printf( "image data significantly differs!\n" );
							break;
						}
					}
				}
			} else {
				for ( int iFrame = 0; iFrame < pTexture1->FrameCount(); iFrame += 1 ) {
					for ( int iMipLevel = 0; iMipLevel < pTexture1->MipCount(); iMipLevel += 1 ) {
						int nMipWidth, nMipHeight, nMipDepth;
						pTexture1->ComputeMipLevelDimensions( iMipLevel, &nMipWidth, &nMipHeight, &nMipDepth );

						for ( int iCubeFace = 0; iCubeFace < pTexture1->FrameCount(); iCubeFace += 1 ) {
							for ( int z = 0; z < nMipDepth; z += 1 ) {
								pData1 = pTexture1->ImageData( iFrame, iCubeFace, iMipLevel, 0, 0, z );
								pData2 = pTexture2->ImageData( iFrame, iCubeFace, iMipLevel, 0, 0, z );

								const int nMipSize = pTexture1->ComputeMipSize( iMipLevel );
								if ( memcmp( pData1, pData2, nMipSize ) ) {
									bool bBreak = false;

									for ( int y = 0; y < nMipHeight; y += 1 ) {
										for ( int x = 0; x < nMipWidth; x += 1 ) {
											uint8 const* pData1a = pTexture1->ImageData( iFrame, iCubeFace, iMipLevel, x, y, z );
											uint8 const* pData2a = pTexture2->ImageData( iFrame, iCubeFace, iMipLevel, x, y, z );

											if ( memcmp( pData1a, pData2a, ImageLoader::SizeInBytes( pTexture1->Format() ) ) ) {
												printf( "Frame %d Mip level %d Face %d Z-slice %d texel (%d,%d) different!\n", iFrame, iMipLevel, iCubeFace, z, x, y );
												bBreak = true;
												break;
											}
										}

										if ( bBreak ) {
											break;
										}
									}
								}
							}
						}
					}
				}
			}

			bMatch = false;
		}
	}

	// Lowres data
	{
		int iDummy, iSize1, iSize2;
		pTexture1->LowResFileInfo( &iDummy, &iSize1 );
		pTexture2->LowResFileInfo( &iDummy, &iSize2 );

		if ( iSize1 != iSize2 ) {
			printf( "%s differing low res image data size: %d != %d\n", argv[ 1 ], iSize1, iSize2 );
			bMatch = false;
		}

		if ( bMatch ) {
			if ( memcmp( pTexture1->LowResImageData(), pTexture2->LowResImageData(), iSize1 ) != 0 ) {
				printf( "%s differing low res image data\n", argv[ 1 ] );
				bMatch = false;
			}
		}
	}

	// Check other resources
	{
		int numRes1 = pTexture1->GetResourceTypes( nullptr, 0 );
		int numRes2 = pTexture2->GetResourceTypes( nullptr, 0 );

		// List of resource types checked or insignificant diffs
		using MapResTypes = CUtlMap<int, bool>;
		MapResTypes mapTypes( DefLessFunc( int ) );
		mapTypes.Insert( VTF_LEGACY_RSRC_LOW_RES_IMAGE, true );
		mapTypes.Insert( VTF_LEGACY_RSRC_IMAGE, true );
		mapTypes.Insert( MK_VTF_RSRC_ID( 'C', 'R', 'C' ), true );

		auto puiresbuffer = static_cast<uint32*>( stackalloc( ( numRes1 + numRes2 ) * sizeof( uint32 ) ) );

		int arrNums[ 2 ] = { numRes1, numRes2 };

		for ( int itx = 0; itx < 2; ++itx ) {
			arrTextures[ itx ]->GetResourceTypes( puiresbuffer, arrNums[ itx ] );
			while ( arrNums[ itx ]-- > 0 ) {
				uint32 uiResType = puiresbuffer[ arrNums[ itx ] ];
				if ( mapTypes.Find( uiResType ) != mapTypes.InvalidIndex() ) {
					continue;
				}

				mapTypes.Insert( uiResType, true );

				size_t numBytes1, numBytes2;
				void const* pvResData1 = pTexture1->GetResourceData( uiResType, &numBytes1 );
				void const* pvResData2 = pTexture2->GetResourceData( uiResType, &numBytes2 );

				if ( not pvResData1 != not pvResData2 ) {
					printf( "%s different resource %s %s\n", argv[ 1 ], ResourceToString( uiResType ), pvResData1 ? "present" : "missing" );
					bMatch = false;
				} else if ( numBytes1 != numBytes2 ) {
					printf( "%s different resource %s size %lld != %lld\n", argv[ 1 ], ResourceToString( uiResType ), static_cast<long long>( numBytes1 ), static_cast<long long>( numBytes2 ) );
					bMatch = false;
				} else if ( memcmp( pvResData1, pvResData2, numBytes1 ) != 0 ) {
					printf( "%s different resource %s data\n", argv[ 1 ], ResourceToString( uiResType ) );
					bMatch = false;
				}
			}
		}
	}


	if ( bMatch ) {
		return 0;
	}
	return 1;
}
