project( raytrace C CXX )

set( RAYTRACE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Sources
	"${RAYTRACE_DIR}/raytrace.cpp"
	"${RAYTRACE_DIR}/trace2.cpp"
	"${RAYTRACE_DIR}/trace3.cpp"
)

# Preprocessor defs
set( DEFINES "" )

# Platform-specific preprocessor defines
set( WIN32_DEFINES   )
set( POSIX32_DEFINES )
set( WIN64_DEFINES   )
set( POSIX64_DEFINES )
set( WINDOWS_DEFINES )
set( POSIX_DEFINES   )

add_library( raytrace STATIC )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )
target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
		mathlib
)
target_include_directories( raytrace
	PRIVATE
		"${SRC_DIR}/utils/common"
)
