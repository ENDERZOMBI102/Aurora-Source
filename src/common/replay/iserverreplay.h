//========= Copyright Valve Corporation, All rights reserved. ============//
//
//=======================================================================================//
#pragma once
#include "interface.h"


#define SERVER_REPLAY_INTERFACE_VERSION "ServerReplay001"


class IReplayFactory;
class KeyValues;

//
// Allows the replay DLL to talk to the server
//
class IServerReplay : public IBaseInterface {
public:
	virtual void UploadOgsData( KeyValues* pData, bool bIncludeTimeField ) = 0;
};