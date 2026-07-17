project( captioncompiler C CXX )

set( CAPTIONCOMPILER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${CAPTIONCOMPILER_DIR}/captioncompiler.cpp"
	"${SRC_DIR}/common/compiledcaptionswap.cpp"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"

	# Private Header files
	"${CAPTIONCOMPILER_DIR}/cbase.h"
	"${SRC_DIR}/utils/common/filesystem_tools.h"

	# Public Source files
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/public/filesystem_helpers.h"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/filesystem_init.h"
	"${SRC_DIR}/public/mathlib/mathlib.h"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/public/stringregistry.cpp"
	"${SRC_DIR}/public/stringregistry.h"
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

add_executable( captioncompiler )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )
target_include_directories( ${PROJECT_NAME}
	PRIVATE
		"${SRC_DIR}/utils/common"
		"${SRC_DIR}/game/shared"
)
target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		appframework
		tier1
		mathlib
		tier2
		tier3
)
