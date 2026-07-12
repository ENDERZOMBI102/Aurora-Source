//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A higher level link library for general use in the game and tools.
//
//===========================================================================//
#pragma once
#include "Color.h"
#include "datacache/imdlcache.h"
#include "mathlib/vector.h"
#include "studio.h"


//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
struct matrix3x4_t;

struct MDLSquenceLayer_t {
	int m_nSequenceIndex;
	float m_flWeight;
	bool m_bNoLoop;
	float m_flCycleBeganAt;
};

//-----------------------------------------------------------------------------
// Class containing simplistic MDL state for use in rendering
//-----------------------------------------------------------------------------
class CMDL {
public:
	CMDL() = default;
	~CMDL();

	auto SetMDL( MDLHandle_t pHandle ) -> void;
	auto GetMDL() const -> MDLHandle_t;

	// Simple version of drawing; sets up bones for you
	auto Draw( const matrix3x4_t& rootToWorld ) -> void;

	// NOTE: This version of draw assumes you've filled in the bone to world
	// matrix yourself by calling IStudioRender::LockBoneMatrices. The pointer
	// returned by that method needs to be passed into here
	auto Draw( const matrix3x4_t& rootToWorld, const matrix3x4_t* pBoneToWorld ) -> void;


	auto SetUpBones( const matrix3x4_t& shapeToWorld, int nMaxBoneCount, matrix3x4_t* pOutputMatrices, const float* pPoseParameters = nullptr, MDLSquenceLayer_t* pSequenceLayers = nullptr, int nNumSequenceLayers = 0 ) -> void;
	auto SetupBonesWithBoneMerge( const CStudioHdr* pMergeHdr, matrix3x4_t* pMergeBoneToWorld, const CStudioHdr* pFollow, const matrix3x4_t* pFollowBoneToWorld, const matrix3x4_t& matModelToWorld ) -> void;

	auto GetStudioHdr() -> studiohdr_t*;

private:
	auto UnreferenceMDL() -> void;

public:
	MDLHandle_t m_MDLHandle{ MDLHANDLE_INVALID };
	Color m_Color{};
	int m_nSkin{};
	int m_nBody{};
	int m_nSequence{};
	int m_nLOD{};
	float m_flPlaybackRate{};
	float m_flTime{};
	float m_pFlexControls[ MAXSTUDIOFLEXCTRL * 4 ] { };
	Vector m_vecViewTarget{};
	bool m_bWorldSpaceViewTarget{};
	void* m_pProxyData{};
};


//-----------------------------------------------------------------------------
// Returns the bounding box for the model
//-----------------------------------------------------------------------------
auto GetMDLBoundingBox( Vector* pMins, Vector* pMaxs, MDLHandle_t pHandle, int pSequence ) -> void;

//-----------------------------------------------------------------------------
// Returns the radius of the model as measured from the origin
//-----------------------------------------------------------------------------
auto GetMDLRadius( MDLHandle_t h, int nSequence ) -> float;

//-----------------------------------------------------------------------------
// Returns a more accurate bounding sphere
//-----------------------------------------------------------------------------
auto GetMDLBoundingSphere( Vector* pVecCenter, float* pRadius, MDLHandle_t h, int nSequence ) -> void;
