//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "appframework/IAppSystem.h"
#include "interface.h"


#define VENGINE_HLDS_API_VERSION "VENGINE_HLDS_API_VERSION002"

class CAppSystemGroup;
struct ModInfo_t {
	void* m_pInstance;
	const char* m_pBaseDirectory;// Executable directory ("c:/program files/half-life 2", for example)
	const char* m_pInitialMod;   // Mod name ("cstrike", for example)
	const char* m_pInitialGame;  // Root game name ("hl2", for example, in the case of cstrike)
	CAppSystemGroup* m_pParentAppSystemGroup;
	bool m_bTextMode;
};


//-----------------------------------------------------------------------------
// Purpose: This is the interface exported by the engine.dll to allow a dedicated server front end
//  application to host it.
//-----------------------------------------------------------------------------
class IDedicatedServerAPI : public IAppSystem {
public:
	static constexpr auto INTERFACE_VERSION{ VENGINE_HLDS_API_VERSION };
public:
	// Initialize the engine with the specified base directory and interface factories
	virtual bool ModInit( ModInfo_t& info ) = 0;
	// Shutdown the engine
	virtual void ModShutdown() = 0;
	// Run a frame
	virtual bool RunFrame() = 0;
	// Insert text into console
	virtual void AddConsoleText( char* text ) = 0;
	// Get current status to display in the hlds UI (console window title bar, e.g. )
	virtual void UpdateStatus( float* fps, int* nActive, int* nMaxPlayers, char* pszMap, int maxlen ) = 0;
	// Get current Hostname to display in the hlds UI (console window title bar, e.g. )
	virtual void UpdateHostname( char* pszHostname, int maxlen ) = 0;
};
