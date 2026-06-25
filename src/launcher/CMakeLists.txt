project( launcher CXX )

set( LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Project files
	"${LAUNCHER_DIR}/launcher.cpp"
	"${LAUNCHER_DIR}/gameapploader.cpp"
	"${LAUNCHER_DIR}/gameapploader.hpp"
	"${LAUNCHER_DIR}/sourcemutex.cpp"
	"${LAUNCHER_DIR}/sourcemutex.hpp"
	"${LAUNCHER_DIR}/launchermgr.cpp"
	"${LAUNCHER_DIR}/launchermgr.hpp"

	# Common files
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/idedicatedexports.h"
	"${SRC_DIR}/public/engine/hlds_api.h"
	"${SRC_DIR}/public/engine/launcher_api.hpp"
)

# Preprocessor defs
set( DEFINES )

# Platform-specific preprocessor defines
set( WIN32_DEFINES   )
set( POSIX32_DEFINES )
set( WIN64_DEFINES   )
set( POSIX64_DEFINES )
set( WINDOWS_DEFINES )
set( POSIX_DEFINES   )

add_library( launcher MODULE )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( launcher
	PRIVATE
		tier0
		tier1
		vstdlib
		appframework
		tier2
		tier3
		mathlib
		SDL3-shared
)
