//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "appframework/IAppSystem.h"
#include "interface.h"


struct ModInfo_t;

#define VENGINE_LAUNCHER_API_VERSION "VENGINE_LAUNCHER_API_VERSION004"
class ILauncherAPI : public IAppSystem {
public:
	static constexpr auto INTERFACE_VERSION{ VENGINE_LAUNCHER_API_VERSION };
public:
	virtual bool SetStartupInfo( ModInfo_t* data ) = 0;
	virtual int Run() = 0;
};

// TODO: Figure this out
