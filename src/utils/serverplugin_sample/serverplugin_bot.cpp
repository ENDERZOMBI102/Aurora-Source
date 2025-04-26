//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Basic BOT handling.
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================//
#include "interface.h"
#include "filesystem.h"
#undef VECTOR_NO_SLOW_OPERATIONS
#include "mathlib/vector.h"

#include "../../game/shared/in_buttons.h"
#include "../../game/shared/shareddefs.h"
#include "convar.h"
#include "edict.h"
#include "eiface.h"
#include "game/server/iplayerinfo.h"
#include "igameevents.h"
#include "vstdlib/random.h"
#include "engine/IEngineTrace.h"

extern IBotManager* botmanager;
extern IUniformRandomStream* randomStr;
extern IVEngineServer* engine;
extern IEngineTrace* enginetrace;
extern IPlayerInfoManager* playerinfomanager;// game dll interface to interact with players
extern IServerPluginHelpers* helpers;        // special 3rd party plugin helpers from the engine

extern CGlobalVars* gpGlobals;

ConVar bot_forcefireweapon{ "plugin_bot_forcefireweapon", "", 0, "Force bots with the specified weapon to fire." };
ConVar bot_forceattack2{ "plugin_bot_forceattack2", "0", 0, "When firing, use attack2." };
ConVar bot_forceattackon{ "plugin_bot_forceattackon", "0", 0, "When firing, don't tap fire, hold it down." };
ConVar bot_flipout{ "plugin_bot_flipout", "0", 0, "When on, all bots fire their guns." };
ConVar bot_changeclass{ "plugin_bot_changeclass", "0", 0, "Force all bots to change to the specified class." };
static ConVar bot_mimic{ "plugin_bot_mimic", "0", 0, "Bot uses usercmd of player by index." };
static ConVar bot_mimic_yaw_offset{ "plugin_bot_mimic_yaw_offset", "0", 0, "Offsets the bot yaw." };

ConVar bot_sendcmd{ "plugin_bot_sendcmd", "", 0, "Forces bots to send the specified command." };
ConVar bot_crouch{ "plugin_bot_crouch", "0", 0, "Bot crouches" };


// This is our bot class.
class CPluginBot {
public:
	CPluginBot() = default;

	bool m_bBackwards{ false };

	float m_flNextTurnTime{ 0 };
	bool m_bLastTurnToRight{ false };

	float m_flNextStrafeTime{ 0 };
	float m_flSideMove{ 0 };

	QAngle m_ForwardAngle{};
	QAngle m_LastAngles{};

	IBotController* m_BotInterface{ nullptr };
	IPlayerInfo* m_PlayerInfo{ nullptr };
	edict_t* m_BotEdict{ nullptr };
};

CUtlVector<CPluginBot> s_Bots{};

void Bot_Think( CPluginBot* pBot );

// Handler for the "bot" command.
void BotAdd_f() {
	if ( not botmanager ) {
		return;
	}

	static int s_BotNum = 0;
	char botName[ 64 ];
	Q_snprintf( botName, sizeof( botName ), "Bot_%i", s_BotNum );
	s_BotNum++;

	if ( edict_t* botEdict = botmanager->CreateBot( botName ) ) {
		int botIndex = s_Bots.AddToTail();
		CPluginBot& bot = s_Bots[ botIndex ];
		bot.m_BotInterface = botmanager->GetBotController( botEdict );
		bot.m_PlayerInfo = playerinfomanager->GetPlayerInfo( botEdict );
		bot.m_BotEdict = botEdict;
		Assert( bot.m_BotInterface );
	}
}

ConCommand cc_Bot{ "plugin_bot_add", BotAdd_f, "Add a bot." };


//-----------------------------------------------------------------------------
// Purpose: Run through all the Bots in the game and let them think.
//-----------------------------------------------------------------------------
void Bot_RunAll() {
	if ( not botmanager ) {
		return;
	}

	for ( int i = 0; i < s_Bots.Count(); i++ ) {
		CPluginBot& bot = s_Bots[ i ];
		if ( bot.m_BotEdict->IsFree() or not bot.m_BotEdict->GetUnknown() or not bot.m_PlayerInfo->IsConnected() ) {
			s_Bots.Remove( i );
			--i;
		} else {
			Bot_Think( &bot );
		}
	}
}

bool Bot_RunMimicCommand( CBotCmd& cmd ) {
	if ( bot_mimic.GetInt() <= 0 ) {
		return false;
	}

	if ( bot_mimic.GetInt() > gpGlobals->maxClients ) {
		return false;
	}

	IPlayerInfo* playerInfo = playerinfomanager->GetPlayerInfo( engine->PEntityOfEntIndex( bot_mimic.GetInt() ) );
	if ( not playerInfo ) {
		return false;
	}

	cmd = playerInfo->GetLastUserCommand();
	cmd.viewangles[ YAW ] += bot_mimic_yaw_offset.GetFloat();

	if ( bot_crouch.GetInt() ) {
		cmd.buttons |= IN_DUCK;
	}

	return true;
}

void Bot_UpdateStrafing( CPluginBot* pBot, CBotCmd& cmd ) {
	if ( gpGlobals->curtime >= pBot->m_flNextStrafeTime ) {
		pBot->m_flNextStrafeTime = gpGlobals->curtime + 1.0f;

		if ( randomStr->RandomInt( 0, 5 ) == 0 ) {
			pBot->m_flSideMove = -600.0f + 1200.0f * randomStr->RandomFloat( 0, 2 );
		} else {
			pBot->m_flSideMove = 0;
		}
		cmd.sidemove = pBot->m_flSideMove;

		if ( randomStr->RandomInt( 0, 20 ) == 0 ) {
			pBot->m_bBackwards = true;
		} else {
			pBot->m_bBackwards = false;
		}
	}
}

void Bot_UpdateDirection( CPluginBot* pBot ) {
	float angledelta = 15.0;

	int maxtries = static_cast<int>( 360.0 / angledelta );

	if ( pBot->m_bLastTurnToRight ) {
		angledelta = -angledelta;
	}

	QAngle angle( pBot->m_BotInterface->GetLocalAngles() );

	trace_t trace;
	Vector forward;
	while ( --maxtries >= 0 ) {
		AngleVectors( angle, &forward );

		Vector vecSrc = pBot->m_BotInterface->GetLocalOrigin() + Vector( 0, 0, 36 );
		Vector vecEnd = vecSrc + forward * 10;

		Ray_t ray;
		ray.Init( vecSrc, vecEnd, Vector( -16, -16, 0 ), Vector( 16, 16, 72 ) );
		CTraceFilterWorldAndPropsOnly traceFilter;
		enginetrace->TraceRay( ray, MASK_PLAYERSOLID, &traceFilter, &trace );

		if ( trace.fraction == 1.0 ) {
			if ( gpGlobals->curtime < pBot->m_flNextTurnTime ) {
				break;
			}
		}

		angle.y += angledelta;

		if ( angle.y > 180 ) {
			angle.y -= 360;
		} else if ( angle.y < -180 ) {
			angle.y += 360;
		}

		pBot->m_flNextTurnTime = gpGlobals->curtime + 2.0f;
		pBot->m_bLastTurnToRight = randomStr->RandomInt( 0, 1 ) == 0;

		pBot->m_ForwardAngle = angle;
		pBot->m_LastAngles = angle;
	}

	pBot->m_BotInterface->SetLocalAngles( angle );
}


void Bot_FlipOut( CPluginBot* pBot, CBotCmd& cmd ) {
	if ( bot_flipout.GetInt() > 0 and not pBot->m_PlayerInfo->IsDead() ) {
		if ( bot_forceattackon.GetBool() or RandomFloat( 0.0, 1.0 ) > 0.5 ) {
			cmd.buttons |= bot_forceattack2.GetBool() ? IN_ATTACK2 : IN_ATTACK;
		}

		if ( bot_flipout.GetInt() >= 2 ) {
			pBot->m_LastAngles += RandomAngle( -1, 1 );  // add random offset to the angle

			for ( int i = 0; i < 2; i++ ) {
				if ( fabs( pBot->m_LastAngles[ i ] - pBot->m_ForwardAngle[ i ] ) > 15.0f ) {
					if ( pBot->m_LastAngles[ i ] > pBot->m_ForwardAngle[ i ] ) {
						pBot->m_LastAngles[ i ] = pBot->m_ForwardAngle[ i ] + 15;
					} else {
						pBot->m_LastAngles[ i ] = pBot->m_ForwardAngle[ i ] - 15;
					}
				}
			}

			pBot->m_LastAngles[ 2 ] = 0;

			pBot->m_BotInterface->SetLocalAngles( pBot->m_LastAngles );
		}
	}
}


void Bot_HandleSendCmd( const CPluginBot* pBot ) {
	if ( strlen( bot_sendcmd.GetString() ) > 0 ) {
		//send the cmd from this bot
		helpers->ClientCommand( pBot->m_BotEdict, bot_sendcmd.GetString() );

		bot_sendcmd.SetValue( "" );
	}
}


// If bots are being forced to fire a weapon, see if I have it
void Bot_ForceFireWeapon( const CPluginBot* pBot, CBotCmd& cmd ) {
	if ( Q_strlen( bot_forcefireweapon.GetString() ) > 0 ) {
		pBot->m_BotInterface->SetActiveWeapon( bot_forcefireweapon.GetString() );
		bot_forcefireweapon.SetValue( "" );
		// Start firing
		// Some weapons require releases, so randomise firing
		if ( bot_forceattackon.GetBool() or RandomFloat( 0.0, 1.0 ) > 0.5 ) {
			cmd.buttons |= bot_forceattack2.GetBool() ? IN_ATTACK2 : IN_ATTACK;
		}
	}
}


void Bot_SetForwardMovement( const CPluginBot* pBot, CBotCmd& cmd ) {
	if ( not pBot->m_BotInterface->IsEFlagSet( EFL_BOT_FROZEN ) ) {
		if ( pBot->m_PlayerInfo->GetHealth() == 100 ) {
			cmd.forwardmove = 600.f * ( pBot->m_bBackwards ? -1.f : 1.f );
			if ( pBot->m_flSideMove != 0.0f ) {
				cmd.forwardmove *= randomStr->RandomFloat( 0.1, 1.0f );
			}
		} else {
			// Stop when shot
			cmd.forwardmove = 0;
		}
	}
}


void Bot_HandleRespawn( const CPluginBot* pBot, CBotCmd& ) {
	// Wait for Reinforcement wave
	if ( pBot->m_PlayerInfo->IsDead() ) {
		if ( pBot->m_PlayerInfo->GetTeamIndex() == 0 ) {
			helpers->ClientCommand( pBot->m_BotEdict, "joingame" );
			helpers->ClientCommand( pBot->m_BotEdict, "jointeam 3" );
			helpers->ClientCommand( pBot->m_BotEdict, "joinclass 0" );
		}
	}
}


//-----------------------------------------------------------------------------
// Run this Bot's AI for one frame.
//-----------------------------------------------------------------------------
void Bot_Think( CPluginBot* pBot ) {
	CBotCmd cmd;
	Q_memset( &cmd, 0, sizeof( cmd ) );

	// Finally, override all this stuff if the bot is being forced to mimic a player.
	if ( not Bot_RunMimicCommand( cmd ) ) {
		cmd.sidemove = pBot->m_flSideMove;

		if ( not pBot->m_PlayerInfo->IsDead() ) {
			Bot_SetForwardMovement( pBot, cmd );

			// Only turn if I haven't been hurt
			if ( not pBot->m_BotInterface->IsEFlagSet( EFL_BOT_FROZEN ) and pBot->m_PlayerInfo->GetHealth() == 100 ) {
				Bot_UpdateDirection( pBot );
				Bot_UpdateStrafing( pBot, cmd );
			}

			// Handle console settings.
			Bot_ForceFireWeapon( pBot, cmd );
			Bot_HandleSendCmd( pBot );
		} else {
			Bot_HandleRespawn( pBot, cmd );
		}

		Bot_FlipOut( pBot, cmd );

		cmd.viewangles = pBot->m_BotInterface->GetLocalAngles();
		cmd.upmove = 0;
		cmd.impulse = 0;
	}

	pBot->m_BotInterface->RunPlayerMove( &cmd );
}
