project( raytrace C CXX )

set( RAYTRACE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files
	"${RAYTRACE_DIR}/raytrace.cpp"
	"${RAYTRACE_DIR}/trace2.cpp"
	"${RAYTRACE_DIR}/trace3.cpp"
)

# Target type
set( KIND "STATIC" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

asource_link_libraries(
	PRIVATE
		tier0
		tier1
		mathlib
)
asource_include_directories(
	PRIVATE
		"${SRC_DIR}/utils/common"
)
