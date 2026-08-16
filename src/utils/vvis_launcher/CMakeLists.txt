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

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		tier0
		tier1
		${CMAKE_DL_LIBS}
)

add_dependencies( ${PROJECT_NAME} vvis_dll #[[filesystem_stdio]] )
