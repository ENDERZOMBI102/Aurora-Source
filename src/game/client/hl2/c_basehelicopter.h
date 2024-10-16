//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include "c_ai_basenpc.h"


class C_BaseHelicopter : public C_AI_BaseNPC {
public:
	DECLARE_CLASS( C_BaseHelicopter, C_AI_BaseNPC );
	DECLARE_CLIENTCLASS();

	C_BaseHelicopter();

	float StartupTime() const { return m_flStartupTime; }

private:
	C_BaseHelicopter( const C_BaseHelicopter& other ) {}
	float m_flStartupTime;
};
