project( vtf C CXX )

set( VTF_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VTF_DIR}/vtf.cpp"
	"${VTF_DIR}/cvtf.cpp"

	# Private Header files
	"${VTF_DIR}/cvtf.hpp"

	# Public Source files

	# Public Header files
	"${SRC_DIR}/public/vtf/vtf.h"
)

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/vtf" )

# Target type
set( KIND "STATIC" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

asource_link_libraries(
    PRIVATE
        tier0
        mathlib
        bitmap
        sourcepp::vtfpp
)
