# inputsystem.cmake

set( APPFRAMEWORK_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( APPFRAMEWORK_SOURCE_FILES
	# Sources
	"${APPFRAMEWORK_DIR}/appsystemgroup.cpp"

	# Public units
	"${SRCDIR}/public/filesystem_init.cpp"

	# Public headers
	"${SRCDIR}/public/filesystem_init.h"
	"${SRCDIR}/public/appframework/AppFramework.h"
	"${SRCDIR}/public/appframework/IAppSystem.h"
	"${SRCDIR}/public/appframework/IAppSystemGroup.h"
	"${SRCDIR}/public/appframework/AppFramework.h"
	"${SRCDIR}/public/appframework/ilaunchermgr.h"
	"${SRCDIR}/public/appframework/tier2app.h"
	"${SRCDIR}/public/appframework/tier3app.h"
	"${SRCDIR}/public/appframework/VguiMatSysApp.h"
)

add_library( appframework STATIC ${APPFRAMEWORK_SOURCE_FILES} )

target_include_directories( appframework
	PRIVATE
		"${SRCDIR}/common"
		"${SRCDIR}/public"
)
target_link_libraries( appframework
	PRIVATE
		tier0
		vstdlib
)
