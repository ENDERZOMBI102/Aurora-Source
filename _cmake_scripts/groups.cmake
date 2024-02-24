# groups.cmake

if (${BUILD_GROUP} STREQUAL "game")
	if (${BUILD_GAME} STREQUAL "hl2mp")
		include("${SRCDIR}/game/client/client_hl2mp.cmake")
		include("${SRCDIR}/game/server/server_hl2mp.cmake")
	endif()
	
	include("${SRCDIR}/mathlib/mathlib.cmake")
	include("${SRCDIR}/raytrace/raytrace.cmake")
	include("${SRCDIR}/tier1/tier1.cmake")
	include("${SRCDIR}/tier2/tier2.cmake")
	include("${SRCDIR}/tier3/tier3.cmake")
	include("${SRCDIR}/vgui2/vgui_controls/vgui_controls.cmake")

elseif (${BUILD_GROUP} STREQUAL "everything")
	if (${BUILD_GAME} STREQUAL "hl2mp")
		include("${SRCDIR}/game/client/client_hl2mp.cmake")
		include("${SRCDIR}/game/server/server_hl2mp.cmake")
		include("${SRCDIR}/materialsystem/stdshaders/game_shader_dx9_hl2mp.cmake")
	endif()

	if (${IS_WINDOWS})
		include("${SRCDIR}/utils/captioncompiler/captioncompiler.cmake")
		include("${SRCDIR}/utils/height2normal/height2normal.cmake")
		include("${SRCDIR}/utils/motionmapper/motionmapper.cmake")
#		include("${SRCDIR}/utils/qc_eyes/qc_eyes.cmake")
		include("${SRCDIR}/utils/tgadiff/tgadiff.cmake")
		include("${SRCDIR}/utils/vice/vice.cmake")
		include("${SRCDIR}/utils/vtf2tga/vtf2tga.cmake")
		include("${SRCDIR}/utils/vtfdiff/vtfdiff.cmake")
	endif()
	include("${SRCDIR}/tier0/tier0.cmake")
	include("${SRCDIR}/vstdlib/vstdlib.cmake")
	include("${SRCDIR}/tier1/tier1.cmake")
	include("${SRCDIR}/tier2/tier2.cmake")
	include("${SRCDIR}/tier3/tier3.cmake")
	include("${SRCDIR}/appframework/appframework.cmake")

	include("${SRCDIR}/fgdlib/fgdlib.cmake")
	include("${SRCDIR}/utils/vbsp/vbsp.cmake")
	include("${SRCDIR}/utils/vrad/vrad_dll.cmake")
	include("${SRCDIR}/utils/vrad_launcher/vrad_launcher.cmake")
	include("${SRCDIR}/utils/vvis/vvis_dll.cmake")
	include("${SRCDIR}/utils/vvis_launcher/vvis_launcher.cmake")

	include("${SRCDIR}/filesystem_stdio/filesystem_stdio.cmake")
	include("${SRCDIR}/bootstrap/bootstrap.cmake")
	include("${SRCDIR}/launcher/launcher.cmake")
	include("${SRCDIR}/inputsystem/inputsystem.cmake")
	include("${SRCDIR}/utils/lzma/lzma.cmake")
	include("${SRCDIR}/mathlib/mathlib.cmake")
	include("${SRCDIR}/raytrace/raytrace.cmake")
	include("${SRCDIR}/utils/serverplugin_sample/serverplugin_empty.cmake")
	include("${SRCDIR}/vgui2/vgui_controls/vgui_controls.cmake")

	# Declare additional dependencies
    add_dependencies( "client_${BUILD_GAME}" bootstrap inputsystem launcher filesystem_stdio )
    add_dependencies( "server_${BUILD_GAME}" bootstrap inputsystem launcher filesystem_stdio )

elseif (${BUILD_GROUP} STREQUAL "compilers")
	include("${SRCDIR}/tier0/tier0.cmake")
	include("${SRCDIR}/vstdlib/vstdlib.cmake")
	include("${SRCDIR}/appframework/appframework.cmake")
	include("${SRCDIR}/tier1/tier1.cmake")
	include("${SRCDIR}/tier2/tier2.cmake")
	include("${SRCDIR}/fgdlib/fgdlib.cmake")
	include("${SRCDIR}/filesystem_stdio/filesystem_stdio.cmake")
	include("${SRCDIR}/utils/vbsp/vbsp.cmake")
	include("${SRCDIR}/utils/vrad/vrad_dll.cmake")
	include("${SRCDIR}/utils/vrad_launcher/vrad_launcher.cmake")
	include("${SRCDIR}/utils/vvis/vvis_dll.cmake")
	include("${SRCDIR}/utils/lzma/lzma.cmake")
	include("${SRCDIR}/utils/vvis_launcher/vvis_launcher.cmake")
	include("${SRCDIR}/mathlib/mathlib.cmake")
	include("${SRCDIR}/raytrace/raytrace.cmake")
	include("${SRCDIR}/raytrace_cuda/raytrace_cuda.cmake")

elseif (${BUILD_GROUP} STREQUAL "shaders")
	if (${BUILD_GAME} STREQUAL "hl2mp")
		include("${SRCDIR}/materialsystem/stdshaders/game_shader_dx9_hl2mp.cmake")
	endif()

	include("${SRCDIR}/mathlib/mathlib.cmake")
	include("${SRCDIR}/tier1/tier1.cmake")
endif()