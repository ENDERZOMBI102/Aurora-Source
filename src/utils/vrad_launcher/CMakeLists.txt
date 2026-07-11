project( vrad_launcher C CXX )

set( VRAD_LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VRAD_LAUNCHER_DIR}/vrad_launcher.cpp"

	# Public Header files
	"${SRC_DIR}/public/tier1/interface.h"
	"${SRC_DIR}/public/ivraddll.h"
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
set( OUTPUT_FILE_NAME "vrad" )

add_executable( vrad_launcher )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )
if ( ${IS_WINDOWS} AND NOT ${IS_64BIT} )
	target_link_options( vrad_launcher PRIVATE "/LARGEADDRESSAWARE" )
endif ()
target_link_libraries( vrad_launcher
	PRIVATE
		tier0
		tier1
		vstdlib
		sourcepp::steampp
)
add_dependencies( vrad_launcher vrad_dll )
