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

# Preprocessor defs
set( DEFINES )

# Platform-specific preprocessor defines
set( WIN32_DEFINES   )
set( POSIX32_DEFINES )
set( WIN64_DEFINES   )
set( POSIX64_DEFINES )
set( WINDOWS_DEFINES )
set( POSIX_DEFINES   )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/vtf" )

add_library( vtf STATIC )

include( ${CMAKESCRIPTS_DIR}/project-base.cmake )
target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		mathlib
		bitmap
		sourcepp::vtfpp
)
