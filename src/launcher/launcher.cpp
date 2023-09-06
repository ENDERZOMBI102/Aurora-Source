//
// Created by ENDERZOMBI102 on 22/07/2023.
//

#include "appframework/AppFramework.h"
#include "icommandline.h"
#include "launcher_ds.hpp"


//-----------------------------------------------------------------------------
//   Main entry point
//-----------------------------------------------------------------------------
DLL_EXPORT int LauncherMain( int argc, char* argv[] ) {
	CommandLine()->CreateCmdLine( argc, argv );

	if ( Plat_IsInDebugSession() )
		printf( "[I] running with debugger attached!" );

	if ( CommandLine()->FindParm( "-dedicated" ) != 0 ) {
		CLauncherDS launcherds{};
		CSteamApplication steamApplication( &launcherds );
		return steamApplication.Run();
	}


}
