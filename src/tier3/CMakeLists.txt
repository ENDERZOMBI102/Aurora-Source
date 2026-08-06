project( tier3 C CXX )

set( TIER3_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${TIER3_DIR}/tier3.cpp"
	"${TIER3_DIR}/scenetokenprocessor.cpp"
	"${TIER3_DIR}/mdlutils.cpp"
	"${TIER3_DIR}/choreoutils.cpp"

	# Private Header files
	"${TIER3_DIR}/scenetokenprocessor.hpp"

	# Public Source files

	# Public Header files
	"${SRC_DIR}/public/tier3/choreoutils.h"
	"${SRC_DIR}/public/tier3/mdlutils.h"
	"${SRC_DIR}/public/tier3/scenetokenprocessor.h"
	"${SRC_DIR}/public/tier3/tier3.h"
	"${SRC_DIR}/public/tier3/tier3dm.h"
)

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/tier3" )

add_library( ${PROJECT_NAME} STATIC )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
)
