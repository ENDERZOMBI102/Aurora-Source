//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================//
#pragma once


class IReplayMovie;
namespace vgui {
	class Panel;
};

/**
 * Show the YouTube login dialog and attempt to upload the movie if login was successful
 * @param pMovie
 * @param pParent
 */
void YouTube_ShowLoginDialog( IReplayMovie* pMovie, vgui::Panel* pParent );

/**
 *
 * Show the YouTube upload dialog and upload the movie
 * @param pMovie
 * @param pParent
 */
void YouTube_ShowUploadDialog( IReplayMovie* pMovie, vgui::Panel* pParent );
