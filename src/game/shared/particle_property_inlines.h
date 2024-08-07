//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Define inline functions for the CParticleProperty class. The
//			definitions	exist in this include file to avoid cluttering up
//			particle_property.h, but this file should not be included from any-
//			where else.
//
//=============================================================================
#pragma once
#ifndef PARTICLEPROPERTY_H
	#error "Do not include particle_property_inlines.h from anywhere other than particle_property.h!"
#endif

/// Set the parent of a given control point on a given effect to the index of another control point. This is
/// in fact entirely redundant given the function is actually on the CNewParticleEffect, but is included here
/// for uniformity of interface.
void CParticleProperty::SetControlPointParent( CNewParticleEffect* pEffect, int whichControlPoint, int parentIdx ) {
	pEffect->SetControlPointParent( whichControlPoint, parentIdx );
}

/// Given an index, return a pointer to the relevant particle effect structure. For convenience.
CNewParticleEffect* CParticleProperty::GetParticleEffectFromIdx( int idx ) {
	return m_ParticleEffects[ idx ].pParticleEffect.GetObject();
}
