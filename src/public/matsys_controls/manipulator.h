//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================
#pragma once
#include "mathlib/vector.h"
#include "vgui_controls/Panel.h"

//-----------------------------------------------------------------------------
// Manipulator interface
//-----------------------------------------------------------------------------
class IManipulator {
public:
	virtual ~IManipulator() {}
	virtual void OnBeginManipulation() = 0;
	virtual void OnAcceptManipulation() = 0;
	virtual void OnCancelManipulation() = 0;

	virtual void OnTick() = 0;

	virtual void OnCursorMoved( int x, int y ) = 0;
	virtual void OnMousePressed( vgui::MouseCode code, int x, int y ) = 0;
	virtual void OnMouseReleased( vgui::MouseCode code, int x, int y ) = 0;
	virtual void OnMouseWheeled( int delta ) = 0;

	virtual void SetViewportSize( int w, int h ) = 0;
};


//-----------------------------------------------------------------------------
// Base class helper for implementing manipulators
//-----------------------------------------------------------------------------
class CBaseManipulator : public IManipulator {
public:
	CBaseManipulator() {
		m_nViewport[ 0 ] = m_nViewport[ 1 ] = 0;
	}

	virtual void OnTick() {};

	virtual void OnBeginManipulation() {}
	virtual void OnAcceptManipulation() {};
	virtual void OnCancelManipulation() {};

	virtual void OnCursorMoved( int x, int y ) {};
	virtual void OnMousePressed( vgui::MouseCode code, int x, int y ) {};
	virtual void OnMouseReleased( vgui::MouseCode code, int x, int y ) {};
	virtual void OnMouseWheeled( int delta ) {};

	virtual void SetViewportSize( int w, int h ) {
		m_nViewport[ 0 ] = w;
		m_nViewport[ 1 ] = h;
	}

protected:
	int m_nViewport[ 2 ];
};


//-----------------------------------------------------------------------------
// Base class for manipulators which operate on transforms
//-----------------------------------------------------------------------------
class CTransformManipulator : public CBaseManipulator {
public:
	CTransformManipulator( matrix3x4_t* pTransform );

	void SetTransform( matrix3x4_t* transform );
	matrix3x4_t* GetTransform();

protected:
	matrix3x4_t* m_pTransform;
};


//-----------------------------------------------------------------------------
// Standard maya-like transform manipulator
//-----------------------------------------------------------------------------
class CPotteryWheelManip : public CTransformManipulator {
public:
	CPotteryWheelManip( matrix3x4_t* pTransform );

	virtual void OnBeginManipulation();
	virtual void OnAcceptManipulation();
	virtual void OnCancelManipulation();

	virtual void OnTick();

	virtual void OnCursorMoved( int x, int y );
	virtual void OnMousePressed( vgui::MouseCode code, int x, int y );
	virtual void OnMouseReleased( vgui::MouseCode code, int x, int y );
	virtual void OnMouseWheeled( int delta );

	// Sets the zoom level
	void SetZoom( float flZoom );

protected:
	int m_lastx, m_lasty;

	float m_zoom;
	float m_altitude, m_azimuth;
	//vec3 m_lookat

	float m_prevZoom;
	float m_prevAltitude, m_prevAzimuth;

	float m_flLastMouseTime;
	float m_flLastTickTime;
	float m_flSpin;
	bool m_bSpin;

	void UpdateTransform();
	void UpdateZoom( float delta );
};
