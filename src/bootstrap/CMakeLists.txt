project( bootstrap C CXX )

set( BOOTSTRAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${BOOTSTRAP_DIR}/main.cpp"
)

# Set the output file name
set( OUTPUT_FILE_NAME "aurosrc" )

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		${CMAKE_DL_LIBS}
)
