//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================
#pragma once

enum debughistorycategories_t {
	HISTORY_ENTITY_IO,
	HISTORY_AI_DECISIONS,
	HISTORY_SCENE_PRINT,
	HISTORY_ALYX_BLIND,   // TEMP: until we find and fix this bug
	HISTORY_PLAYER_DAMAGE,// record all damage done to the player

	// Add new categories here

	MAX_HISTORY_CATEGORIES,
};

#define DISABLE_DEBUG_HISTORY

#if defined( DISABLE_DEBUG_HISTORY )
	#define ADD_DEBUG_HISTORY( category, line ) ( (void) 0 )
#else
	#define ADD_DEBUG_HISTORY( category, line ) AddDebugHistoryLine( category, line )
void AddDebugHistoryLine( int iCategory, const char* pszLine );
#endif
