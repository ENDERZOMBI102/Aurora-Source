//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: A higher level link library for general use in the game and tools.
//
//===========================================================================//
#pragma once
#include "tier2/tier2.h"

//-----------------------------------------------------------------------------
// Set up methods related to datamodel interfaces
//-----------------------------------------------------------------------------
auto ConnectDataModel( CreateInterfaceFn factory ) -> bool;
auto InitDataModel() -> InitReturnVal_t;
void ShutdownDataModel();
void DisconnectDataModel();

// Helper empty implementation of an IAppSystem for tier2 libraries
template<class IInterface, int ConVarFlag = 0>
class CTier2DmAppSystem : public CTier2AppSystem<IInterface, ConVarFlag> {
	using BaseClass = CTier2AppSystem<IInterface, ConVarFlag>;
public:
	explicit CTier2DmAppSystem( bool bIsPrimaryAppSystem = true )
		: BaseClass( bIsPrimaryAppSystem ) { }

	auto Connect( CreateInterfaceFn factory ) -> bool override {
		if ( not BaseClass::Connect( factory ) ) {
			return false;
		}

		ConnectDataModel( factory );

		return true;
	}

	auto Init() -> InitReturnVal_t  override {
		InitReturnVal_t nRetVal = BaseClass::Init();
		if ( nRetVal != INIT_OK ) {
			return nRetVal;
		}

		nRetVal = InitDataModel();
		if ( nRetVal != INIT_OK ) {
			return nRetVal;
		}

		return INIT_OK;
	}

	void Shutdown() override {
		ShutdownDataModel();
		BaseClass::Shutdown();
	}

	void Disconnect() override {
		DisconnectDataModel();
		BaseClass::Disconnect();
	}
};
