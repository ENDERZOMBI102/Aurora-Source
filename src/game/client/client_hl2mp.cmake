# client_hl2mp.cmake
set( PROJECT "client_hl2mp" )

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
	"${CLIENT_DIR}/episodic/c_vort_charge_token.cpp"
	"${SRC_DIR}/game/shared/hl2/basehlcombatweapon_shared.cpp"
	"${CLIENT_DIR}/hl2/c_antlion_dust.cpp"
	"${CLIENT_DIR}/hl2/c_ar2_explosion.cpp"
	"${CLIENT_DIR}/hl2/c_barnacle.cpp"
	"${CLIENT_DIR}/hl2/c_barney.cpp"
	"${CLIENT_DIR}/hl2/c_basehelicopter.cpp"
	"${CLIENT_DIR}/hl2/c_basehelicopter.h"
	"${CLIENT_DIR}/hl2/c_basehlcombatweapon.cpp"
	"${CLIENT_DIR}/hl2/c_basehlcombatweapon.h"
	"${CLIENT_DIR}/hl2/c_basehlplayer.cpp"
	"${CLIENT_DIR}/hl2/c_basehlplayer.h"
	"${CLIENT_DIR}/hl2/c_citadel_effects.cpp"
	"${CLIENT_DIR}/hl2/c_corpse.cpp"
	"${CLIENT_DIR}/hl2/c_corpse.h"
	"${CLIENT_DIR}/hl2/c_env_alyxtemp.cpp"
	"${CLIENT_DIR}/hl2/c_env_headcrabcanister.cpp"
	"${CLIENT_DIR}/hl2/c_env_starfield.cpp"
	"${CLIENT_DIR}/hl2/c_func_tankmortar.cpp"
	"${CLIENT_DIR}/hl2/c_hl2_playerlocaldata.cpp"
	"${CLIENT_DIR}/hl2/c_hl2_playerlocaldata.h"
	"${CLIENT_DIR}/hl2/c_info_teleporter_countdown.cpp"
	"${CLIENT_DIR}/hl2/c_npc_antlionguard.cpp"
	"${CLIENT_DIR}/hl2/c_npc_combinegunship.cpp"
	"${CLIENT_DIR}/hl2/c_npc_manhack.cpp"
	"${CLIENT_DIR}/hl2/c_npc_rollermine.cpp"
	"${CLIENT_DIR}/hl2/c_plasma_beam_node.cpp"
	"${CLIENT_DIR}/hl2/c_prop_combine_ball.cpp"
	"${CLIENT_DIR}/hl2/c_prop_combine_ball.h"
	"${CLIENT_DIR}/hl2/c_rotorwash.cpp"
	"${CLIENT_DIR}/hl2/c_script_intro.cpp"
	"${SRC_DIR}/game/shared/script_intro_shared.cpp"
	"${CLIENT_DIR}/hl2/c_strider.cpp"
	"${CLIENT_DIR}/hl2/c_te_concussiveexplosion.cpp"
	"${CLIENT_DIR}/hl2/c_te_flare.cpp"
	"${CLIENT_DIR}/hl2/c_thumper_dust.cpp"
	"${CLIENT_DIR}/hl2/c_vehicle_airboat.cpp"
	"${CLIENT_DIR}/hl2/c_vehicle_cannon.cpp"
	"${CLIENT_DIR}/hl2/c_vehicle_crane.cpp"
	"${CLIENT_DIR}/hl2/c_vehicle_crane.h"
	"${CLIENT_DIR}/hl2/c_vehicle_prisoner_pod.cpp"
	"${CLIENT_DIR}/hl2/c_weapon__stubs_hl2.cpp"
	"${CLIENT_DIR}/hl2/c_weapon_crossbow.cpp"
	"${SRC_DIR}/game/shared/hl2/citadel_effects_shared.h"
	"${SRC_DIR}/game/shared/hl2/env_headcrabcanister_shared.cpp"
	"${SRC_DIR}/game/shared/hl2/env_headcrabcanister_shared.h"
	"${CLIENT_DIR}/hl2/fx_antlion.cpp"
	"${CLIENT_DIR}/hl2/fx_bugbait.cpp"
	"${CLIENT_DIR}/hl2/fx_hl2_impacts.cpp"
	"${CLIENT_DIR}/hl2/fx_hl2_tracers.cpp"
	"${CLIENT_DIR}/hl2/hl2_clientmode.cpp"
	"${SRC_DIR}/game/shared/hl2/hl2_gamerules.cpp"
	"${SRC_DIR}/game/shared/hl2/hl2_gamerules.h"
	"${SRC_DIR}/game/shared/hl2/hl2_shareddefs.h"
	"${SRC_DIR}/game/shared/hl2/hl2_usermessages.cpp"
	"${SRC_DIR}/game/shared/hl2/hl_gamemovement.cpp"
	"${SRC_DIR}/game/shared/hl2/hl_gamemovement.h"
	"${CLIENT_DIR}/hl2/hl_in_main.cpp"
	"${CLIENT_DIR}/hl2/hl_prediction.cpp"
	"${CLIENT_DIR}/hl2/hud_ammo.cpp"
	"${CLIENT_DIR}/hl2/hud_battery.cpp"
	"${CLIENT_DIR}/hl2/hud_blood.cpp"
	"${CLIENT_DIR}/hl2/hud_credits.cpp"
	"${CLIENT_DIR}/hl2/hud_damageindicator.cpp"
	"${CLIENT_DIR}/hl2/hud_flashlight.cpp"
	"${CLIENT_DIR}/hl2/hud_health.cpp"
	"${CLIENT_DIR}/hl2/hud_poisondamageindicator.cpp"
	"${CLIENT_DIR}/hl2/hud_quickinfo.cpp"
	"${CLIENT_DIR}/hud_squadstatus.cpp"
	"${CLIENT_DIR}/hl2/hud_suitpower.cpp"
	"${CLIENT_DIR}/hl2/hud_suitpower.h"
	"${CLIENT_DIR}/hl2/hud_weaponselection.cpp"
	"${CLIENT_DIR}/hl2/hud_zoom.cpp"
	"${CLIENT_DIR}/hl2/shieldproxy.cpp"
	"${CLIENT_DIR}/hl2/vgui_rootpanel_hl2.cpp"

	# HL2MP
	"${CLIENT_DIR}/hl2mp/c_hl2mp_player.cpp"
	"${CLIENT_DIR}/hl2mp/c_hl2mp_player.h"
	"${CLIENT_DIR}/hl2mp/c_te_hl2mp_shotgun_shot.cpp"
	"${CLIENT_DIR}/hl2mp/clientmode_hl2mpnormal.cpp"
	"${CLIENT_DIR}/hl2mp/clientmode_hl2mpnormal.h"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_gamerules.cpp"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_gamerules.h"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_player_shared.cpp"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_player_shared.h"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_weapon_parse.cpp"
	"${SRC_DIR}/game/shared/hl2mp/hl2mp_weapon_parse.h"

	# HL2MP->Weapons
	"${SRC_DIR}/game/shared/hl2mp/weapon_357.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_ar2.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_ar2.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_crossbow.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_crowbar.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_frag.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbase.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbase.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbase_machinegun.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbase_machinegun.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbasebasebludgeon.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbasehlmpcombatweapon.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_hl2mpbasehlmpcombatweapon.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_physcannon.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_physcannon.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_pistol.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_rpg.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_rpg.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_shotgun.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_slam.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_slam.h"
	"${SRC_DIR}/game/shared/hl2mp/weapon_smg1.cpp"
	"${SRC_DIR}/game/shared/hl2mp/weapon_stunstick.cpp"

	# HL2MP->UI
	"${CLIENT_DIR}/hl2mp/ui/backgroundpanel.cpp"
	"${CLIENT_DIR}/hl2mp/ui/backgroundpanel.h"
	"${CLIENT_DIR}/hl2mp/hl2mp_hud_chat.cpp"
	"${CLIENT_DIR}/hl2mp/hl2mp_hud_chat.h"
	"${CLIENT_DIR}/hl2mp/hl2mp_hud_target_id.cpp"
	"${CLIENT_DIR}/hl2mp/hl2mp_hud_team.cpp"
	"${CLIENT_DIR}/hl2mp/ui/hl2mpclientscoreboard.cpp"
	"${CLIENT_DIR}/hl2mp/ui/hl2mpclientscoreboard.h"
	"${CLIENT_DIR}/hl2mp/ui/hl2mptextwindow.cpp"
	"${CLIENT_DIR}/hl2mp/ui/hl2mptextwindow.h"
	"${CLIENT_DIR}/hl2mp/hud_deathnotice.cpp"
)

# Set the output file name
set( OUTPUT_FILE_NAME "client" )
# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/mod_hl2mp/bin" )

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_include_directories(
	PRIVATE
		"${CLIENT_DIR}/hl2mp/ui"
		"${CLIENT_DIR}/hl2mp"
		"${SRC_DIR}/game/shared/hl2mp"
		"${CLIENT_DIR}/hl2"
		"${CLIENT_DIR}/hl2/elements"
		"${SRC_DIR}/game/shared/hl2"
)
asource_compile_definitions(
	PRIVATE
		HL2MP
		HL2_CLIENT_DLL
)