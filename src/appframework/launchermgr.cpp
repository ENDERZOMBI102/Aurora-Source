//
// Created by ENDERZOMBI102 on 08/06/2025.
// 
#include "launchermgr.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

#include "tier0/icommandline.h"


#if defined( USE_SDL )
	namespace { CLauncherMgr s_LauncherMgr{}; }

	auto CLauncherMgr::Connect( CreateInterfaceFn factory ) -> bool {
		return true;
	}
	auto CLauncherMgr::Disconnect() -> void {
	}
	auto CLauncherMgr::QueryInterface( const char* pInterfaceName ) -> void* {
		if ( V_strcmp( pInterfaceName, SDLMGR_INTERFACE_VERSION ) == 0 ) {
			return this;
		}
		return nullptr;
	}
	auto CLauncherMgr::Init() -> InitReturnVal_t {
		const auto res{ SDL_InitSubSystem( SDL_INIT_VIDEO ) };
		if ( res < 0 ) {
			Warning( "[LauncherMgr] Failed to initialize SDL video subsystem (%s)\n", SDL_GetError() );
			return InitReturnVal_t::INIT_FAILED;
		}
		return InitReturnVal_t::INIT_OK;
	}
	auto CLauncherMgr::Shutdown() -> void {
	}

	auto CLauncherMgr::CreateGameWindow( const char* const pTitle, const bool pWindowed, const int pWidth, const int pHeight ) -> bool {
		uint32 flags{};
		if ( CommandLine()->FindParm( "-vulkan" ) ) {
			flags |= SDL_WINDOW_VULKAN;
		} else {
			#if defined( DX_TO_GL_ABSTRACTION )
				flags |= SDL_WINDOW_OPENGL;
			#endif
		}
		flags |= pWindowed ? 0 : SDL_WINDOW_FULLSCREEN;

		m_Window = SDL_CreateWindow( pTitle, pWidth, pHeight, flags );
		return m_Window != nullptr;
	}

	auto CLauncherMgr::IncWindowRefCount() -> void {
		m_WindowRefCount += 1;
	}
	auto CLauncherMgr::DecWindowRefCount() -> void {
		// TODO: Destroy window on reach 0?
		if ( m_WindowRefCount > 0 ) {
			m_WindowRefCount -= 1;
		}
	}

	auto CLauncherMgr::GetEvents( CCocoaEvent* pEvents, int nMaxEventsToReturn, bool debugEvents ) -> int {
		return {};
	}
	#if IsLinux()
		auto CLauncherMgr::PeekAndRemoveKeyboardEvents( bool* pbEsc, bool* pbReturn, bool* pbSpace, bool debugEvents ) -> int {
			return {};
		}
	#endif

	auto CLauncherMgr::SetCursorPosition( const int x, const int y ) -> void {
		if ( SDL_WarpMouseGlobal( x, y ) < 0 ) {
			Warning( V_STRINGIFY( $expr ) " failed: %s", SDL_GetError() );
		}
	}

	auto CLauncherMgr::SetWindowFullScreen( const bool pFullScreen, const int pWidth, const int pHeight ) -> void {
		m_Fullscreen = pFullScreen;
		if ( SDL_SetWindowFullscreen( m_Window, true ) < 0 ) {
			Warning( V_STRINGIFY( $expr ) " failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::IsWindowFullScreen() -> bool {
		return m_Fullscreen;
	}
	auto CLauncherMgr::MoveWindow( const int x, const int y ) -> void {
		if ( SDL_SetWindowPosition( m_Window, x, y ) < 0 ) {
			Warning( V_STRINGIFY( $expr ) " failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::SizeWindow( const int pWidth, const int pHeight ) -> void {
		if ( SDL_SetWindowSize( m_Window, pWidth, pHeight ) < 0 ) {
			Warning( V_STRINGIFY( $expr ) " failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::PumpWindowsMessageLoop() -> void {
	}

	auto CLauncherMgr::DestroyGameWindow() -> void {
		SDL_DestroyWindow( m_Window );
		m_Window = nullptr;
	}
	auto CLauncherMgr::SetApplicationIcon( const char* const pAppIconFile ) -> void {
		// open image
		const auto ops{ SDL_RWFromFile( pAppIconFile, "rb" ) };
		if ( not ops ) {
			Warning( "Failed to open icon at `%s`: %s", pAppIconFile, SDL_GetError() );
			return;
		}
		// load image
		const auto surface{ SDL_LoadBMP_RW( ops, true ) };
		if ( not surface ) {
			Warning( "Failed to load icon: %s", SDL_GetError() );
			return;
		}
		SDL_SetWindowIcon( m_Window, surface );
		SDL_DestroySurface( surface );
	}
	auto CLauncherMgr::GetMouseDelta( int& x, int& y, bool bIgnoreNextMouseDelta ) -> void {

	}

	auto CLauncherMgr::GetNativeDisplayInfo( int nDisplay, uint& nWidth, uint& nHeight, uint& nRefreshHz ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::RenderedSize( uint& width, uint& height, bool set ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::DisplayedSize( uint& width, uint& height ) -> void { AssertUnreachable(); }

	#if defined( DX_TO_GL_ABSTRACTION )
		auto CLauncherMgr::GetMainContext() -> PseudoGLContextPtr { AssertUnreachable(); return {}; }
		auto CLauncherMgr::GetGLContextForWindow( void* windowref ) -> PseudoGLContextPtr { AssertUnreachable(); return {}; }
		auto CLauncherMgr::CreateExtraContext() -> PseudoGLContextPtr { AssertUnreachable(); return {}; }
		auto CLauncherMgr::DeleteContext( PseudoGLContextPtr hContext ) -> void { AssertUnreachable(); }
		auto CLauncherMgr::MakeContextCurrent( PseudoGLContextPtr hContext ) -> bool { AssertUnreachable(); return {}; }
		auto CLauncherMgr::GetDisplayDB() -> GLMDisplayDB* { AssertUnreachable(); return {}; }
		auto CLauncherMgr::GetDesiredPixelFormatAttribsAndRendererInfo( uint** ptrOut, uint* countOut, GLMRendererInfoFields* rendInfoOut ) -> void { AssertUnreachable(); }
		auto CLauncherMgr::ShowPixels( CShowPixelsParams* params ) -> void { AssertUnreachable(); }
	#endif

	auto CLauncherMgr::GetStackCrawl( CStackCrawlParams* params ) -> void { AssertUnreachable(); }

	auto CLauncherMgr::WaitUntilUserInput( int msSleepTime ) -> void { AssertUnreachable(); }

	auto CLauncherMgr::GetWindowRef() -> void* { AssertUnreachable(); return {}; }

	auto CLauncherMgr::SetMouseVisible( bool bState ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::SetMouseCursor( SDL_Cursor* hCursor ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::SetForbidMouseGrab( bool bForbidMouseGrab ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::OnFrameRendered() -> void { AssertUnreachable(); }

	auto CLauncherMgr::SetGammaRamp( const uint16* pRed, const uint16* pGreen, const uint16* pBlue ) -> void { AssertUnreachable(); }

	auto CLauncherMgr::GetPrevGLSwapWindowTime() -> double { AssertUnreachable(); return {}; }

	ILauncherMgr* g_pLauncherMgr{ &s_LauncherMgr };
#endif