# server_sdk.cmake
set( PROJECT "server_sdk" )

set( SOURCE_FILES
	"${SERVER_DIR}/ai_relationship.cpp"
	"${SERVER_DIR}/basegrenade_concussion.cpp"
	"${SERVER_DIR}/basegrenade_contact.cpp"
	"${SERVER_DIR}/basegrenade_timed.cpp"
	"${SERVER_DIR}/EntityFlame.h"
	"${SERVER_DIR}/hl2/Func_Monitor.cpp"
	"${SERVER_DIR}/grenadethrown.cpp"
	"${SERVER_DIR}/grenadethrown.h"
	"${SERVER_DIR}/h_cycler.cpp"
	"${SERVER_DIR}/h_cycler.h"
	"${SERVER_DIR}/monstermaker.cpp"
	"${SERVER_DIR}/monstermaker.h"
	"${SERVER_DIR}/physics_bone_follower.h"
	"${SRC_DIR}/game/shared/predicted_viewmodel.cpp"
	"${SRC_DIR}/game/shared/predicted_viewmodel.h"
	"${SRC_DIR}/game/shared/ragdoll_shared.h"
	"${SRC_DIR}/game/shared/solidsetdefaults.h"
	"${SRC_DIR}/game/shared/hl2/survival_gamerules.cpp"
	"${SERVER_DIR}/team_objectiveresource.cpp"
	"${SERVER_DIR}/team_objectiveresource.h"
	"${SERVER_DIR}/team_spawnpoint.cpp"
	"${SERVER_DIR}/team_spawnpoint.h"
	"${SERVER_DIR}/team_control_point.cpp"
	"${SERVER_DIR}/team_control_point.h"
	"${SERVER_DIR}/team_control_point_master.cpp"
	"${SERVER_DIR}/team_control_point_master.h"
	"${SERVER_DIR}/team_control_point_round.cpp"
	"${SERVER_DIR}/team_control_point_round.h"
	"${SERVER_DIR}/team_train_watcher.cpp"
	"${SERVER_DIR}/team_train_watcher.h"
	"${SRC_DIR}/game/shared/teamplayroundbased_gamerules.cpp"
	"${SRC_DIR}/game/shared/touchlink.h"
	"${SERVER_DIR}/trigger_area_capture.cpp"
	"${SERVER_DIR}/trigger_area_capture.h"
	"${SRC_DIR}/game/shared/teamplay_round_timer.cpp"
	"${SRC_DIR}/game/shared/teamplay_round_timer.h"

	# HL2 DLL
	"${SERVER_DIR}/npc_talker.cpp"
	"${SERVER_DIR}/npc_talker.h"
	"${SRC_DIR}/game/shared/script_intro_shared.cpp"
	"${SERVER_DIR}/weapon_cubemap.cpp"

	# SDK
	"${SERVER_DIR}/sdk/sdk_bot_temp.cpp"
	"${SERVER_DIR}/sdk/sdk_bot_temp.h"
	"${SERVER_DIR}/sdk/sdk_client.cpp"
	"${SERVER_DIR}/sdk/sdk_gameinterface.cpp"
	#"${SERVER_DIR}/sdk/sdk_gameinterface.h"

	# Entities
	"${SERVER_DIR}/sdk/sdk_logicalentity.cpp"
	"${SERVER_DIR}/sdk/sdk_modelentity.cpp"
	"${SERVER_DIR}/sdk/sdk_brushentity.cpp"
	"${SERVER_DIR}/sdk/sdk_vehicle_jeep.cpp"
	"${SERVER_DIR}/sdk/sdk_env_message.cpp"
	"${SERVER_DIR}/sdk/sdk_env_sparkler.cpp"

	"${SERVER_DIR}/sdk/sdk_team.cpp"
	"${SERVER_DIR}/sdk/sdk_team.h"
	"${SERVER_DIR}/sdk/sdk_eventlog.cpp"
	
	"${SRC_DIR}/game/shared/sdk/sdk_gamerules.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_gamerules.h"

	# Player
	"${SERVER_DIR}/sdk/sdk_player.cpp"
	"${SERVER_DIR}/sdk/sdk_player.h"
	"${SERVER_DIR}/sdk/sdk_playermove.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_player_shared.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_player_shared.h"
	"${SRC_DIR}/game/shared/sdk/sdk_playerclass_info_parse.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playerclass_info_parse.h"
	"${SRC_DIR}/game/shared/sdk/sdk_playeranimstate.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playeranimstate.h"

	"${SRC_DIR}/game/shared/sdk/sdk_gamemovement.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_usermessages.cpp"

	# weapon code
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_parse.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_parse.h"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_melee.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_melee.h"
	
	"${SRC_DIR}/game/shared/sdk/sdk_fx_shared.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_fx_shared.h"
	"${SRC_DIR}/game/shared/sdk/sdk_basegrenade_projectile.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_basegrenade_projectile.h"
	"${SRC_DIR}/game/shared/sdk/sdk_shareddefs.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_shareddefs.h"

	# SDK->Weapons
	"${SERVER_DIR}/sdk/te_firebullets.cpp"
	"${SERVER_DIR}/sdk/te_firebullets.h"
	"${SRC_DIR}/game/shared/sdk/weapon_sdkbase.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_sdkbase.h"
	"${SRC_DIR}/game/shared/sdk/weapon_basesdkgrenade.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_basesdkgrenade.h"
	"${SRC_DIR}/game/shared/sdk/weapon_crowbar.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_grenade.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_grenade.h"
	"${SRC_DIR}/game/shared/sdk/weapon_mp5.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_pistol.cpp"
	"${SRC_DIR}/game/shared/sdk/weapon_shotgun.cpp"
)

# Set the output file name
set( OUTPUT_FILE_NAME "server" )
# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/mod_sdk/bin" )

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_include_directories(
	PRIVATE
		"${SERVER_DIR}/sdk"
		"${SRC_DIR}/game/shared/sdk"
)
asource_compile_definitions(
	PRIVATE
		SDKDLL
)

if ( ${IS_SOURCESDK} )
	target_use_nav_mesh( ${PROJECT} )
endif()
