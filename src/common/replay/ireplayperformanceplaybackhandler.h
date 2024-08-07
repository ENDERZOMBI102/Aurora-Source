//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=======================================================================================//
#pragma once
#include "interface.h"
#include "replay/ireplayperformancecontroller.h"


class Vector;
class QAngle;


class IReplayPerformancePlaybackHandler : public IBaseInterface {
public:
	virtual void OnEvent_Camera_Change_FirstPerson( float flTime, int nEntityIndex ) = 0;
	virtual void OnEvent_Camera_Change_ThirdPerson( float flTime, int nEntityIndex ) = 0;
	virtual void OnEvent_Camera_Change_Free( float flTime ) = 0;
	virtual void OnEvent_Camera_ChangePlayer( float flTime, int nEntIndex ) = 0;
	virtual void OnEvent_Camera_SetView( const SetViewParams_t& params ) = 0;
	virtual void OnEvent_TimeScale( float flTime, float flScale ) = 0;
};
