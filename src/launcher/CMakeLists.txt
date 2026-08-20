project( launcher CXX )

set( LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files
	"${LAUNCHER_DIR}/launcher.cpp"
	"${LAUNCHER_DIR}/gameapploader.cpp"
	"${LAUNCHER_DIR}/gameapploader.hpp"
	"${LAUNCHER_DIR}/sourcemutex.cpp"
	"${LAUNCHER_DIR}/sourcemutex.hpp"
	"${LAUNCHER_DIR}/launchermgr.cpp"
	"${LAUNCHER_DIR}/launchermgr.hpp"

	# Public Source/Header files
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/filesystem_init.h"
	"${SRC_DIR}/public/idedicatedexports.h"
	"${SRC_DIR}/public/engine/hlds_api.h"
	"${SRC_DIR}/public/engine/launcher_api.hpp"
)

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
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
