//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once


#define SF_ENERGYCORE_NO_PARTICLES ( 1 << 0 )
#define SF_ENERGYCORE_START_ON ( 1 << 1 )

enum {
	ENERGYCORE_STATE_OFF,
	ENERGYCORE_STATE_CHARGING,
	ENERGYCORE_STATE_DISCHARGING,
};

#ifndef CLIENT_DLL
	// ============================================================================
	//
	//  Energy core - charges up and then releases energy from its position
	//
	// ============================================================================
	class CCitadelEnergyCore : public CBaseEntity {
		DECLARE_CLASS( CCitadelEnergyCore, CBaseEntity );
		DECLARE_SERVERCLASS();
		DECLARE_DATADESC();

	public:
		void InputStartCharge( inputdata_t& inputdata );
		void InputStartDischarge( inputdata_t& inputdata );
		void InputStop( inputdata_t& inputdata );
		void SetScale( float flScale ) { m_flScale = flScale; }

		void StartCharge( float flWarmUpTime );
		void StartDischarge();
		void StopDischarge( float flCoolDownTime );

		virtual int ShouldTransmit( const CCheckTransmitInfo* pInfo );
		virtual int UpdateTransmitState();

		virtual void Precache();
		void Spawn();

	private:
		CNetworkVar( float, m_flScale );
		CNetworkVar( int, m_nState );
		CNetworkVar( float, m_flDuration );
		CNetworkVar( float, m_flStartTime );
	};
#endif
