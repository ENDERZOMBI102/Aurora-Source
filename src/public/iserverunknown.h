//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//
#pragma once
#include "ihandleentity.h"

class ICollideable;
class IServerNetworkable;
class CBaseEntity;


// This is the server's version of IUnknown. We may want to use a QueryInterface-like
// mechanism if this gets big.
class IServerUnknown : public IHandleEntity {
public:
	// Gets the interface to the collideable + networkable representation of the entity
	virtual ICollideable* GetCollideable() = 0;
	virtual IServerNetworkable* GetNetworkable() = 0;
	virtual CBaseEntity* GetBaseEntity() = 0;
};
