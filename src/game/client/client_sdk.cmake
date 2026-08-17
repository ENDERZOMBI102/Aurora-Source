# client_sdk.cmake
set( PROJECT "client_sdk" )

list( APPEND SOURCE_FILES
	# Source Files
	"${CLIENT_DIR}/c_team_objectiveresource.cpp"
	"${CLIENT_DIR}/c_team_objectiveresource.h"
	"${CLIENT_DIR}/c_team_train_watcher.cpp"
	"${CLIENT_DIR}/c_team_train_watcher.h"
	"${CLIENT_DIR}/hud_voicestatus.cpp"
	"${SRC_DIR}/game/shared/predicted_viewmodel.cpp"
	"${SRC_DIR}/game/shared/predicted_viewmodel.h"
	"${SRC_DIR}/game/shared/teamplay_round_timer.cpp"
	"${SRC_DIR}/game/shared/teamplay_round_timer.h"

	# HL2 DLL
	"${SRC_DIR}/game/shared/script_intro_shared.cpp"

	# SDK
	"${CLIENT_DIR}/sdk/c_sdk_env_sparkler.cpp"
	"${CLIENT_DIR}/sdk/c_sdk_player.cpp"
	"${CLIENT_DIR}/sdk/c_sdk_player.h"
	"${CLIENT_DIR}/sdk/c_sdk_team.cpp"
	"${CLIENT_DIR}/sdk/c_sdk_team.h"
	"${CLIENT_DIR}/sdk/c_te_firebullets.cpp"
	"${CLIENT_DIR}/sdk/c_weapon_stubs_midn.cpp"
	"${CLIENT_DIR}/sdk/clientmode_sdk.cpp"
	"${CLIENT_DIR}/sdk/clientmode_sdk.h"
	"${CLIENT_DIR}/sdk/sdk_fx_impacts.cpp"
	"${CLIENT_DIR}/sdk/sdk_fx_weaponfx.cpp"
	"${CLIENT_DIR}/sdk/sdk_hud_ammo.cpp"
	"${CLIENT_DIR}/sdk/sdk_hud_health.cpp"
	"${CLIENT_DIR}/sdk/sdk_hud_message.cpp"
	"${CLIENT_DIR}/sdk/sdk_hud_weaponselection.cpp"
	"${CLIENT_DIR}/sdk/sdk_in_main.cpp"
	"${CLIENT_DIR}/sdk/sdk_prediction.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_gamerules.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_gamerules.h"
	"${SRC_DIR}/game/shared/sdk/sdk_player_shared.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_player_shared.h"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_parse.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_parse.h"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_melee.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_weapon_melee.h"
	"${SRC_DIR}/game/shared/sdk/sdk_usermessages.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playeranimstate.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playeranimstate.h"
	"${SRC_DIR}/game/shared/sdk/sdk_fx_shared.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_fx_shared.h"
	"${SRC_DIR}/game/shared/sdk/sdk_basegrenade_projectile.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_basegrenade_projectile.h"
	"${SRC_DIR}/game/shared/sdk/sdk_gamemovement.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playerclass_info_parse.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_playerclass_info_parse.h"
	"${SRC_DIR}/game/shared/sdk/sdk_shareddefs.cpp"
	"${SRC_DIR}/game/shared/sdk/sdk_shareddefs.h"

	# SDK->vgui
	"${CLIENT_DIR}/sdk/vgui/sdkviewport.cpp"
	"${CLIENT_DIR}/sdk/vgui/sdkviewport.h"
	"${CLIENT_DIR}/sdk/vgui/vgui_rootpanel_sdk.cpp"
	"${CLIENT_DIR}/sdk/vgui/vgui_rootpanel_sdk.h"

	# SDK->Weapons
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
set( OUTPUT_FILE_NAME "client" )
# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/mod_sdk/bin" )

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_include_directories(
	PRIVATE
		"${CLIENT_DIR}/sdk/vgui"
		"${CLIENT_DIR}/sdk"
		"${SRC_DIR}/game/shared/sdk"
)
asource_compile_definitions(
	PRIVATE
		SDKDLL
)
