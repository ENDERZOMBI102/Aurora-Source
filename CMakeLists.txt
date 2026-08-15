cmake_minimum_required( VERSION 3.27 FATAL_ERROR )

# Pre-configure checks
if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR )
	message( FATAL_ERROR "Prevented in-tree build. Please create a `build` directory and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there" )
endif ()
if ( APPLE )
	message( FATAL_ERROR "Aurora Source has discontinued OSX support, please use either Windows or Linux." )
endif ()
set( IS_64BIT 0 )
if ( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
	if ( NOT "${ASOURCE_SKIP_x86_CHECK}" )
		message( FATAL_ERROR "Aurora Source only supports 32-bit generation for now" )
	endif ()
	set( IS_64BIT 1 )
endif ()

# Setup configuration types
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE )

project(
	AuroraSource
		VERSION 0.1.0
		DESCRIPTION "A \"branch\" of the source engine, forked off SDK 2013's codebase."
		HOMEPAGE_URL "https://github.com/ENDERZOMBI102/Aurora-Source"
		LANGUAGES CXX C ASM
)

# For some reason, checking if CMAKE_BUILD_TYPE is defined is unreliable
# So simply check if it's empty instead
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "" )
	set( CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE )
endif()

# Platform-dependant constants
set( IS_WINDOWS 0 )
set( IS_LINUX 0 )
set( IS_OSX 0 )
set( IS_POSIX 0 )
if ( WIN32 )
	set( IS_WINDOWS 1 )
	if ( IS_64BIT )
		set( platSubDir "/win64" )
	else ()
		set( platSubDir "" )
	endif ()
	set( CMAKE_IMPORT_LIBRARY_SUFFIX ".lib" )
elseif ( UNIX )
	set( IS_POSIX 1 )
	if ( LINUX )
		set( IS_LINUX 1 )
		if ( IS_64BIT )
			set( platSubDir "/linux64" )
		else ()
			set( platSubDir "/linux32" )
		endif ()
	endif()
endif()

# Various path constants we use all around the scripts
set( ROOT_DIR         "${CMAKE_CURRENT_LIST_DIR}" )
set( SRC_DIR          "${CMAKE_CURRENT_LIST_DIR}/src" )
set( GAME_DIR         "${CMAKE_CURRENT_LIST_DIR}/game" )
set( THIRDPARTY_DIR   "${CMAKE_CURRENT_LIST_DIR}/thirdparty" )
set( CMAKESCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/_cmake_scripts" )
set( LIBPUBLIC_DIR    "${SRC_DIR}/lib/public${platSubDir}" )
set( LIBCOMMON_DIR    "${SRC_DIR}/lib/common${platSubDir}" )
unset( platSubDir )

# Configuration options for the user
include( "${CMAKESCRIPTS_DIR}/options.cmake" )

# Init "project" properties
foreach ( type IN ITEMS "Executable" "Game" "Library" "Module" )
	set_property( DIRECTORY ${ROOT_DIR} PROPERTY ASOURCE_${type} "" )
endforeach ()

# Setup cmake standards
set( CMAKE_C_STANDARD 23 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET "hidden" )
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET "hidden" )
set( CMAKE_SKIP_RPATH OFF )
set( CMAKE_INSTALL_RPATH "$ORIGIN" )
set( CMAKE_BUILD_WITH_INSTALL_RPATH ON )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${GAME_DIR}/bin/" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${GAME_DIR}/bin/" )
set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Import third-party libraries
if ( NOT ${ASOURCE_3RD_PARTY_LOGS} )
	set( CMAKE_MESSAGE_LOG_LEVEL "WARNING" )
endif ()
include( "${THIRDPARTY_DIR}/init.cmake" )
set( CMAKE_MESSAGE_LOG_LEVEL "STATUS" )

# Setup build group infra
include( "${CMAKESCRIPTS_DIR}/groups.cmake" )

# Import the projects
# -- Libraries
add_group_subdir( "${SRC_DIR}/tier0"                    IN "game" "compilers" "shaders" )
add_group_subdir( "${SRC_DIR}/utils/lzma"               IN        "compilers" "shaders" )
add_group_subdir( "${SRC_DIR}/tier1"                    IN "game" "compilers" "shaders" )
add_group_subdir( "${SRC_DIR}/vstdlib"                  IN "game" "compilers" )
add_group_subdir( "${SRC_DIR}/mathlib"                  IN "game" "compilers" "shaders" )
add_group_subdir( "${SRC_DIR}/tier2"                    IN "game" "compilers" )
add_group_subdir( "${SRC_DIR}/tier3"                    IN "game" )
add_group_subdir( "${SRC_DIR}/fgdlib"                   IN        "compilers" )
add_group_subdir( "${SRC_DIR}/bitmap"                   IN "game" "compilers" )
add_group_subdir( "${SRC_DIR}/vtf"                      IN "game" "compilers" )
add_group_subdir( "${SRC_DIR}/appframework"             )
add_group_subdir( "${SRC_DIR}/raytrace"                 IN "game" "compilers" )
add_group_subdir( "${SRC_DIR}/materialsystem/shaderlib" IN                    "shaders" )
add_group_subdir( "${SRC_DIR}/vgui2/vgui_controls"      IN "game" )
# -- Modules
add_group_subdir( "${SRC_DIR}/filesystem_stdio"            IN        "compilers" )
add_group_subdir( "${SRC_DIR}/utils/togl"                  LINUX_ONLY )
add_group_subdir( "${SRC_DIR}/materialsystem/stdshaders"   IN "game"             "shaders" )
add_group_subdir( "${SRC_DIR}/launcher"                    )
add_group_subdir( "${SRC_DIR}/utils/serverplugin_sample"   )
#add_group_subdir( "${SRC_DIR}/game/client"                 IN "game" )
#add_group_subdir( "${SRC_DIR}/game/server"                 IN "game" )

# -- Executables
add_group_subdir( "${SRC_DIR}/bootstrap"             )
add_group_subdir( "${SRC_DIR}/utils/captioncompiler" IN "compilers" )
add_group_subdir( "${SRC_DIR}/utils/vbsp"            IN "compilers" )
add_group_subdir( "${SRC_DIR}/utils/vvis"            IN "compilers" )
add_group_subdir( "${SRC_DIR}/utils/vvis_launcher"   IN "compilers" )
add_group_subdir( "${SRC_DIR}/utils/vrad"            IN "compilers" )
add_group_subdir( "${SRC_DIR}/utils/vrad_launcher"   IN "compilers" )
#add_group_subdir( "${SRC_DIR}/utils/height2normal"   WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/motionmapper"    WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/qc_eyes"         WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/tgadiff"         WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/vice"            WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/vtf2tga"         WINDOWS_ONLY )
#add_group_subdir( "${SRC_DIR}/utils/vtfdiff"         WINDOWS_ONLY )


# Print info
block()
	set( targets "" )
	set( targetCount 0 )
	foreach ( type IN ITEMS "Executable" "Game" "Library" "Module" )
		get_property( values DIRECTORY ${ROOT_DIR} PROPERTY ASOURCE_${type} )
		# number of targets
		list( LENGTH values count )
		math( EXPR targetCount "${targetCount} + ${count}" )
		# joint target list
		string( JOIN ", " string ${values} )
		# spaces after type name
		string( LENGTH "${type}" typeLen )
		math( EXPR spacesLen "11 - ${typeLen}" )
		string( REPEAT " " ${spacesLen} spaces )
		# final string
		set( targets  "${targets}${type}${spaces}: ${string}\n" )
	endforeach ()

	message( NOTICE "\n--- Aurora Source ---" )
	message( NOTICE "CMake      : v${CMAKE_VERSION}" )
	message( NOTICE "Platform   : ${CMAKE_SYSTEM_NAME}" )
	message( NOTICE "Compiler   : ${CMAKE_C_COMPILER}, ${CMAKE_CXX_COMPILER}" )
	message( NOTICE "Build group: ${BUILD_GROUP} (${targetCount} targets)" )
	message( NOTICE "Game       : ${BUILD_GAME}" )
	message( NOTICE "64bit build: ${IS_64BIT}" )
	message( NOTICE "---    Targets    ---" )
	message( NOTICE "${targets}" )
endblock()
