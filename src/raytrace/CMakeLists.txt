project( raytrace C CXX )

set( RAYTRACE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Sources
	"${RAYTRACE_DIR}/raytrace.cpp"
	"${RAYTRACE_DIR}/trace2.cpp"
	"${RAYTRACE_DIR}/trace3.cpp"
)

add_library( ${PROJECT_NAME} STATIC )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
		mathlib
)
target_include_directories( ${PROJECT_NAME}
	PRIVATE
		"${SRC_DIR}/utils/common"
)
