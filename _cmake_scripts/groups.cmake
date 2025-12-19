# groups.cmake

# get what build groups we support
get_property( BUILD_GROUPS CACHE "BUILD_GROUP" PROPERTY "STRINGS" )

# group_include( $path IN $group0 $group1 ... [WINDOWS_ONLY] )
#   All included projects are assumed to be cross-platform,
#   it is up to the maintainer to mark them as closed-platform with the respective options.
function( group_include path )
	cmake_parse_arguments( GP "WINDOWS_ONLY" "" "IN" ${ARGN} )

	# check pre-conditions...
	if ( ${GP_WINDOWS_ONLY} AND NOT ${IS_WINDOWS} )
		message( NOTICE "- Skipping ${path} because we are NOT targeting Windows" )
		return()
	elseif ( NOT (${BUILD_GROUP} IN_LIST GP_IN) )
		message( NOTICE "- Skipping ${path} because it is NOT in the current build group" )
		return()
	endif ()

	# all pre-conditions were met, lets add it!
	message( NOTICE "- Including ${path}" )
	include( ${path} )

	# check that all declared build groups have been defined, so to be consistent
	foreach ( GROUP ${GP_IN} )
		if ( NOT (${GROUP} IN_LIST BUILD_GROUPS) )
			message( WARNING "  * Unknown build group used: `${GROUP}`, was this intentional?" )
		endif ()
	endforeach ()
endfunction()


if ( NOT DEFINED BUILD_GROUP )
	message( FATAL_ERROR "No build group was passed, please choose one of the following: ${BUILD_GROUPS}" )
elseif ( NOT ("${BUILD_GROUP}" IN_LIST BUILD_GROUPS) )
	message( FATAL_ERROR "Invalid build group `${BUILD_GROUP}`, valid groups are: ${BUILD_GROUPS}" )
endif()

include( "${SRCDIR}/lib/statics.cmake" )  # TODO: Remove when not needed anymore

message( NOTICE "Projects   :" )

# libraries
group_include( "${SRCDIR}/tier0/tier0.cmake"                           IN "everything" "game" "compilers" "shaders" )
group_include( "${SRCDIR}/vstdlib/vstdlib.cmake"                       IN "everything" "game" "compilers" )
group_include( "${SRCDIR}/tier1/tier1.cmake"                           IN "everything" "game" "compilers" "shaders" )
group_include( "${SRCDIR}/tier2/tier2.cmake"                           IN "everything" "game" "compilers" )
group_include( "${SRCDIR}/tier3/tier3.cmake"                           IN "everything" "game" )
group_include( "${SRCDIR}/appframework/appframework.cmake"             IN "everything" )
group_include( "${SRCDIR}/utils/lzma/lzma.cmake"                       IN "everything"        "compilers" "shaders" )
group_include( "${SRCDIR}/mathlib/mathlib.cmake"                       IN "everything" "game" "compilers" "shaders" )
group_include( "${SRCDIR}/raytrace/raytrace.cmake"                     IN "everything" "game" "compilers" )
group_include( "${SRCDIR}/raytrace_cuda/raytrace_cuda.cmake"           IN                     "compilers" )
group_include( "${SRCDIR}/vgui2/vgui_controls/vgui_controls.cmake"     IN "everything" "game" )
group_include( "${SRCDIR}/fgdlib/fgdlib.cmake"                         IN "everything"        "compilers" )
group_include( "${SRCDIR}/bitmap/bitmap.cmake"                         IN "everything" )
group_include( "${SRCDIR}/materialsystem/shaderlib/shaderlib.cmake"    IN "everything"                    "shaders" )

# modules
group_include( "${SRCDIR}/filesystem_stdio/filesystem_stdio.cmake"     IN "everything"        "compilers" )
group_include( "${SRCDIR}/launcher/launcher.cmake"                     IN "everything" )
group_include( "${SRCDIR}/inputsystem/inputsystem.cmake"               IN "everything" )
group_include( "${SRCDIR}/utils/togl/togl.cmake"                       IN "everything" )

# map compilers
group_include( "${SRCDIR}/utils/vbsp/vbsp.cmake"                       IN "everything"        "compilers" )
group_include( "${SRCDIR}/utils/vrad/vrad_dll.cmake"                   IN "everything"        "compilers" )
group_include( "${SRCDIR}/utils/vrad_launcher/vrad_launcher.cmake"     IN "everything"        "compilers" )
group_include( "${SRCDIR}/utils/vvis/vvis_dll.cmake"                   IN "everything"        "compilers" )
group_include( "${SRCDIR}/utils/vvis_launcher/vvis_launcher.cmake"     IN "everything"        "compilers" )

# the game
group_include( "${SRCDIR}/game/client/client_${BUILD_GAME}.cmake"      IN "everything" "game" )
group_include( "${SRCDIR}/game/server/server_${BUILD_GAME}.cmake"      IN "everything" "game" )
group_include( "${SRCDIR}/materialsystem/stdshaders/game_shader_dx9_${BUILD_GAME}.cmake" IN "everything" "shaders" )

# tools
group_include( "${SRCDIR}/utils/captioncompiler/captioncompiler.cmake" IN "everything" )
# those are still windows-only for now...
group_include( "${SRCDIR}/utils/height2normal/height2normal.cmake"     IN "everything" WINDOWS_ONLY )
group_include( "${SRCDIR}/utils/motionmapper/motionmapper.cmake"       IN "everything" WINDOWS_ONLY )
#group_include( "${SRCDIR}/utils/qc_eyes/qc_eyes.cmake"                 IN "everything" WINDOWS_ONLY )
group_include( "${SRCDIR}/utils/tgadiff/tgadiff.cmake"                 IN "everything" WINDOWS_ONLY )
group_include( "${SRCDIR}/utils/vice/vice.cmake"                       IN "everything" WINDOWS_ONLY )
group_include( "${SRCDIR}/utils/vtf2tga/vtf2tga.cmake"                 IN "everything" WINDOWS_ONLY )
group_include( "${SRCDIR}/utils/vtfdiff/vtfdiff.cmake"                 IN "everything" WINDOWS_ONLY )

# misc
group_include( "${SRCDIR}/utils/serverplugin_sample/serverplugin_empty.cmake" IN "everything" )
group_include( "${SRCDIR}/bootstrap/bootstrap.cmake"                   IN "everything" )


# If we can, declare additional dependencies
if ( ${BUILD_GROUP} STREQUAL "everything" )
	add_dependencies( "client_${BUILD_GAME}" bootstrap filesystem_stdio togl launcher #[[inputsystem]] )
	add_dependencies( "server_${BUILD_GAME}" bootstrap #[[inputsystem launcher]] )
endif ()
