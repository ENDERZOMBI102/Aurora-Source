//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#pragma once
#include "fontabc.h"
#include "vgui/VGUI.h"

abstract_class ITextMessage {
public:
	virtual void SetPosition( int x, int y ) = 0;
	virtual void AddChar( int r, int g, int b, int a, wchar_t ch ) = 0;

	virtual void GetLength( int* wide, int* tall, const char* string ) = 0;
	virtual int GetFontInfo( FONTABC * pABCs, vgui::HFont hFont ) = 0;

	virtual void SetFont( vgui::HFont hCustomFont ) = 0;
	virtual void SetDefaultFont( void ) = 0;
};

extern ITextMessage* textmessage;
