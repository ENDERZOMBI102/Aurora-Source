//
// Created by ENDERZOMBI102 on 24/12/2025.
//
#include "tier2/tier2dm.h"
#include "datamodel/idatamodel.h"
#include "datamodel/dmelementfactoryhelper.h"
#include "dmserializers/idmserializers.h"


auto ConnectDataModel( const CreateInterfaceFn factory ) -> bool {
	g_pDmElementFramework = static_cast<IDmElementFramework*>( factory( VDMELEMENTFRAMEWORK_VERSION, nullptr ) );
	if ( g_pDmElementFramework == nullptr ) {
		return false;
	}
	g_pDataModel = static_cast<IDataModel*>( factory( VDATAMODEL_INTERFACE_VERSION, nullptr ) );
	if ( g_pDataModel == nullptr ) {
		return false;
	}
	g_pDmSerializers = static_cast<IDmSerializers*>( factory( DMSERIALIZERS_INTERFACE_VERSION, nullptr ) );
	if ( g_pDmSerializers == nullptr ) {
		return false;
	}
	return true;
}
auto InitDataModel() -> InitReturnVal_t {
	InitReturnVal_t res{};
	if ( (res = g_pDmElementFramework->Init()) == InitReturnVal_t::INIT_FAILED ) {
		return res;
	}
	if ( (res = g_pDataModel->Init()) == InitReturnVal_t::INIT_FAILED ) {
		return res;
	}
	return g_pDmSerializers->Init();
}
void ShutdownDataModel() {
	g_pDmElementFramework->Shutdown();
	g_pDataModel->Shutdown();
	g_pDmSerializers->Shutdown();
}
void DisconnectDataModel() {
	g_pDmElementFramework = nullptr;
	g_pDataModel = nullptr;
	g_pDmSerializers = nullptr;
}
