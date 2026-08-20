//
// Created by ENDERZOMBI102 on 03/08/2026.
//
#include "appframework/vguimatsysapp.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

#include "tier0/icommandline.h"
#include "filesystem.h"
#include "inputsystem/iinputsystem.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/materialsystem_config.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"


CVguiMatSysApp::CVguiMatSysApp() : BaseClass() {
	// do nothing uwu
}
auto CVguiMatSysApp::Create() -> bool {
	// vgui & dependencies
	AppSystemInfo_t infos[] {
		{ .m_pModuleName = "inputsystem", .m_pInterfaceName = IInputSystem::INTERFACE_VERSION },
		{ .m_pModuleName = "materialsystem", .m_pInterfaceName = IMaterialSystem::INTERFACE_VERSION },
		{ .m_pModuleName = "vguimatsurface", .m_pInterfaceName = vgui::ISurface::INTERFACE_VERSION },
		{ .m_pModuleName = "vgui2", .m_pInterfaceName = vgui::IVGui::INTERFACE_VERSION },
		{ },
	};
	if ( not this->AddSystems( infos ) ) {
		return false;
	}

	// verify we got matsys
	g_pMaterialSystem = materials = this->FindSystem<IMaterialSystem>();
	if ( not g_pMaterialSystem ) {
		Warning( "Failed to find necessary `IMaterialSystem` interface!\n" );
		return false;
	}

	// load the requested shader API
	const ICommandLine* const cmdline{ CommandLine() };
	const char* shaderDll{};
	if ( cmdline->FindParm( "-noshaderapi" ) != 0 ) {
		shaderDll = "shaderapiempty";
	} else {
		shaderDll = cmdline->ParmValue( "-shaderdll", "shaderapidx9" );
	}
	g_pMaterialSystem->SetShaderAPI( shaderDll );
	return true;
}
bool CVguiMatSysApp::PreInit() {
	if ( not BaseClass::PreInit() ) {
		return false;
	}

	// check if all systems were connected
	bool connectErr{ false };
	if ( g_pFullFileSystem == nullptr ) {
		Warning( "Failed to connect FileSystem!" );
		connectErr = true;
	}
	if ( g_pMaterialSystem == nullptr ) {
		Warning( "Failed to connect MaterialSystem!" );
		connectErr = true;
	}
	if ( g_pInputSystem == nullptr ) {
		Warning( "Failed to connect InputSystem!" );
		connectErr = true;
	}
	if ( g_pMatSystemSurface == nullptr ) {
		Warning( "Failed to connect MatSystemSurface!" );
		connectErr = true;
	}
	if ( connectErr ) {
		return false;
	}

	// load up SDL
	if ( not SDL_InitSubSystem( SDL_INIT_VIDEO ) ) {
		Warning( "Failed to init SDL: %s\n", SDL_GetError() );
		return false;
	}

	// load up arguments
	const ICommandLine* const cmdline{ CommandLine() };
	const bool fullscreen{ cmdline->FindParm( "-fullscreen" ) != 0 or cmdline->FindParm( "-full" ) != 0 };
	int width{ cmdline->ParmValue( "-width", 0 ) };
	if ( width == 0 ) {
		width = cmdline->ParmValue( "-w", 1024 );
	}
	int height{ cmdline->ParmValue( "-height", 0 ) };
	if ( height == 0 ) {
		height = cmdline->ParmValue( "-h", 768 );
	}
	const int adapter{ cmdline->ParmValue( "-adapter", 0 ) };
	const bool ref{ cmdline->FindParm( "-ref" ) != 0 };

	// create window
	m_HWnd = this->CreateAppWindow( "", not fullscreen, width, height );
	if ( m_HWnd == nullptr ) {
		return false;
	}

	// update material system
	MaterialSystem_Config_t config{ g_pMaterialSystem->GetCurrentConfigForVideoCard() };
	config.SetFlag( MATERIAL_INIT_REFERENCE_RASTERIZER, ref );
	g_pMaterialSystem->SetAdapter( adapter, config.m_Flags );

	return true;
}
void CVguiMatSysApp::PostShutdown() {


	SDL_QuitSubSystem( SDL_INIT_VIDEO );

	CVguiSteamApp::PostShutdown();
}
auto CVguiMatSysApp::GetAppWindow() -> void* {
	return m_HWnd;
}
auto CVguiMatSysApp::GetWindowWidth() const -> int {
	return  m_nWidth;
}
auto CVguiMatSysApp::GetWindowHeight() const -> int {
	return m_nHeight;
}
auto CVguiMatSysApp::AppPumpMessages() -> void {
	AssertUnreachable();
}
auto CVguiMatSysApp::SetVideoMode() -> bool {
	const ICommandLine* const cmdline{ CommandLine() };

	MaterialSystem_Config_t config{};
	config.SetFlag( MATSYS_VIDCFG_FLAGS_WINDOWED, cmdline->FindParm( "-fullscreen" ) != 0 or cmdline->FindParm( "-full" ) != 0 );
	config.SetFlag( MATSYS_VIDCFG_FLAGS_RESIZING, cmdline->FindParm( "-resizing" ) != 0 );
	config.SetFlag( MATSYS_VIDCFG_FLAGS_NO_WAIT_FOR_VSYNC, cmdline->FindParm( "-mat_vsync" ) != 0 );
	config.m_nAASamples = cmdline->ParmValue( "-mat_antialias", 1 );
	config.m_nAAQuality = cmdline->ParmValue( "-mat_aaquality", 0 );

	return g_pMaterialSystem->SetMode( m_HWnd, config );
}
auto CVguiMatSysApp::SetupSearchPaths( const char* pStartingDir, bool bOnlyUseStartingDir, bool bIsTool ) -> bool {
	// call og method, we want to add not replace
	if ( not CSteamAppSystemGroup::SetupSearchPaths( pStartingDir, bOnlyUseStartingDir, bIsTool ) ) {
		return false;
	}

	const char* const gameInfoPath{ this->GetGameInfoPath() };
	g_pFullFileSystem->AddSearchPath( gameInfoPath, "SKIN" );
	return true;
}
auto CVguiMatSysApp::CreateAppWindow( char const* pTitle, const bool pWindowed, const int pWidth, const int pHeight ) -> void* {
	uint32 flags{ SDL_WINDOW_HIGH_PIXEL_DENSITY };
	if constexpr ( IsPlatformOpenGL() ) {
		flags |= SDL_WINDOW_OPENGL;
	}
	if ( not pWindowed ) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	SDL_Window* const window{ SDL_CreateWindow( pTitle, pWidth, pHeight, flags ) };
	if ( window == nullptr ) {
		Error( "Failed to create window: %s\n", SDL_GetError() );
	}
	if ( not SDL_SetWindowPosition( window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED ) ) {
		Warning( "Failed to position window: %s\n", SDL_GetError() );
	}

	return m_HWnd = window;
}


