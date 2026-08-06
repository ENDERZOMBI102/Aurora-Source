project( bootstrap C CXX )

set( BOOTSTRAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${BOOTSTRAP_DIR}/main.cpp"
)

# Set the output file name
set( OUTPUT_FILE_NAME "aurosrc" )

add_executable( ${PROJECT_NAME} )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		${CMAKE_DL_LIBS}
)

add_dependencies( ${PROJECT_NAME} launcher )
