//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "appframework/IAppSystem.h"
#include "interface.h"


class ILauncherAPI : public IAppSystem {
public:
	virtual int Run() = 0;
};
#define VENGINE_LAUNCHER_API_VERSION "VENGINE_LAUNCHER_API_VERSION004"

// TODO: Figure this out
