project( vtf C CXX )

set( VTF_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VTF_DIR}/cvtf.cpp"

	# Private Header files
	"${VTF_DIR}/cvtf.hpp"

	# Public Source files

	# Public Header files
	"${SRC_DIR}/public/vtf/vtf.h"
)

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/vtf" )

add_library( vtf STATIC )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		mathlib
		bitmap
		sourcepp::vtfpp
)
