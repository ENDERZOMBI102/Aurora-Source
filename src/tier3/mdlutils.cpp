//
// Created by ENDERZOMBI102 on 12/07/2026.
#include "tier3/mdlutils.h"
#include <utility>

#include "tier3/tier3.h"


CMDL::~CMDL() {
	this->UnreferenceMDL();
}

auto CMDL::SetMDL( const MDLHandle_t pHandle ) -> void {
	// do not leak
	this->UnreferenceMDL();

	m_MDLHandle = pHandle;

	// if its a valid handle, up its refcount
	if ( m_MDLHandle != MDLHANDLE_INVALID ) {
		(void) g_pMDLCache->AddRef( m_MDLHandle );
		(void) g_pMDLCache->LockStudioHdr( m_MDLHandle );
	}
}
auto CMDL::GetMDL() const -> MDLHandle_t {
	return m_MDLHandle;
}
auto CMDL::Draw( const matrix3x4_t& rootToWorld ) -> void {
	AssertUnreachable();
}
auto CMDL::Draw( const matrix3x4_t& rootToWorld, const matrix3x4_t* pBoneToWorld ) -> void {
	AssertUnreachable();
}
auto CMDL::SetUpBones( const matrix3x4_t& shapeToWorld, int nMaxBoneCount, matrix3x4_t* pOutputMatrices, const float* pPoseParameters, MDLSquenceLayer_t* pSequenceLayers, int nNumSequenceLayers ) -> void {
	AssertUnreachable();
}
auto CMDL::SetupBonesWithBoneMerge( const CStudioHdr* pMergeHdr, matrix3x4_t* pMergeBoneToWorld, const CStudioHdr* pFollow, const matrix3x4_t* pFollowBoneToWorld, const matrix3x4_t& matModelToWorld ) -> void {
	AssertUnreachable();
}
auto CMDL::GetStudioHdr() -> studiohdr_t* {
	Assert( g_pMDLCache != nullptr );
	if ( g_pMDLCache == nullptr ) [[unlikely]] {
		return nullptr;
	}
	return g_pMDLCache->GetStudioHdr( m_MDLHandle );
}
auto CMDL::UnreferenceMDL() -> void {
	if ( m_MDLHandle != MDLHANDLE_INVALID and g_pMDLCache != nullptr ) {
		g_pMDLCache->UnlockStudioHdr( m_MDLHandle );
		g_pMDLCache->Release( m_MDLHandle );
	}
	m_MDLHandle = MDLHANDLE_INVALID;
}

auto GetMDLBoundingBox( Vector* pMins, Vector* pMaxs, const MDLHandle_t pHandle, const int pSequence ) -> void {
	(void) pSequence;
	if ( pHandle == MDLHANDLE_INVALID or g_pMDLCache == nullptr ) [[unlikely]] {
		*pMins = {};
		*pMaxs = {};
		return;
	}
	const studiohdr_t* hdr{ g_pMDLCache->GetStudioHdr( pHandle ) };
	// FIXME: This is incorrect!!
	*pMins = hdr->hull_min;
	*pMaxs = hdr->hull_max;
}
auto GetMDLRadius( MDLHandle_t h, int nSequence ) -> float {
	AssertUnreachable();
}
auto GetMDLBoundingSphere( Vector* pVecCenter, float* pRadius, MDLHandle_t h, int nSequence ) -> void {
	AssertUnreachable();
}

