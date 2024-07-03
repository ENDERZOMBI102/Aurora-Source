//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef INTERVAL_H
#define INTERVAL_H
#if IsWindows()
#pragma once
#endif

#include "basetypes.h"


interval_t ReadInterval( const char *pString );
float RandomInterval( const interval_t &interval );

#endif // INTERVAL_H
