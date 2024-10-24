//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Expose an IsAHunter function
//
//=============================================================================//
#pragma once

class CBaseEntity;

/// true if given entity pointer is a hunter.
bool Hunter_IsHunter( CBaseEntity* pEnt );

// call throughs for member functions

void Hunter_StriderBusterAttached( CBaseEntity* pHunter, CBaseEntity* pAttached );
void Hunter_StriderBusterDetached( CBaseEntity* pHunter, CBaseEntity* pAttached );
void Hunter_StriderBusterLaunched( CBaseEntity* pBuster );
