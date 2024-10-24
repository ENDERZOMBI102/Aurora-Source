//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:
//
//=============================================================================//
#pragma once
#include <bitvec.h>
#include <const.h>
#include <inetmsghandler.h>

class INetMessage;
class IRecipientFilter;
class IClient;

typedef struct player_info_s player_info_t;

abstract_class IServer : public IConnectionlessPacketHandler {
public:
	virtual ~IServer() {}

	virtual int GetNumClients() const = 0;      // returns current number of clients
	virtual int GetNumProxies() const = 0;      // returns number of attached HLTV proxies
	virtual int GetNumFakeClients() const = 0;  // returns number of fake clients/bots
	virtual int GetMaxClients() const = 0;      // returns current client limit
	virtual IClient* GetClient( int index ) = 0;// returns interface to client
	virtual int GetClientCount() const = 0;     // returns number of clients slots (used & unused)
	virtual int GetUDPPort() const = 0;         // returns current used UDP port
	virtual float GetTime() const = 0;          // returns game world time
	virtual int GetTick() const = 0;            // returns game world tick
	virtual float GetTickInterval() const = 0;  // tick interval in seconds
	virtual const char* GetName() const = 0;    // public server name
	virtual const char* GetMapName() const = 0; // current map name (BSP)
	virtual int GetSpawnCount() const = 0;
	virtual int GetNumClasses() const = 0;
	virtual int GetClassBits() const = 0;
	virtual void GetNetStats( float& avgIn, float& avgOut ) = 0;// total net in/out in bytes/sec
	virtual int GetNumPlayers() = 0;
	virtual bool GetPlayerInfo( int nClientIndex, player_info_t* pinfo ) = 0;

	virtual bool IsActive() const = 0;
	virtual bool IsLoading() const = 0;
	virtual bool IsDedicated() const = 0;
	virtual bool IsPaused() const = 0;
	virtual bool IsMultiplayer() const = 0;
	virtual bool IsPausable() const = 0;
	virtual bool IsHLTV() const = 0;
	virtual bool IsReplay() const = 0;

	virtual const char* GetPassword() const = 0;// returns the password or NULL if none set

	virtual void SetPaused( bool paused ) = 0;
	virtual void SetPassword( const char* password ) = 0;// set password (NULL to disable)

	virtual void BroadcastMessage( INetMessage & msg, bool onlyActive = false, bool reliable = false ) = 0;
	virtual void BroadcastMessage( INetMessage & msg, IRecipientFilter & filter ) = 0;

	virtual void DisconnectClient( IClient * client, const char* reason ) = 0;
};
