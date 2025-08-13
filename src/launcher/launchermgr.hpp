//
// Created by ENDERZOMBI102 on 08/06/2025.
// 
#pragma once
#include "SDL3/SDL_video.h"
#include "appframework/ilaunchermgr.h"

#if defined( USE_SDL )
	class CLauncherMgr : public ILauncherMgr {
	public:
		auto Connect( CreateInterfaceFn factory ) -> bool override;
		auto Disconnect() -> void override;
		auto QueryInterface( const char* pInterfaceName ) -> void* override;
		auto Init() -> InitReturnVal_t override;
		auto Shutdown() -> void override;

		auto CreateGameWindow( const char* pTitle, bool pWindowed, int pWidth, int pHeight ) -> bool override;

		auto IncWindowRefCount() -> void override;
		auto DecWindowRefCount() -> void override;

		auto GetEvents( CCocoaEvent* pEvents, int nMaxEventsToReturn, bool debugEvents ) -> int override;
		#if IsLinux()
			auto PeekAndRemoveKeyboardEvents( bool* pbEsc, bool* pbReturn, bool* pbSpace, bool debugEvents ) -> int override;
		#endif

		auto SetCursorPosition( int x, int y ) -> void override;

		auto SetWindowFullScreen( bool pFullScreen, int pWidth, int pHeight ) -> void override;
		auto IsWindowFullScreen() -> bool override;
		auto MoveWindow( int x, int y ) -> void override;
		auto SizeWindow( int pWidth, int pHeight ) -> void override;
		auto PumpWindowsMessageLoop() -> void override;

		auto DestroyGameWindow() -> void override;
		auto SetApplicationIcon( const char* pAppIconFile ) -> void override;
		auto GetMouseDelta( int& x, int& y, bool bIgnoreNextMouseDelta ) -> void override;

		auto GetNativeDisplayInfo( int nDisplay, uint& nWidth, uint& nHeight, uint& nRefreshHz ) -> void override;
		auto RenderedSize( uint& oWidth, uint& oHeight, bool pSet ) -> void override;
		auto DisplayedSize( uint& oWidth, uint& oHeight ) -> void override;

		#if defined( DX_TO_GL_ABSTRACTION )
			auto GetMainContext() -> PseudoGLContextPtr override;
			auto GetGLContextForWindow( void* windowref ) -> PseudoGLContextPtr override;
			auto CreateExtraContext() -> PseudoGLContextPtr override;
			auto DeleteContext( PseudoGLContextPtr pContext ) -> void override;
			auto MakeContextCurrent( PseudoGLContextPtr pContext ) -> bool override;
			auto GetDisplayDB() -> GLMDisplayDB* override;
			auto GetDesiredPixelFormatAttribsAndRendererInfo( uint** ptrOut, uint* countOut, GLMRendererInfoFields* rendInfoOut ) -> void override;
			auto ShowPixels( CShowPixelsParams* params ) -> void override;
		#endif

		auto GetStackCrawl( CStackCrawlParams* params ) -> void override;

		auto WaitUntilUserInput( int msSleepTime ) -> void override;

		auto GetWindowRef() -> void* override;

		auto SetMouseVisible( bool pState ) -> void override;
		auto SetMouseCursor( SDL_Cursor* pCursor ) -> void override;
		auto SetForbidMouseGrab( bool bForbidMouseGrab ) -> void override;
		auto OnFrameRendered() -> void override;

		auto SetGammaRamp( const uint16* pRed, const uint16* pGreen, const uint16* pBlue ) -> void override;

		auto GetPrevGLSwapWindowTime() -> double override;
	private:
		SDL_Window* m_Window{ nullptr };
		SDL_GLContext m_MainContext{ nullptr };
		uint32 m_WindowRefCount{ 0 };
		float64 m_PrevSwapTime{ 0 };
		bool m_Fullscreen{ false };
	};
#endif
