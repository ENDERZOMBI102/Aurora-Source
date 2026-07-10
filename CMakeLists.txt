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
	if ( NOT "${ASRC_SKIP_x86_CHECK}" )
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

# Setup cmake standards
set( CMAKE_C_STANDARD 23 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_VISIBILITY_PRESET hidden )
set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_VISIBILITY_PRESET hidden )
set( CMAKE_BUILD_RPATH_USE_ORIGIN 1 )
set( CMAKE_BUILD_RPATH $ORIGIN )
set( CMAKE_INSTALL_RPATH $ORIGIN )
set( CMAKE_BUILD_WITH_INSTALL_RPATH 1 )

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
	#	set( CMAKE_IMPORT_LIBRARY_SUFFIX ".a" )
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
	set_property( DIRECTORY ${ROOT_DIR} PROPERTY ASRC_${type} "" )
endforeach ()

# Import third-party libraries
if ( NOT ${ASRC_3RD_PARTY_LOGS} )
	set( CMAKE_MESSAGE_LOG_LEVEL "WARNING" )
endif ()
include( "${THIRDPARTY_DIR}/init.cmake" )
set( CMAKE_MESSAGE_LOG_LEVEL "STATUS" )

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
add_subdirectory( "${SRC_DIR}/materialsystem/shaderlib" )
# -- Modules
add_subdirectory( "${SRC_DIR}/filesystem_stdio" )
add_subdirectory( "${SRC_DIR}/launcher" )
# -- Executables
add_subdirectory( "${SRC_DIR}/bootstrap" )
add_subdirectory( "${SRC_DIR}/utils/vbsp" )
add_subdirectory( "${SRC_DIR}/utils/vvis" )
add_subdirectory( "${SRC_DIR}/utils/vvis_launcher" )

# Print info
block()
	set( targets "" )
	set( targetCount 0 )
	foreach ( type IN ITEMS "Executable" "Game" "Library" "Module" )
		get_property( values DIRECTORY ${ROOT_DIR} PROPERTY ASRC_${type} )
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
	message( NOTICE "Build group: ${BUILD_GROUP} (${targetCount} targets)" )
	message( NOTICE "Game       : ${BUILD_GAME}" )
	message( NOTICE "64bit build: ${IS_64BIT}" )
	message( NOTICE "---    Targets    ---" )
	message( NOTICE "${targets}" )
endblock()
