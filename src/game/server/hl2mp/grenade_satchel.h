//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:		Satchel Charge
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#pragma once
#include "basegrenade_shared.h"
#include "hl2mp/weapon_slam.h"

class CSoundPatch;
class CSprite;

class CSatchelCharge : public CBaseGrenade {
public:
	DECLARE_CLASS( CSatchelCharge, CBaseGrenade );

	void Spawn( void );
	void Precache( void );
	void BounceSound( void );
	void SatchelTouch( CBaseEntity* pOther );
	void SatchelThink( void );

	// Input handlers
	void InputExplode( inputdata_t& inputdata );

	float m_flNextBounceSoundTime;
	bool m_bInAir;
	Vector m_vLastPosition;

public:
	CWeapon_SLAM* m_pMyWeaponSLAM;// Who shot me..
	bool m_bIsAttached;
	void Deactivate( void );

	CSatchelCharge();
	~CSatchelCharge();

	DECLARE_DATADESC();

private:
	void CreateEffects();
	CHandle<CSprite> m_hGlowSprite;
};
