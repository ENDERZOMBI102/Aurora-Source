project( bootstrap C CXX )

set( BOOTSTRAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${BOOTSTRAP_DIR}/main.cpp"
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
set( OUTPUT_FILE_NAME "aurosrc" )

add_executable( bootstrap )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( bootstrap
	PRIVATE
		${CMAKE_DL_LIBS}
)
