//
// Created by ENDERZOMBI102 on 03/07/2025.
//
#include "vstdlib/cvar.h"
// This must be the final include in a .cpp file!!!
#include "tier0/memdbgon.h"


CreateInterfaceFn VStdLib_GetICVarFactory() {
	return Sys_GetFactoryThis();
}