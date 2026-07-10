project( tier2 C CXX )

set( TIER2_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${TIER2_DIR}/vconfig.cpp"
	"${TIER2_DIR}/tier2.cpp"
	"${TIER2_DIR}/tier2dm.cpp"

	# Private Header files
#	"${TIER2_DIR}/memalloc.hpp"

	# Public Source files

	# Public Header files
	"${SRC_DIR}/public/tier2/beamsegdraw.h"
	"${SRC_DIR}/public/tier2/camerautils.h"
	"${SRC_DIR}/public/tier2/fileutils.h"
	"${SRC_DIR}/public/tier2/keybindings.h"
	"${SRC_DIR}/public/tier2/meshutils.h"
	"${SRC_DIR}/public/tier2/p4helpers.h"
	"${SRC_DIR}/public/tier2/renderutils.h"
	"${SRC_DIR}/public/tier2/riff.h"
	"${SRC_DIR}/public/tier2/soundutils.h"
	"${SRC_DIR}/public/tier2/tier2.h"
	"${SRC_DIR}/public/tier2/tier2dm.h"
	"${SRC_DIR}/public/tier2/utlstreambuffer.h"
	"${SRC_DIR}/public/tier2/vconfig.h"
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

add_library( tier2 STATIC )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/tier2" )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
)
