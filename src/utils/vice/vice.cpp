//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Defines the entry point for the console application.
//
// $NoKeywords: $
//
//=============================================================================//
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tier0/platform.h"
#include "cmdlib.h"
#include "tier0/dbg.h"
#include "tier0/icommandline.h"
#include "tier1/strtools.h"
#include "tier1/utlbuffer.h"
#include "filesystem_tools.h"
#include "mathlib/IceKey.h"


#define FF_TRYAGAIN 1
#define FF_DONTPROCESS 2

static bool g_NoPause = false;
static bool g_Quiet = false;
static bool g_Encrypt = false;
static bool g_Decrypt = false;
static char g_ICEKey[ 16 ];
static char g_Extension[ 16 ];

static void Pause() {
	if ( not g_NoPause ) {
		printf( "Hit a key to continue\n" );
		getchar();
	}
}

static void Exit( const char* msg ) {
	fprintf( stderr, "%s", msg );
	Pause();
	exit( -1 );
}

static void Usage() {
	fprintf( stderr, "Usage: vice [-quiet] [-nopause] [-encrypt key] [-decrypt key] [-newext name] file file2 . . .\n" );
	fprintf( stderr, "-quiet   : don't print anything out, don't pause for input\n" );
	fprintf( stderr, "-nopause : don't pause for input\n" );
	fprintf( stderr, "-encrypt : encrypt files with given key\n" );
	fprintf( stderr, "-decrypt : decypt files with given key\n" );
	fprintf( stderr, "-newext  : new output file extension\n" );
	Pause();
	exit( -1 );
}


bool Process_File( char* pInputBaseName, int maxlen ) {
	Q_FixSlashes( pInputBaseName, '/' );
	// Q_StripExtension( pInputBaseName, pInputBaseName, maxlen );

	if ( !g_Quiet ) {
		printf( "input file: %s\n", pInputBaseName );
	}

	FileHandle_t f = g_pFullFileSystem->Open( pInputBaseName, "rb", "vice" );

	if ( !f )
		Error( "Could not open input file" );

	int fileSize = g_pFullFileSystem->Size( f );

	unsigned char* buffer = static_cast<unsigned char*>( _alloca( fileSize ) );

	g_pFullFileSystem->Read( buffer, fileSize, f ); // read into local buffer
	g_pFullFileSystem->Close( f ); // close file after reading

	IceKey ice( 0 ); // level 0 = 64bit key
	ice.set( reinterpret_cast<unsigned char*>( g_ICEKey ) ); // set key

	int blockSize = ice.blockSize();

	unsigned char* temp = static_cast<unsigned char*>( _alloca( fileSize ) );
	unsigned char* p1 = buffer;
	unsigned char* p2 = temp;

	// encrypt data in 8 byte blocks
	int bytesLeft = fileSize;
	while ( bytesLeft >= blockSize ) {
		if ( g_Encrypt ) {
			ice.encrypt( p1, p2 );
		} else if ( g_Decrypt ) {
			ice.decrypt( p1, p2 );
		} else {
			memcpy( p2, p1, blockSize );
		}

		bytesLeft -= blockSize;
		p1 += blockSize;
		p2 += blockSize;
	}

	memcpy( p2, p1, bytesLeft );

	Q_SetExtension( pInputBaseName, g_Extension, maxlen );

	if ( not g_Quiet ) {
		printf( "output file: %s\n", pInputBaseName );
	}

	f = g_pFullFileSystem->Open( pInputBaseName, "wb", "vice" );

	if ( not f ) {
		Exit( "Could not open output file" );
	}

	g_pFullFileSystem->Write( temp, fileSize, f ); // read into local buffer
	g_pFullFileSystem->Close( f ); // close file after reading

	return true;
}

int main( int argc, char* argv[] ) {
	CommandLine()->CreateCmdLine( argc, argv );

	if ( argc < 2 ) {
		Usage();
	}
	char* pInputBaseName = nullptr;
	int i = 1;
	strcpy( g_Extension, ".dat" );
	while ( i < argc ) {
		if ( stricmp( argv[ i ], "-quiet" ) == 0 ) {
			i += 1;
			g_Quiet = true;
			g_NoPause = true; // no point in pausing if we aren't going to print anything out.
		}
		if ( stricmp( argv[ i ], "-nopause" ) == 0 ) {
			i += 1;
			g_NoPause = true;
		}
		if ( stricmp( argv[ i ], "-encrypt" ) == 0 ) {
			g_Encrypt = true;
			i += 1;

			if ( strlen( argv[ i ] ) != 8 ) {
				Exit( "Error - ICE key must be a 8 char text.\n" );
			}

			Q_strncpy( g_ICEKey, argv[ i ], sizeof( g_ICEKey ) );
			i += 1;
		}
		if ( stricmp( argv[ i ], "-decrypt" ) == 0 ) {
			g_Decrypt = true;
			i += 1;

			if ( strlen( argv[ i ] ) != 8 ) {
				Exit( "Error - ICE key must be a 8 char text.\n" );
			}

			Q_strncpy( g_ICEKey, argv[ i ], sizeof( g_ICEKey ) );
			i += 1;
		}
		if ( stricmp( argv[ i ], "-newext" ) == 0 ) {
			i += 1;

			if ( strlen( argv[ i ] ) > 5 ) {
				Exit( "Error - extension must be smaller than 4 chars.\n" );
			}

			Q_strncpy( g_Extension, argv[ i ], sizeof( g_Extension ) );
			i += 1;

		} else {
			break;
		}
	}

	if ( i >= argc ) {
		Exit( "Error - missing files in commandline.\n" );
	}

	CmdLib_InitFileSystem( argv[ i ] );

	g_pFullFileSystem->GetCurrentDirectory( gamedir, sizeof( gamedir ) );
	g_pFullFileSystem->AddSearchPath( gamedir, "vice" );


	Q_FixSlashes( gamedir, '/' );

	for ( ; i < argc; i += 1 ) {
		pInputBaseName = argv[ i ];
		int maxlen = Q_strlen( pInputBaseName ) + 1;


		if ( strstr( pInputBaseName, "*." ) ) {
			char search[ MAX_PATH ];
			char fname[ MAX_PATH ];

			const char* name{ V_GetFileName( pInputBaseName ) };
			const char* ext{ V_GetFileExtension( name ) };  // find extension wanted
			AssertMsg( ext, "A given file doesn't have an extension!" );
			std::ranges::copy( name, ext - 1, fname );
			fname[ strlen( fname ) - 1 ] = 0; // remove *

			sprintf( search, "%s\\*%s", gamedir, ext );

			Q_FixSlashes( search, '/' );

			char buffer[MAX_PATH];

			FileFindHandle_t handle{};
			const char* path{ g_pFullFileSystem->FindFirstEx( search, "vice", &handle ) };
			for ( ; path; path = g_pFullFileSystem->FindNext( handle ) ) {
				if ( not strnicmp( fname, path, strlen( fname ) ) ) {
					V_strcpy_safe( buffer, path );
					if ( not Process_File( buffer, std::size( buffer ) ) ) {
						break;
					}
				}
			}
			g_pFullFileSystem->FindClose( handle );
		} else {
			Process_File( pInputBaseName, maxlen );
		}
	}

	Pause();
	return 0;
}

