//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
// $NoKeywords: $
//
//===========================================================================//
#pragma once
#include "inputsystem/buttoncode.h"
#include "tier1/utlstring.h"

class CUtlBuffer;


class CKeyBindings {
public:
	void SetBinding( ButtonCode_t code, const char* pBinding );
	void SetBinding( const char* pButtonName, const char* pBinding );

	void Unbind( ButtonCode_t code );
	void Unbind( const char* pButtonName );
	void UnbindAll();

	int GetBindingCount() const;
	void WriteBindings( CUtlBuffer& buf );
	const char* ButtonNameForBinding( const char* pBinding );
	const char* GetBindingForButton( ButtonCode_t code );

private:
	CUtlString m_KeyInfo[ BUTTON_CODE_LAST ];
};
