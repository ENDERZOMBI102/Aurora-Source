//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A higher level link library for general use in the game and tools.
//
//===========================================================================//
#pragma once
#include "tier2/tier2dm.h"
#include "tier3/tier3.h"


//-----------------------------------------------------------------------------
// Helper empty implementation of an IAppSystem for tier3 libraries
//-----------------------------------------------------------------------------
template<class IInterface, int ConVarFlag = 0>
class CTier3DmAppSystem : public CTier2DmAppSystem<IInterface, ConVarFlag> {
	using BaseClass = CTier2DmAppSystem<IInterface, ConVarFlag>;
public:
	explicit CTier3DmAppSystem( bool bIsPrimaryAppSystem = true )
		: BaseClass( bIsPrimaryAppSystem ) { }

	bool Connect( CreateInterfaceFn factory ) override {
		if ( not BaseClass::Connect( factory ) ) {
			return false;
		}

		if ( BaseClass::IsPrimaryAppSystem() ) {
			ConnectTier3Libraries( &factory, 1 );
		}
		return true;
	}

	void Disconnect() override {
		if ( BaseClass::IsPrimaryAppSystem() ) {
			DisconnectTier3Libraries();
		}
		BaseClass::Disconnect();
	}
};
