//
// Created by ENDERZOMBI102 on 22/07/2023.
//
#include "appframework/AppFramework.h"
#include "gameapploader.hpp"
#include "tier0/icommandline.h"
// This must be the final include in a .cpp file!!!
#include "memdbgon.h"


SpewRetval_t LauncherSpewFunc( SpewType_t pSpewType, char const* pMsg );
void LockSourceMutex();

//-----------------------------------------------------------------------------
//   Main entry point
//-----------------------------------------------------------------------------
DLL_EXPORT int LauncherMain( const int argc, char* argv[] ) {
	// always use the same locale, prevents some character issues
	setlocale( LC_ALL, "en_US.UTF_8" );
	if ( const char* res = setlocale( LC_ALL, nullptr ); strcmp( res, "en_US.UTF_8" ) != 0 ) {
		Warning( "failed to set locale; using system locale `%s`. Unicode characters may not work.\n", res );
	}

	// check if we got asked to rest a bit before continuing
	for ( int i{}; i < argc; i += 1 ) {
		if ( strcmp( argv[i], "-sleepatstartup" ) == 0 ) {
			sleep( 5 );
			break;
		}
	}

	// first init the CommandLine
	CommandLine()->CreateCmdLine( argc, argv );

	// then set the Spew function, so we can log stuff as soon as possible
	SpewOutputFunc( LauncherSpewFunc );

	// are we in a debug session?
	if ( Plat_IsInDebugSession() ) {
		Log( "running with debugger attached!\n" );
	}

	// verify hardware key
	if ( not Plat_VerifyHardwareKey() ) {
		return 0;
	}

	// check for unsupported args
	static constexpr const char* unsupported[] { "-vcrplayback", "-vcrrecord", };
	for ( const auto* arg : unsupported ) {
		if ( CommandLine()->FindParm( arg ) ) {
			Warning( "Argument `%s` is not supported! will be ignored.\n", arg );
		}
	}

	// check we have a game in our hands
	if ( not CommandLine()->FindParm( "-game" ) ) {
		Warning( "was not given a game to load!! defaulting to `Half-Life 2`" );
		CommandLine()->AppendParm( "-game", "hl2" );
	}

	// then init and launch Source
	CGameAppLoader loader{};
	CSteamApplication app{ &loader };
	return app.Run();
}

SpewRetval_t LauncherSpewFunc( const SpewType_t pSpewType, const char* const pMsg ) {
	switch ( pSpewType ) {
		case SPEW_MESSAGE:
			printf( "[I] %s", pMsg );
			break;
		case SPEW_WARNING:
			printf( "[W] %s", pMsg );
			break;
		case SPEW_ASSERT:
			printf( "[assert] %s", pMsg );
			break;
		case SPEW_ERROR:
			printf( "[E] %s", pMsg );
			break;
		case SPEW_LOG:
			printf( "[D] %s", pMsg );
			break;
		case SPEW_TYPE_COUNT:
			break;
	}
	return SpewRetval_t::SPEW_CONTINUE;
}
