//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Team management class. Contains all the details for a specific team
//
// $NoKeywords: $
//=============================================================================//
#pragma once
#include "shareddefs.h"
#include "utlvector.h"

class CBasePlayer;
class CTeamSpawnPoint;

class CTeam : public CBaseEntity {
	DECLARE_CLASS( CTeam, CBaseEntity );

public:
	CTeam();
	virtual ~CTeam();

	DECLARE_SERVERCLASS();

	virtual void Precache() { };

	virtual void Think();
	virtual int UpdateTransmitState();

	//-----------------------------------------------------------------------------
	// Initialization
	//-----------------------------------------------------------------------------
	virtual void Init( const char* pName, int iNumber );

	//-----------------------------------------------------------------------------
	// Data Handling
	//-----------------------------------------------------------------------------
	virtual int GetTeamNumber() const;
	virtual const char* GetName();
	virtual void UpdateClientData( CBasePlayer* pPlayer );
	virtual bool ShouldTransmitToPlayer( CBasePlayer* pRecipient, CBaseEntity* pEntity );

	//-----------------------------------------------------------------------------
	// Spawnpoints
	//-----------------------------------------------------------------------------
	virtual void InitializeSpawnpoints();
	virtual void AddSpawnpoint( CTeamSpawnPoint* pSpawnpoint );
	virtual void RemoveSpawnpoint( CTeamSpawnPoint* pSpawnpoint );
	virtual CBaseEntity* SpawnPlayer( CBasePlayer* pPlayer );

	//-----------------------------------------------------------------------------
	// Players
	//-----------------------------------------------------------------------------
	virtual void InitializePlayers();
	virtual void AddPlayer( CBasePlayer* pPlayer );
	virtual void RemovePlayer( CBasePlayer* pPlayer );
	virtual int GetNumPlayers();
	virtual CBasePlayer* GetPlayer( int iIndex );

	//-----------------------------------------------------------------------------
	// Scoring
	//-----------------------------------------------------------------------------
	virtual void AddScore( int iScore );
	virtual void SetScore( int iScore );
	virtual int GetScore();
	virtual void ResetScores();

	// Round scoring
	virtual int GetRoundsWon() { return m_iRoundsWon; }
	virtual void SetRoundsWon( int iRounds ) { m_iRoundsWon = iRounds; }
	virtual void IncrementRoundsWon() { m_iRoundsWon++; }

	void AwardAchievement( int iAchievement );

	virtual int GetAliveMembers();

public:
	CUtlVector<CTeamSpawnPoint*> m_aSpawnPoints;
	CUtlVector<CBasePlayer*> m_aPlayers;

	// Data
	CNetworkString( m_szTeamname, MAX_TEAM_NAME_LENGTH );
	CNetworkVar( int, m_iScore );
	CNetworkVar( int, m_iRoundsWon );
	int m_iDeaths;

	// Spawnpoints
	int m_iLastSpawn;// Index of the last spawnpoint used

	CNetworkVar( int, m_iTeamNum );// Which team is this?
};

extern CUtlVector<CTeam*> g_Teams;
extern CTeam* GetGlobalTeam( int iIndex );
extern int GetNumberOfTeams();
