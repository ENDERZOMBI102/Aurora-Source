project( vrad_launcher C CXX )

set( VRAD_LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VRAD_LAUNCHER_DIR}/vrad_launcher.cpp"

	# Public Header files
	"${SRC_DIR}/public/tier1/interface.h"
	"${SRC_DIR}/public/ivraddll.h"
)

# Set the output file name
set( OUTPUT_FILE_NAME "vrad" )

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

if ( ${IS_WINDOWS} AND NOT ${IS_64BIT} )
	target_link_options( ${PROJECT_NAME}
		PRIVATE
			"/LARGEADDRESSAWARE"
	)
endif ()
asource_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
		vstdlib
		sourcepp::steampp
)
add_dependencies( ${PROJECT_NAME} vrad_dll )
