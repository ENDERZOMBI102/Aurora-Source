//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#if !defined ( SHATTERSURFACETYPES_H )
#define SHATTERSURFACETYPES_H
#if IsWindows()
#pragma once
#endif

enum ShatterSurface_t
{
	// Note: This much match with the client entity
	SHATTERSURFACE_GLASS = 0,
	SHATTERSURFACE_TILE  = 1,
};

#endif
