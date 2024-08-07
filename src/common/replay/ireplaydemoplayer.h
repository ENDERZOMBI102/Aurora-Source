//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=======================================================================================//
#pragma once
#include "interface.h"
#include "replay/replay.h"


#define INTERFACEVERSION_REPLAYDEMOPLAYER "ReplayDemoPlayer001"

//
// Interface for replay demo player
//
class IReplayDemoPlayer : public IBaseInterface {
public:
	virtual void PlayReplay( ReplayHandle_t hReplay, int iPerformance ) = 0;
	virtual void PlayNextReplay() = 0;
	virtual void ClearReplayList() = 0;
	virtual void AddReplayToList( ReplayHandle_t hReplay, int iPerformance ) = 0;
	virtual CReplay* GetCurrentReplay() = 0;
	virtual CReplayPerformance* GetCurrentPerformance() = 0;// The playing replay, or NULL if playing the original replay
	virtual void PauseReplay() = 0;
	virtual bool IsReplayPaused() = 0;
	virtual void ResumeReplay() = 0;
	virtual void OnSignonStateFull() = 0;
};
