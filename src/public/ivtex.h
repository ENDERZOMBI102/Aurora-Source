//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//===========================================================================//
#pragma once
#include "appframework/IAppSystem.h"
#include "tier1/interface.h"


#define IVTEX_INTERFACE_VERSION "VTEX_003"

class IVTex : public IAppSystem {
public:
	static constexpr auto INTERFACE_VERSION{ IVTEX_INTERFACE_VERSION };
public:
	// For use by command-line tools
	virtual int VTex( int argc, char** argv ) = 0;

	// For use by engine
	virtual int VTex( CreateInterfaceFn filesystemFactory, const char* pGameDir, int argc, char** argv ) = 0;
};
