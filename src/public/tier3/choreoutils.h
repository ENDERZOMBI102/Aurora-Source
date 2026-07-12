//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Helper methods + classes for choreo
//
//===========================================================================//
#pragma once


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class CChoreoScene;
class CChoreoEvent;
class CStudioHdr;


//-----------------------------------------------------------------------------
// Finds sound files associated with events
//-----------------------------------------------------------------------------
auto GetSoundForEvent( CChoreoEvent* pEvent, CStudioHdr* pStudioHdr ) -> const char*;


//-----------------------------------------------------------------------------
// Fixes up the duration of a choreo scene based on wav files + animations
// Returns true if a change needed to be made
//-----------------------------------------------------------------------------
auto AutoAddGestureKeys( CChoreoEvent* e, CStudioHdr* pStudioHdr, float* pPoseParameters, bool bCheckOnly ) -> bool;
auto UpdateGestureLength( CChoreoEvent* e, CStudioHdr* pStudioHdr, float* pPoseParameters, bool bCheckOnly ) -> bool;
auto UpdateSequenceLength( CChoreoEvent* e, CStudioHdr* pStudioHdr, float* pPoseParameters, bool bCheckOnly, bool bVerbose ) -> bool;
