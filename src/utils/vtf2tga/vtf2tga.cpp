//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//
#include "bitmap/tgawriter.h"
#include "filesystem.h"
#include "mathlib/mathlib.h"
#include "tier0/dbg.h"
#include "tier0/icommandline.h"
#include "tier1/strtools.h"
#include "tier1/utlbuffer.h"
#include "tier2/tier2.h"
#include "vtf/vtf.h"


//-----------------------------------------------------------------------------
// HDRFIXME: move this somewhere else.
//-----------------------------------------------------------------------------
static void PFMWrite( const float* pFloatImage, const char* pFilename, const int width, const int height ) {
	FILE* fp = fopen( pFilename, "wb" );
	fprintf( fp, "PF\n%d %d\n-1.000000\n", width, height );
	for ( int i = height - 1; i >= 0; i -= 1 ) {
		const float* pRow = &pFloatImage[ 3 * width * i ];
		fwrite( pRow, width * sizeof( float ) * 3, 1, fp );
	}
	fclose( fp );
}

static SpewRetval_t VTF2TGAOutputFunc( const SpewType_t spewType, char const* pMsg ) {
	printf( "%s", pMsg );
	fflush( stdout );

	if ( spewType == SPEW_ERROR ) {
		return SPEW_ABORT;
	}
	return spewType == SPEW_ASSERT ? SPEW_DEBUGGER : SPEW_CONTINUE;
}

static void Usage() {
	Error( "Usage: vtf2tga -i <input vtf> [-o <output tga>] [-mip]\n" );
	exit( -1 );
}

int main( const int argc, char** argv ) {
	SpewOutputFunc( VTF2TGAOutputFunc );
	CommandLine()->CreateCmdLine( argc, argv );
	MathLib_Init( 2.2f, 2.2f, 0.0f, 1.0f, false, false, false, false );
	InitDefaultFileSystem();

	const char* pVTFFileName = CommandLine()->ParmValue( "-i" );
	const char* pTGAFileName = CommandLine()->ParmValue( "-o" );
	const bool bGenerateMipLevels = CommandLine()->CheckParm( "-mip" ) != nullptr;
	if ( not pVTFFileName ) {
		Usage();
	}

	if ( not pTGAFileName ) {
		pTGAFileName = pVTFFileName;
	}

	char pCurrentDirectory[ MAX_PATH ];
	if ( _getcwd( pCurrentDirectory, sizeof( pCurrentDirectory ) ) == nullptr ) {
		fprintf( stderr, "Unable to get the current directory\n" );
		return -1;
	}
	Q_StripTrailingSlash( pCurrentDirectory );

	char pBuf[ MAX_PATH ];
	if ( not Q_IsAbsolutePath( pTGAFileName ) ) {
		Q_snprintf( pBuf, sizeof( pBuf ), "%s\\%s", pCurrentDirectory, pTGAFileName );
	} else {
		Q_strncpy( pBuf, pTGAFileName, sizeof( pBuf ) );
	}
	Q_FixSlashes( pBuf );

	char pOutFileNameBase[ MAX_PATH ];
	Q_StripExtension( pBuf, pOutFileNameBase, MAX_PATH );

	char pActualVTFFileName[ MAX_PATH ];
	Q_strncpy( pActualVTFFileName, pVTFFileName, MAX_PATH );
	if ( not Q_strstr( pActualVTFFileName, ".vtf" ) ) {
		Q_strcat( pActualVTFFileName, ".vtf", MAX_PATH );
	}

	FILE* vtfFp = fopen( pActualVTFFileName, "rb" );
	if ( not vtfFp ) {
		Error( "Can't open %s\n", pActualVTFFileName );
		exit( -1 );
	}

	fseek( vtfFp, 0, SEEK_END );
	const int srcVTFLength = ftell( vtfFp );
	fseek( vtfFp, 0, SEEK_SET );

	CUtlBuffer buf;
	buf.EnsureCapacity( srcVTFLength );
	const int nBytesRead = fread( buf.Base(), 1, srcVTFLength, vtfFp );
	fclose( vtfFp );
	buf.SeekPut( CUtlBuffer::SEEK_HEAD, nBytesRead );

	IVTFTexture* pTex = CreateVTFTexture();
	if ( not pTex->Unserialize( buf ) ) {
		Error( "*** Error reading in .VTF file %s\n", pActualVTFFileName );
		exit( -1 );
	}

	Msg( "vtf width: %d\n", pTex->Width() );
	Msg( "vtf height: %d\n", pTex->Height() );
	Msg( "vtf numFrames: %d\n", pTex->FrameCount() );

	Msg( "TEXTUREFLAGS_POINTSAMPLE=%s\n", ( pTex->Flags() & TEXTUREFLAGS_POINTSAMPLE ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_TRILINEAR=%s\n", ( pTex->Flags() & TEXTUREFLAGS_TRILINEAR ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_CLAMPS=%s\n", ( pTex->Flags() & TEXTUREFLAGS_CLAMPS ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_CLAMPT=%s\n", ( pTex->Flags() & TEXTUREFLAGS_CLAMPT ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_CLAMPU=%s\n", ( pTex->Flags() & TEXTUREFLAGS_CLAMPU ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_BORDER=%s\n", ( pTex->Flags() & TEXTUREFLAGS_BORDER ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_ANISOTROPIC=%s\n", ( pTex->Flags() & TEXTUREFLAGS_ANISOTROPIC ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_HINT_DXT5=%s\n", ( pTex->Flags() & TEXTUREFLAGS_HINT_DXT5 ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_SRGB=%s\n", ( pTex->Flags() & TEXTUREFLAGS_SRGB ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_NORMAL=%s\n", ( pTex->Flags() & TEXTUREFLAGS_NORMAL ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_NOMIP=%s\n", ( pTex->Flags() & TEXTUREFLAGS_NOMIP ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_NOLOD=%s\n", ( pTex->Flags() & TEXTUREFLAGS_NOLOD ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_ALL_MIPS=%s\n", ( pTex->Flags() & TEXTUREFLAGS_ALL_MIPS ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_PROCEDURAL=%s\n", ( pTex->Flags() & TEXTUREFLAGS_PROCEDURAL ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_ONEBITALPHA=%s\n", ( pTex->Flags() & TEXTUREFLAGS_ONEBITALPHA ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_EIGHTBITALPHA=%s\n", ( pTex->Flags() & TEXTUREFLAGS_EIGHTBITALPHA ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_ENVMAP=%s\n", ( pTex->Flags() & TEXTUREFLAGS_ENVMAP ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_RENDERTARGET=%s\n", ( pTex->Flags() & TEXTUREFLAGS_RENDERTARGET ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_DEPTHRENDERTARGET=%s\n", ( pTex->Flags() & TEXTUREFLAGS_DEPTHRENDERTARGET ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_NODEBUGOVERRIDE=%s\n", ( pTex->Flags() & TEXTUREFLAGS_NODEBUGOVERRIDE ) ? "true" : "false" );
	Msg( "TEXTUREFLAGS_SINGLECOPY=%s\n", ( pTex->Flags() & TEXTUREFLAGS_SINGLECOPY ) ? "true" : "false" );

	Vector vecReflectivity = pTex->Reflectivity();
	Msg( "vtf reflectivity: %f %f %f\n", vecReflectivity[ 0 ], vecReflectivity[ 1 ], vecReflectivity[ 2 ] );
	Msg( "transparency: " );
	if ( pTex->Flags() & TEXTUREFLAGS_EIGHTBITALPHA ) {
		Msg( "eightbitalpha\n" );
	} else if ( pTex->Flags() & TEXTUREFLAGS_ONEBITALPHA ) {
		Msg( "onebitalpha\n" );
	} else {
		Msg( "noalpha\n" );
	}
	const ImageFormat srcFormat = pTex->Format();
	Msg( "vtf format: %s\n", ImageLoader::GetName( srcFormat ) );

	const int iTGANameLen = Q_strlen( pOutFileNameBase );

	const int iFaceCount = pTex->FaceCount();
	const int nFrameCount = pTex->FrameCount();
	const bool bIsCubeMap = pTex->IsCubeMap();

	const int iLastMipLevel = bGenerateMipLevels ? pTex->MipCount() - 1 : 0;
	for ( int iFrame = 0; iFrame < nFrameCount; iFrame += 1 ) {
		for ( int iMipLevel = 0; iMipLevel <= iLastMipLevel; iMipLevel += 1 ) {
			int iWidth, iHeight, iDepth;
			pTex->ComputeMipLevelDimensions( iMipLevel, &iWidth, &iHeight, &iDepth );

			for ( int iCubeFace = 0; iCubeFace < iFaceCount; iCubeFace += 1 ) {
				for ( int z = 0; z < iDepth; z += 1 ) {
					// Construct output filename
					char* pTempNameBuf = new char[ iTGANameLen + 13 ]; //(char *)stackalloc( iTGANameLen + 13 );
					Q_strncpy( pTempNameBuf, pOutFileNameBase, iTGANameLen + 1 );
					char* pExt = Q_strrchr( pTempNameBuf, '.' );
					if ( pExt ) {
						pExt = nullptr;
					}

					if ( bIsCubeMap ) {
						Assert( pTex->Depth() == 1 ); // shouldn't this be 1 instead of 0?
						static const char* pCubeFaceName[ 7 ] = { "rt", "lf", "bk", "ft", "up", "dn", "sph" };
						Q_strcat( pTempNameBuf, pCubeFaceName[ iCubeFace ], iTGANameLen + 13 );
					}

					if ( nFrameCount > 1 ) {
						char pTemp[ 4 ];
						Q_snprintf( pTemp, 4, "%03d", iFrame );
						Q_strcat( pTempNameBuf, pTemp, iTGANameLen + 13 );
					}

					if ( iLastMipLevel != 0 ) {
						char pTemp[ 8 ];
						Q_snprintf( pTemp, 8, "_mip%d", iMipLevel );
						Q_strcat( pTempNameBuf, pTemp, iTGANameLen + 13 );
					}

					if ( pTex->Depth() > 1 ) {
						char pTemp[ 6 ];
						Q_snprintf( pTemp, 6, "_z%03d", z );
						Q_strcat( pTempNameBuf, pTemp, iTGANameLen + 13 );
					}

					if ( srcFormat == IMAGE_FORMAT_RGBA16161616F ) {
						Q_strcat( pTempNameBuf, ".pfm", iTGANameLen + 13 );
					} else {
						Q_strcat( pTempNameBuf, ".tga", iTGANameLen + 13 );
					}

					uint8* pSrcImage = pTex->ImageData( iFrame, iCubeFace, iMipLevel, 0, 0, z );

					ImageFormat dstFormat;
					if ( srcFormat == IMAGE_FORMAT_RGBA16161616F ) {
						dstFormat = IMAGE_FORMAT_RGB323232F;
					} else {
						if ( ImageLoader::IsTransparent( srcFormat ) || ( srcFormat == IMAGE_FORMAT_ATI1N ) || ( srcFormat == IMAGE_FORMAT_ATI2N ) ) {
							dstFormat = IMAGE_FORMAT_BGRA8888;
						} else {
							dstFormat = IMAGE_FORMAT_BGR888;
						}
					}
					//	dstFormat = IMAGE_FORMAT_RGBA8888;
					//	dstFormat = IMAGE_FORMAT_RGB888;
					//	dstFormat = IMAGE_FORMAT_BGRA8888;
					//	dstFormat = IMAGE_FORMAT_BGR888;
					//	dstFormat = IMAGE_FORMAT_BGRA5551;
					//	dstFormat = IMAGE_FORMAT_BGR565;
					//	dstFormat = IMAGE_FORMAT_BGRA4444;
					//	printf( "dstFormat: %s\n", ImageLoader::GetName( dstFormat ) );
					auto pDstImage = new uint8[ ImageLoader::GetMemRequired( iWidth, iHeight, 1, dstFormat, false ) ];
					if ( not ImageLoader::ConvertImageFormat( pSrcImage, srcFormat, pDstImage, dstFormat, iWidth, iHeight, 0, 0 ) ) {
						Error( "Error converting from %s to %s\n", ImageLoader::GetName( srcFormat ), ImageLoader::GetName( dstFormat ) );
						exit( -1 );
					}

					if ( dstFormat != IMAGE_FORMAT_RGB323232F ) {
						if ( ImageLoader::IsTransparent( dstFormat ) && ( dstFormat != IMAGE_FORMAT_RGBA8888 ) ) {
							uint8* tmpImage = pDstImage;
							pDstImage = new uint8[ ImageLoader::GetMemRequired( iWidth, iHeight, 1, IMAGE_FORMAT_RGBA8888, false ) ];
							if ( not ImageLoader::ConvertImageFormat( tmpImage, dstFormat, pDstImage, IMAGE_FORMAT_RGBA8888, iWidth, iHeight, 0, 0 ) ) {
								Error( "Error converting from %s to %s\n", ImageLoader::GetName( dstFormat ), ImageLoader::GetName( IMAGE_FORMAT_RGBA8888 ) );
							}
							dstFormat = IMAGE_FORMAT_RGBA8888;
						} else if ( not ImageLoader::IsTransparent( dstFormat ) && ( dstFormat != IMAGE_FORMAT_RGB888 ) ) {
							uint8* tmpImage = pDstImage;
							pDstImage = new uint8[ ImageLoader::GetMemRequired( iWidth, iHeight, 1, IMAGE_FORMAT_RGB888, false ) ];
							if ( not ImageLoader::ConvertImageFormat( tmpImage, dstFormat, pDstImage, IMAGE_FORMAT_RGB888, iWidth, iHeight, 0, 0 ) ) {
								Error( "Error converting from %s to %s\n", ImageLoader::GetName( dstFormat ), ImageLoader::GetName( IMAGE_FORMAT_RGB888 ) );
							}
							dstFormat = IMAGE_FORMAT_RGB888;
						}

						CUtlBuffer outBuffer;
						TGAWriter::WriteToBuffer( pDstImage, outBuffer, iWidth, iHeight, dstFormat, dstFormat );
						if ( not g_pFullFileSystem->WriteFile( pTempNameBuf, nullptr, outBuffer ) ) {
							fprintf( stderr, "unable to write %s\n", pTempNameBuf );
						}
					} else {
						PFMWrite( reinterpret_cast<float*>( pDstImage ), pTempNameBuf, iWidth, iHeight );
					}

					delete[] pTempNameBuf;
				}
			}
		}
	}

	// leak leak leak leak leak, leak leak, leak leak (Blue Danube)
	return 0;
}
