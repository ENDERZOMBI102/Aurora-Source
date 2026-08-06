project( vvis_launcher C CXX )

set( VVIS_LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VVIS_LAUNCHER_DIR}/vvis_launcher.cpp"

	# Public Header files
	"${SRC_DIR}/public/tier1/interface.h"
)

# Set the output file name
set( OUTPUT_FILE_NAME "vvis" )

add_executable( ${PROJECT_NAME} )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
		${CMAKE_DL_LIBS}
)

add_dependencies( ${PROJECT_NAME} vvis_dll #[[filesystem_stdio]] )
