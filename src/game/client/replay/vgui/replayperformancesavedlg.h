//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=======================================================================================//
#pragma once

//-----------------------------------------------------------------------------

class CReplay;

//-----------------------------------------------------------------------------

typedef void ( *OnConfirmSaveCallback )( bool bConfirmed, wchar_t* pTitle, void* pContext );

//-----------------------------------------------------------------------------

void ReplayUI_ShowPerformanceSaveDlg( OnConfirmSaveCallback pfnCallback, void* pContext, CReplay* pReplay,
									  bool bExitEditorWhenDone );
bool ReplayUI_IsPerformanceSaveDlgOpen();
