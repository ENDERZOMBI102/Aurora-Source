cmake_minimum_required( VERSION 3.27 FATAL_ERROR )

if ( CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR )
	message( FATAL_ERROR "Prevented in-tree build. Please create a `build` directory and run \"cmake -S ${CMAKE_SOURCE_DIR} -B .\" from there" )
endif ()
if ( APPLE )
	message( FATAL_ERROR "Aurora Source has discontinued OSX support, please use either Windows or Linux." )
endif ()
set( IS_64BIT 0 )
if ( "${CMAKE_SIZEOF_VOID_P}" EQUAL "8" )
	if ( NOT "${ASRC_SKIP_x86_CHECK}" )
		message( FATAL_ERROR "Aurora Source only supports 32-bit generation for now" )
	endif ()
	set( IS_64BIT 1 )
endif ()

set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE )

message( NOTICE "Running CMake v${CMAKE_VERSION}" )

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

# This is a way to emulate groups.vgc
set( BUILD_GROUP "game" CACHE STRING "Build Group" )
# For the CMake GUIs that support a combobox list
set_property( CACHE BUILD_GROUP PROPERTY STRINGS
	"everything"
	"game"
	"shaders"
	"compilers"
)

# Which game are we building?
set( BUILD_GAME "hl2mp" CACHE STRING "Build Game" )
set_property( CACHE BUILD_GAME PROPERTY STRINGS
	"hl2mp"
	"sdk"
)

set( ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}" )
set( SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src" )
set( GAME_DIR "${CMAKE_CURRENT_LIST_DIR}/game" )
set( THIRDPARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/thirdparty" )
set( CMAKESCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/_cmake_scripts" )
include( "${CMAKESCRIPTS_DIR}/project-init.cmake" )

# Setup third party BEFORE we "customize" our compilation process
include( "${THIRDPARTY_DIR}/init.cmake" )

set( LIBPUBLIC "${SRC_DIR}/lib/public${PLATSUBDIR}" )
set( LIBCOMMON "${SRC_DIR}/lib/common${PLATSUBDIR}" )

link_directories(
	${LIBPUBLIC}
	${LIBCOMMON}
)

include_directories(
	"${SRC_DIR}/common"
	"${SRC_DIR}/public"
	"${SRC_DIR}/public/tier0"
	"${SRC_DIR}/public/tier1"
)

message( NOTICE "\n--- Aurora Source ---" )
message( NOTICE "Platform   : ${CMAKE_SYSTEM_NAME}" )
message( NOTICE "Build group: ${BUILD_GROUP}" )
message( NOTICE "Game       : ${BUILD_GAME}" )
message( NOTICE "64bit build: ${IS_64BIT}" )

# Import the projects
# -- Libraries
add_subdirectory( "${SRC_DIR}/tier0" )
add_subdirectory( "${SRC_DIR}/tier1" )
add_subdirectory( "${SRC_DIR}/vstdlib" )
add_subdirectory( "${SRC_DIR}/tier2" )
add_subdirectory( "${SRC_DIR}/tier3" )
add_subdirectory( "${SRC_DIR}/mathlib" )
add_subdirectory( "${SRC_DIR}/fgdlib" )
add_subdirectory( "${SRC_DIR}/bitmap" )
add_subdirectory( "${SRC_DIR}/appframework" )
# -- Modules
add_subdirectory( "${SRC_DIR}/filesystem_stdio" )
add_subdirectory( "${SRC_DIR}/launcher" )
# -- Executables
add_subdirectory( "${SRC_DIR}/bootstrap" )
add_subdirectory( "${SRC_DIR}/utils/vbsp" )
add_subdirectory( "${SRC_DIR}/utils/vvis" )
add_subdirectory( "${SRC_DIR}/utils/vvis_launcher" )
