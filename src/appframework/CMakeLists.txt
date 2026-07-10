project( appframework CXX )

set( APPFRAMEWORK_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Sources
	"${APPFRAMEWORK_DIR}/appsystemgroup.cpp"
	"${APPFRAMEWORK_DIR}/appframework.cpp"

	# Public units
	"${SRC_DIR}/public/filesystem_init.cpp"

	# Public headers
	"${SRC_DIR}/public/filesystem_init.h"
	"${SRC_DIR}/public/appframework/AppFramework.h"
	"${SRC_DIR}/public/appframework/IAppSystem.h"
	"${SRC_DIR}/public/appframework/IAppSystemGroup.h"
	"${SRC_DIR}/public/appframework/AppFramework.h"
	"${SRC_DIR}/public/appframework/ilaunchermgr.h"
	"${SRC_DIR}/public/appframework/tier2app.h"
	"${SRC_DIR}/public/appframework/tier3app.h"
	"${SRC_DIR}/public/appframework/VguiMatSysApp.h"
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

add_library( appframework STATIC )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/appframework" )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( appframework
	PRIVATE
		tier0
		tier1
		vstdlib
		SDL3-shared
)
