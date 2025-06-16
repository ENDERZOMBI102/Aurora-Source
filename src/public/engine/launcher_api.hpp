//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "appframework/IAppSystem.h"
#include "interface.h"


struct ModInfo_t;

class ILauncherAPI : public IAppSystem {
public:
	virtual bool SetStartupInfo( ModInfo_t* data ) = 0;
	virtual int Run() = 0;
};
#define VENGINE_LAUNCHER_API_VERSION "VENGINE_LAUNCHER_API_VERSION004"

// TODO: Figure this out
