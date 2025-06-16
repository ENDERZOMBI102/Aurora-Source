//
// Created by ENDERZOMBI102 on 03/09/2024.
//
#include "gameapploader.hpp"
#include "appframework/AppFramework.h"
#include "datacache/idatacache.h"
#include "engine/hlds_api.h"
#include "engine/launcher_api.hpp"
#include "filesystem.h"
#include "filesystem/IQueuedLoader.h"
#include "filesystem_init.h"
#include "icommandline.h"
#include "inputsystem/iinputsystem.h"
#include "istudiorender.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/materialsystem_config.h"
#include "tier3/tier3.h"
#include "vphysics_interface.h"
#include "vstdlib/cvar.h"
#include "vstdlib/iprocessutils.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "vgui/IPanel.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"
#include "avi/iavi.h"
#include "SDL_video.h"
// This must be the final include in a .cpp file!!!
#include "memdbgon.h"

#include <SDL_version.h>


IFileSystem* g_pFileSystem{nullptr};
namespace {
	char s_BaseDir[ MAX_PATH ];
	char s_GameInfoDir[ MAX_PATH ];
	CDedicatedExports s_DedicatedExports{};
	IDedicatedServerAPI* s_DedicatedApi{nullptr};
	ILauncherAPI* s_LauncherApi{nullptr};
	IStudioDataCache* s_pStudioDataCache{nullptr};
	SDL_Window* s_Window{nullptr};
}

// ------------------
// CSteamAppLoader
// ------------------
bool CGameAppLoader::Create() {
	// are we running a dedicated server?
	m_Dedicated = CommandLine()->FindParm( "-dedicated" ) != 0;

	constexpr const char* vstdlib = []() constexpr -> const char* {
		if constexpr ( IsPosix() ) {
			return "libvstdlib";
		}
		return "vstdlib";
	}();

	// base dependencies
	AppSystemInfo_t appSystems[] {
		{ "filesystem_stdio"  , FILESYSTEM_INTERFACE_VERSION             },
		{ "engine"            , CVAR_QUERY_INTERFACE_VERSION             },
		// { vstdlib             , PROCESS_UTILS_INTERFACE_VERSION          },

		// { "filesystem_stdio"  , QUEUEDLOADER_INTERFACE_VERSION           },

		{ "inputsystem"       , INPUTSYSTEM_INTERFACE_VERSION            },

		{ "vphysics"          , VPHYSICS_INTERFACE_VERSION               },
		{ "materialsystem"    , MATERIAL_SYSTEM_INTERFACE_VERSION        },

		{ "datacache"         , DATACACHE_INTERFACE_VERSION              },
		{ "datacache"         , MDLCACHE_INTERFACE_VERSION               },
		{ "datacache"         , STUDIO_DATA_CACHE_INTERFACE_VERSION      },

		{ "studiorender"      , STUDIO_RENDER_INTERFACE_VERSION          },
		{ "soundemittersystem", SOUNDEMITTERSYSTEM_INTERFACE_VERSION     },

		// { "valve_avi"         , AVI_INTERFACE_VERSION                    },

		{ "vguimatsurface"    , VGUI_SURFACE_INTERFACE_VERSION           },

		{ "vgui2"             , VGUI_PANEL_INTERFACE_VERSION             },
		{ "vgui2"             , VGUI_IVGUI_INTERFACE_VERSION             },

		{ "engine"            , VENGINE_LAUNCHER_API_VERSION             },
		{ nullptr, nullptr }
	};
	if ( not AddSystems( appSystems ) ) {
		return false;
	}

	// TODO: Re-add dedicated server support
	if ( m_Dedicated ) {
		// the following are only needed for the dedicated (for now, gotta research more)
		Assert( AddSystem( LoadModule( "engine" ), VENGINE_HLDS_API_VERSION ) );
	}

	// set the shader API
	if ( auto* matSys = FindSystem<IMaterialSystem>( MATERIAL_SYSTEM_INTERFACE_VERSION ) ) {
		auto loadEmpty{ m_Dedicated or CommandLine()->FindParm( "-noshaderapi" ) != 0 };
		g_pMaterialSystem = materials = matSys; // update globals too
		matSys->SetShaderAPI( loadEmpty ? "shaderapiempty" : "shaderapidx9" );
	}

	return true;
}
bool CGameAppLoader::PreInit() {
	auto factory{ GetFactory() };
	ConnectTier1Libraries( &factory, 1 );
	ConnectTier2Libraries( &factory, 1 );
	g_pMaterialSystem->Connect( factory );

	// Must be done after material system is connected up!
	g_pMaterialSystemHardwareConfig = FindSystem<IMaterialSystemHardwareConfig>( MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION );
	if ( not g_pMaterialSystemHardwareConfig ) {
		return false;
	}

	// load globals
	g_pFullFileSystem = g_pFileSystem = FindSystem<IFileSystem>( FILESYSTEM_INTERFACE_VERSION );
	g_pQueuedLoader = FindSystem<IQueuedLoader>( QUEUEDLOADER_INTERFACE_VERSION );
	g_pStudioRender = FindSystem<IStudioRender>( STUDIO_RENDER_INTERFACE_VERSION );
	g_pDataCache = FindSystem<IDataCache>( DATACACHE_INTERFACE_VERSION );
	g_pMDLCache = FindSystem<IMDLCache>( MDLCACHE_INTERFACE_VERSION );
	s_LauncherApi = FindSystem<ILauncherAPI>( VENGINE_LAUNCHER_API_VERSION );
	// if ( m_Dedicated ) {
	// s_DedicatedApi = FindSystem<IDedicatedServerAPI>( VENGINE_HLDS_API_VERSION );
	// }

	if ( not g_pFullFileSystem or not g_pMaterialSystem or not s_LauncherApi ) {
		Error( "Unable to load EngineAPI!\n" );
		return false;
	}

	if ( not (g_pFileSystem and g_pMaterialSystem and g_pStudioRender and g_pMDLCache and (s_DedicatedApi or s_LauncherApi)) ) {
		Error( "Unable to load required library interface(s)!\n" );
		return false;
	}

	// init modules
	SetupSearchPaths( nullptr, false, false );

	MathLib_Init();
	g_pMaterialSystem->SetAdapter( 0, MATERIAL_INIT_ALLOCATE_FULLSCREEN_TEXTURE );
	g_pMaterialSystem->ModInit();

	// create the window
	s_Window = SDL_CreateWindow( "hl2", 800, 600, SDL_WINDOWPOS_CENTERED | SDL_WINDOW_HIGH_PIXEL_DENSITY );
	void* hwnd;
	#if IsWindows()
		hwnd = SDL_GetProperty( SDL_GetWindowProperties( s_Window ), SDL_PROPERTY_WINDOW_WIN32_HWND_POINTER, nullptr );
	#elif IsPosix()
		if ( strcmp( SDL_GetCurrentVideoDriver(), "x11" ) == 0 ) {
			hwnd = reinterpret_cast<void*>( SDL_GetNumberProperty( SDL_GetWindowProperties( s_Window ), SDL_PROPERTY_WINDOW_X11_WINDOW_NUMBER, 0 ) );
		} else if ( strcmp( SDL_GetCurrentVideoDriver(), "wayland" ) == 0 ) {
			hwnd = SDL_GetProperty( SDL_GetWindowProperties( s_Window ), SDL_PROPERTY_WINDOW_WAYLAND_SURFACE_POINTER, nullptr );
		}
	#endif
	Assert( hwnd );
	g_pMaterialSystem->SetView( hwnd );

	// update matsys config
	const MaterialSystem_Config_t config = g_pMaterialSystem->GetCurrentConfigForVideoCard();
	g_pMaterialSystem->OverrideConfig( config, false );

	return true;
}
int CGameAppLoader::Main() {
	FileSystem_GetExecutableDir( s_BaseDir, MAX_PATH );
	V_StripLastDir( s_BaseDir, MAX_PATH );
	V_StripTrailingSlash( s_BaseDir );

	ModInfo_t modInfo{
		.m_pInstance = nullptr,
		.m_pBaseDirectory = s_BaseDir,
		.m_pInitialMod = s_GameInfoDir,
		.m_pInitialGame = "hl2",
		.m_pParentAppSystemGroup = this,
		.m_bTextMode = true
	};

	if ( m_Dedicated ) {
		s_DedicatedApi->ModInit( modInfo );
		return 0;
	}

	s_LauncherApi->SetStartupInfo( &modInfo );
	return s_LauncherApi->Run();
}
void CGameAppLoader::PostShutdown() {
	g_pMaterialSystem->ModShutdown();
}
void CGameAppLoader::Destroy() {
	DisconnectTier1Libraries();
	DisconnectTier2Libraries();

	SDL_DestroyWindow( s_Window );
	g_pFileSystem = nullptr;
	g_pMaterialSystem = nullptr;
}


// -------------------
// CDedicatedExports
// -------------------
void CDedicatedExports::Sys_Printf( char* text ) {
	// Maybe add logging?
	puts( text );
}

void CDedicatedExports::RunServer() {
	// Main Server loop
	for ( ;; ) {
		s_DedicatedApi->RunFrame();
	}
}
