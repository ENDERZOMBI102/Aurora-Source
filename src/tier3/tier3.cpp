//
// Created by ENDERZOMBI102 on 24/12/2025.
//
#include "tier3/tier3.h"
#include "SoundEmitterSystem/isoundemittersystembase.h"
#include "VGuiMatSurface/IMatSystemSurface.h"
#include "datacache/idatacache.h"
#include "istudiorender.h"
#include "ivtex.h"
#include "vgui/IInput.h"
#include "vgui/ILocalize.h"
#include "vgui/IPanel.h"
#include "vgui/IScheme.h"
#include "vgui/ISystem.h"
#include "vgui/IVGui.h"
#include "video/ivideoservices.h"
#include "vphysics_interface.h"


IStudioRender* g_pStudioRender;
IStudioRender* studiorender;
IMatSystemSurface* g_pMatSystemSurface;
vgui::ISurface* g_pVGuiSurface;
vgui::IInput* g_pVGuiInput;
vgui::IVGui* g_pVGui;
vgui::IPanel* g_pVGuiPanel;
vgui::ILocalize* g_pVGuiLocalize;
vgui::ISchemeManager* g_pVGuiSchemeManager;
vgui::ISystem* g_pVGuiSystem;
IDataCache* g_pDataCache;// FIXME: Should IDataCache be in tier2?
IMDLCache* g_pMDLCache;
IMDLCache* mdlcache;
IVideoServices* g_pVideo;
IDmeMakefileUtils* g_pDmeMakefileUtils;
IPhysicsCollision* g_pPhysicsCollision;
ISoundEmitterSystemBase* g_pSoundEmitterSystem;
IVTex* g_pVTex;

void ConnectTier3Libraries( CreateInterfaceFn* const pFactoryList, const int pFactoryCount ) {
	for ( int i{ 0 }; i < pFactoryCount; i += 1 ) {
		if ( g_pStudioRender == nullptr ) {
			g_pStudioRender = studiorender = static_cast<IStudioRender*>( pFactoryList[i]( STUDIO_RENDER_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pMatSystemSurface == nullptr ) {
			g_pMatSystemSurface = static_cast<IMatSystemSurface*>( pFactoryList[i]( MAT_SYSTEM_SURFACE_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiSurface == nullptr ) {
			g_pVGuiSurface = static_cast<vgui::ISurface*>( pFactoryList[i]( VGUI_SURFACE_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiInput == nullptr ) {
			g_pVGuiInput = static_cast<vgui::IInput*>( pFactoryList[i]( VGUI_INPUT_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGui == nullptr ) {
			g_pVGui = static_cast<vgui::IVGui*>( pFactoryList[i]( VGUI_IVGUI_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiPanel == nullptr ) {
			g_pVGuiPanel = static_cast<vgui::IPanel*>( pFactoryList[i]( VGUI_PANEL_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiLocalize == nullptr ) {
			g_pVGuiLocalize = static_cast<vgui::ILocalize*>( pFactoryList[i]( VGUI_LOCALIZE_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiSchemeManager == nullptr ) {
			g_pVGuiSchemeManager = static_cast<vgui::ISchemeManager*>( pFactoryList[i]( VGUI_SCHEME_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVGuiSystem == nullptr ) {
			g_pVGuiSystem = static_cast<vgui::ISystem*>( pFactoryList[i]( VGUI_SYSTEM_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pDataCache == nullptr ) {
			g_pDataCache = static_cast<IDataCache*>( pFactoryList[i]( DATACACHE_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pMDLCache == nullptr ) {
			g_pMDLCache = mdlcache = static_cast<IMDLCache*>( pFactoryList[i]( MDLCACHE_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVideo == nullptr ) {
			g_pVideo = static_cast<IVideoServices*>( pFactoryList[i]( VIDEO_SERVICES_INTERFACE_VERSION, nullptr ) );
		}
		// TODO: Figure this out
		if ( g_pDmeMakefileUtils == nullptr ) {
			// g_pDmeMakefileUtils = static_cast<IDmeMakefileUtils*>( pFactoryList[i]( , nullptr ) );
		}
		if ( g_pPhysicsCollision == nullptr ) {
			g_pPhysicsCollision = static_cast<IPhysicsCollision*>( pFactoryList[i]( VPHYSICS_COLLISION_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pSoundEmitterSystem == nullptr ) {
			g_pSoundEmitterSystem = static_cast<ISoundEmitterSystemBase*>( pFactoryList[i]( SOUNDEMITTERSYSTEM_INTERFACE_VERSION, nullptr ) );
		}
		if ( g_pVTex == nullptr ) {
			g_pVTex = static_cast<IVTex*>( pFactoryList[i]( IVTEX_INTERFACE_VERSION, nullptr ) );
		}
	}
}
void DisconnectTier3Libraries() {
	g_pStudioRender = nullptr;
	studiorender = nullptr;
	g_pMatSystemSurface = nullptr;
	g_pVGuiSurface = nullptr;
	g_pVGuiInput = nullptr;
	g_pVGui = nullptr;
	g_pVGuiPanel = nullptr;
	g_pVGuiLocalize = nullptr;
	g_pVGuiSchemeManager = nullptr;
	g_pVGuiSystem = nullptr;
	g_pDataCache = nullptr;
	g_pMDLCache = nullptr;
	mdlcache = nullptr;
	g_pVideo = nullptr;
	g_pDmeMakefileUtils = nullptr;
	g_pPhysicsCollision = nullptr;
	g_pSoundEmitterSystem = nullptr;
	g_pVTex = nullptr;
}
