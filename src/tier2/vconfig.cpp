//
// Created by ENDERZOMBI102 on 24/12/2025.
//
#include "tier2/vconfig.h"


void SetVConfigRegistrySetting( const char* pName, const char* pValue, const bool pNotify ) {
	(void) pName;
	(void) pValue;
	(void) pNotify;
}
auto GetVConfigRegistrySetting( const char* pName, char* const pReturn, const int pSize ) -> bool {
	(void) pName;
	(void) pReturn;
	(void) pSize;
	return false;
}

#if defined( PLATFORM_WINDOWS )
	auto RemoveObsoleteVConfigRegistrySetting( const char* pValueName, char* pOldValue, int pSize ) -> bool {
		(void) pValueName;
		(void) pOldValue;
		(void) pSize;
		return false;
	}
#endif

auto ConvertObsoleteVConfigRegistrySetting( const char* pValueName ) -> bool {
	(void) pValueName;
	return false;
}
