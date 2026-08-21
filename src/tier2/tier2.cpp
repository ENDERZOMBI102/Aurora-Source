//
// Created by ENDERZOMBI102 on 24/12/2025.
//
#include "tier2/tier2.h"

#include "filesystem.h"
#include "filesystem/IQueuedLoader.h"
#include "inputsystem/iinputsystem.h"
#include "materialsystem/idebugtextureinfo.h"
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/ivballoctracker.h"
#include "mdllib/mdllib.h"
#include "p4lib/ip4.h"
#include "tier0/icommandline.h"
#include "vgui_controls/RichText.h"


IFileSystem* g_pFullFileSystem;
IMaterialSystem* materials;
IMaterialSystem* g_pMaterialSystem;
IInputSystem* g_pInputSystem;
INetworkSystem* g_pNetworkSystem;
IMaterialSystemHardwareConfig* g_pMaterialSystemHardwareConfig;
IDebugTextureInfo* g_pMaterialSystemDebugTextureInfo;
IVBAllocTracker* g_VBAllocTracker;
IColorCorrectionSystem* colorcorrection;
IP4* p4;
IMdlLib* mdllib;
IQueuedLoader* g_pQueuedLoader;

void ConnectTier2Libraries( const CreateInterfaceFn* pFactoryList, const int pFactoryCount ) {
	for ( int i{ 0 }; i < pFactoryCount; i += 1 ) {
		if ( g_pFullFileSystem == nullptr ) {
			g_pFullFileSystem = static_cast<IFileSystem*>( (*pFactoryList[i])( FILESYSTEM_INTERFACE_VERSION, nullptr ) );
		}
		if ( materials == nullptr ) {
			materials = static_cast<IMaterialSystem*>( (*pFactoryList[i])( MATERIAL_SYSTEM_INTERFACE_VERSION, nullptr ) );
			g_pMaterialSystem = materials;
		}
		if ( g_pInputSystem == nullptr ) {
			g_pInputSystem = static_cast<IInputSystem*>( (*pFactoryList[i])( INPUTSYSTEM_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pNetworkSystem == nullptr ) {
			// whats the string?
			// g_pNetworkSystem = static_cast<INetworkSystem*>( (*pFactoryList[i])( NETWORKSYSTEM_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pMaterialSystemHardwareConfig == nullptr ) {
			g_pMaterialSystemHardwareConfig = static_cast<IMaterialSystemHardwareConfig*>( ( *pFactoryList[ i ] )( MATERIALSYSTEM_HARDWARECONFIG_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pMaterialSystemDebugTextureInfo == nullptr ) {
			g_pMaterialSystemDebugTextureInfo = static_cast<IDebugTextureInfo*>( (*pFactoryList[i])( DEBUG_TEXTURE_INFO_VERSION, nullptr ) );
		}
		if ( g_VBAllocTracker == nullptr ) {
			g_VBAllocTracker = static_cast<IVBAllocTracker*>( (*pFactoryList[i])( VB_ALLOC_TRACKER_INTERFACE_VERSION, nullptr ) );
		}
		if ( colorcorrection == nullptr ) {
			colorcorrection = static_cast<IColorCorrectionSystem*>( (*pFactoryList[i])( COLORCORRECTION_INTERFACE_VERSION, nullptr ) );
		}
		if ( p4 == nullptr ) {
			p4 = static_cast<IP4*>( (*pFactoryList[i])( P4_INTERFACE_VERSION, nullptr ) );
		}
		if ( mdllib == nullptr ) {
			mdllib = static_cast<IMdlLib*>( (*pFactoryList[i])( MDLLIB_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pQueuedLoader == nullptr ) {
			g_pQueuedLoader = static_cast<IQueuedLoader*>( (*pFactoryList[i])( QUEUEDLOADER_INTERFACE_VERSION, nullptr ) );
		}
	}
}
void DisconnectTier2Libraries() {
	p4 = nullptr;
	mdllib = nullptr;
	materials = nullptr;
	colorcorrection = nullptr;
	g_pInputSystem = nullptr;
	g_pQueuedLoader	 = nullptr;
	g_VBAllocTracker = nullptr;
	g_pNetworkSystem = nullptr;
	g_pMaterialSystem = nullptr;
	g_pFullFileSystem = nullptr;
	g_pMaterialSystemHardwareConfig = nullptr;
	g_pMaterialSystemDebugTextureInfo = nullptr;
}

void InitDefaultFileSystem() { }
void ShutdownDefaultFileSystem() { }

void InitCommandLineProgram( int argc, char** argv ) {
	MathLib_Init( 1.0,1.0,1.0,0,false,true,true,true );
	CommandLine()->CreateCmdLine( argc, argv );
	InitDefaultFileSystem();

	if ( not Plat_IsInDebugSession() ) {
		SpewOutputFunc( DefaultSpewFuncAbortOnAsserts );
	}
}
