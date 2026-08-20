//========= Copyright Valve Corporation, All rights reserved. ============//
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// $Header: $
// $NoKeywords: $
//
// Material editor
//=============================================================================
#pragma once
#include "appframework/tier3app.h"


//-----------------------------------------------------------------------------
// The application object
//-----------------------------------------------------------------------------
class CVguiMatSysApp : public CVguiSteamApp {
	using BaseClass = CVguiSteamApp;
public:
	CVguiMatSysApp();
public:	// Methods of IAppSystemGroup
	virtual auto Create() -> bool;
	virtual auto PreInit() -> bool;
	virtual auto PostShutdown() -> void;
	virtual auto Destroy() -> void;
public:
	// Returns the window handle (HWND in Win32)
	auto GetAppWindow() -> void*;

	// Gets the window size
	[[nodiscard]]
	auto GetWindowWidth() const -> int;
	[[nodiscard]]
	auto GetWindowHeight() const -> int;

protected:
	auto AppPumpMessages() -> void;

	// Sets the video mode
	auto SetVideoMode() -> bool;

	// Sets up the game path
	auto SetupSearchPaths( const char* pStartingDir, bool bOnlyUseStartingDir, bool bIsTool ) -> bool;

private:
	// Returns the app name
	virtual auto GetAppName() -> const char* = 0;
	virtual auto AppUsesReadPixels() -> bool { return false; }

	// Creates the app window
	virtual auto CreateAppWindow( char const* pTitle, bool pWindowed, int pWidth, int pHeight ) -> void*;

	void* m_HWnd{};
	int m_nWidth{};
	int m_nHeight{};
};
