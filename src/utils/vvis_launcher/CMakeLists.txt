project( vvis_launcher C CXX )

set( VVIS_LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VVIS_LAUNCHER_DIR}/vvis_launcher.cpp"

	# Public Header files
	"${SRC_DIR}/public/tier1/interface.h"
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

# Set the output file name
set( OUTPUT_FILE_NAME "vvis" )

add_executable( vvis_launcher )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( vvis_launcher
	PRIVATE
		tier0
		tier1
		${CMAKE_DL_LIBS}
)
add_dependencies( vvis_launcher vvis_dll #[[filesystem_stdio]] )
