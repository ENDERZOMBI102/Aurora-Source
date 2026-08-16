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
	"${SRC_DIR}/public/appframework/ilaunchermgr.h"
	"${SRC_DIR}/public/appframework/tier2app.h"
	"${SRC_DIR}/public/appframework/tier3app.h"
	"${SRC_DIR}/public/appframework/vguimatsysapp.h"
)

# Target type
# Target type
set( KIND "STATIC" )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/appframework" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier0
        tier1
        vstdlib
        SDL3-shared
)
