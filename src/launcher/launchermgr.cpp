//
// Created by ENDERZOMBI102 on 08/06/2025.
// 
#include "launchermgr.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

#include "tier0/icommandline.h"


#if defined( USE_SDL )
	auto CLauncherMgr::Connect( CreateInterfaceFn factory ) -> bool {
		return true;
	}
	auto CLauncherMgr::Disconnect() -> void { }
	auto CLauncherMgr::QueryInterface( const char* pInterfaceName ) -> void* {
		if ( V_strcmp( pInterfaceName, INTERFACE_VERSION ) == 0 ) {
			return this;
		}
		return nullptr;
	}
	auto CLauncherMgr::Init() -> InitReturnVal_t {
		if ( not SDL_InitSubSystem( SDL_INIT_VIDEO ) ) {
			Warning( "[LauncherMgr] Failed to initialize SDL video subsystem (%s)\n", SDL_GetError() );
			return INIT_FAILED;
		}
		return INIT_OK;
	}
	auto CLauncherMgr::Shutdown() -> void {
		SDL_QuitSubSystem( SDL_INIT_VIDEO );
	}

	auto CLauncherMgr::CreateGameWindow( const char* const pTitle, const bool pWindowed, const int pWidth, const int pHeight ) -> bool {
		uint32 flags{ SDL_WINDOWPOS_CENTERED | SDL_WINDOW_HIGH_PIXEL_DENSITY };
		if ( CommandLine()->FindParm( "-vulkan" ) ) {
			flags |= SDL_WINDOW_VULKAN;
		} else if constexpr ( IsPlatformOpenGL() ) {
			flags |= SDL_WINDOW_OPENGL;
		}
		flags |= pWindowed ? 0 : SDL_WINDOW_FULLSCREEN;

		m_Window = SDL_CreateWindow( pTitle, pWidth, pHeight, flags );

		// if we're on an ogl platform, also create the context
		// if constexpr ( IsPlatformOpenGL() ) {
			// m_MainContext = SDL_GL_CreateContext( m_Window );
			// AssertFatalMsg( m_MainContext, "Failed to create OGL context: %s\n", SDL_GetError() );
		// }

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
		if ( not SDL_WarpMouseGlobal( x, y ) ) {
			Warning( "SDL_WarpMouseGlobal failed: %s", SDL_GetError() );
		}
	}

	auto CLauncherMgr::SetWindowFullScreen( const bool pFullScreen, const int pWidth, const int pHeight ) -> void {
		m_Fullscreen = pFullScreen;
		if ( not SDL_SetWindowFullscreen( m_Window, true ) ) {
			Warning( "SDL_SetWindowFullscreen failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::IsWindowFullScreen() -> bool {
		return m_Fullscreen;
	}
	auto CLauncherMgr::MoveWindow( const int x, const int y ) -> void {
		if ( not SDL_SetWindowPosition( m_Window, x, y ) ) {
			Warning( "SDL_SetWindowPosition failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::SizeWindow( const int pWidth, const int pHeight ) -> void {
		if ( not SDL_SetWindowSize( m_Window, pWidth, pHeight ) ) {
			Warning( "SDL_SetWindowSize failed: %s", SDL_GetError() );
		}
	}
	auto CLauncherMgr::PumpWindowsMessageLoop() -> void {
		SDL_PumpEvents();
	}

	auto CLauncherMgr::DestroyGameWindow() -> void {
		SDL_DestroyWindow( m_Window );
		m_Window = nullptr;
	}
	auto CLauncherMgr::SetApplicationIcon( const char* const pAppIconFile ) -> void {
		// open image
		const auto ops{ SDL_IOFromFile( pAppIconFile, "rb" ) };
		if ( not ops ) {
			Warning( "Failed to open icon at `%s`: %s", pAppIconFile, SDL_GetError() );
			return;
		}
		// load image
		const auto surface{ SDL_LoadBMP_IO( ops, true ) };
		if ( not surface ) {
			Warning( "Failed to load icon: %s", SDL_GetError() );
			return;
		}
		SDL_SetWindowIcon( m_Window, surface );
		SDL_DestroySurface( surface );
	}
	auto CLauncherMgr::GetMouseDelta( int& x, int& y, bool bIgnoreNextMouseDelta ) -> void {

	}

	auto CLauncherMgr::GetNativeDisplayInfo( int nDisplay, uint& nWidth, uint& nHeight, uint& nRefreshHz ) -> void {
		// get the IDs of the displays
		int32 count{0};
		const auto displayIDs{ SDL_GetDisplays( &count ) };
		// verify we have enough displays
		if ( nDisplay >= count ) {
			return;
		}

		// get requested data
		const auto display{ displayIDs[nDisplay] };
		SDL_Rect rect{};
		const auto res{ SDL_GetDisplayBounds( display, &rect ) };
		AssertMsg( res, "Failed to get display bounds: %s\n", SDL_GetError() );
		const auto mode{ SDL_GetCurrentDisplayMode( display ) };
		AssertMsg( mode, "Failed to get display mode: %s\n", SDL_GetError() );
		nWidth = rect.w;
		nHeight = rect.h;
		nRefreshHz = static_cast<uint>( mode->refresh_rate );
	}
	auto CLauncherMgr::RenderedSize( uint& oWidth, uint& oHeight, bool pSet ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::DisplayedSize( uint& oWidth, uint& oHeight ) -> void {
		// TODO: Is this correct?
		int width{};
		int height{};
		const auto res{ SDL_GetWindowSize( m_Window, &width, &height ) };
		AssertMsg( res, "Failed to get window mode: %s\n", SDL_GetError() );
		oWidth = width;
		oHeight = height;
	}

	#if defined( DX_TO_GL_ABSTRACTION )
		auto CLauncherMgr::GetMainContext() -> PseudoGLContextPtr {
			const auto ctx{ SDL_GL_GetCurrentContext() };
			AssertMsg( ctx, "Failed to get GL context: %s\n", SDL_GetError() );
			return ctx;
		}
		auto CLauncherMgr::GetGLContextForWindow( void* windowref ) -> PseudoGLContextPtr { AssertUnreachable(); return {}; }
		auto CLauncherMgr::CreateExtraContext() -> PseudoGLContextPtr { AssertUnreachable(); return {}; }
		auto CLauncherMgr::DeleteContext( PseudoGLContextPtr pContext ) -> void {
			const auto res{ SDL_GL_DestroyContext( static_cast<SDL_GLContext>( pContext ) ) };
			AssertMsg( res, "Failed to destroy GL context: %s\n", SDL_GetError() );
		}
		auto CLauncherMgr::MakeContextCurrent( const PseudoGLContextPtr pContext ) -> bool {
			return SDL_GL_MakeCurrent( m_Window, static_cast<SDL_GLContext>( pContext ) );
		}
		auto CLauncherMgr::GetDisplayDB() -> GLMDisplayDB* {
			return &m_DisplayDb;
		}
		auto CLauncherMgr::GetDesiredPixelFormatAttribsAndRendererInfo( uint** ptrOut, uint* countOut, GLMRendererInfoFields* rendInfoOut ) -> void { AssertUnreachable(); }
		auto CLauncherMgr::ShowPixels( CShowPixelsParams* params ) -> void { AssertUnreachable(); }
	#endif

	auto CLauncherMgr::GetStackCrawl( CStackCrawlParams* params ) -> void {
		AssertUnreachable();
	}

	auto CLauncherMgr::WaitUntilUserInput( int msSleepTime ) -> void { AssertUnreachable(); }

	auto CLauncherMgr::GetWindowRef() -> void* {
		if constexpr ( IsWindows() ) {
			return SDL_GetPointerProperty( SDL_GetWindowProperties( m_Window ), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr );
		} else if ( IsPosix() and strcmp( SDL_GetCurrentVideoDriver(), "x11" ) == 0 ) {
			return reinterpret_cast<void*>( SDL_GetNumberProperty( SDL_GetWindowProperties( m_Window ), SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0 ) );
		} else if ( IsPosix() and strcmp( SDL_GetCurrentVideoDriver(), "wayland" ) == 0 ) {
			return SDL_GetPointerProperty( SDL_GetWindowProperties( m_Window ), SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr );
		}
		return nullptr;
	}

	auto CLauncherMgr::SetMouseVisible( const bool pState ) -> void {
		if ( pState ) {
			SDL_ShowCursor();
		} else {
			SDL_HideCursor();
		}
	}
	auto CLauncherMgr::SetMouseCursor( SDL_Cursor* pCursor ) -> void {
		SDL_SetCursor( pCursor );
	}
	auto CLauncherMgr::SetForbidMouseGrab( bool bForbidMouseGrab ) -> void { AssertUnreachable(); }
	auto CLauncherMgr::OnFrameRendered() -> void { AssertUnreachable(); }

	auto CLauncherMgr::SetGammaRamp( const uint16* pRed, const uint16* pGreen, const uint16* pBlue ) -> void { AssertUnreachable(); }

	auto CLauncherMgr::GetPrevGLSwapWindowTime() -> double {
		return m_PrevSwapTime;
	}

	namespace { CLauncherMgr s_LauncherMgr{}; }
	ILauncherMgr* g_pLauncherMgr{ &s_LauncherMgr };
	EXPOSE_SINGLE_INTERFACE_GLOBALVAR( CLauncherMgr, ILauncherMgr, SDLMGR_INTERFACE_VERSION, s_LauncherMgr );
#endif