project( tier0 C CXX )

set( TIER3_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
#	"${TIER3_DIR}/dbg.cpp"

	# Header files
#	"${TIER3_DIR}/memalloc.hpp"

	# Public
	"${SRC_DIR}/public/tier3/choreoutils.h"
	"${SRC_DIR}/public/tier3/mdlutils.h"
	"${SRC_DIR}/public/tier3/scenetokenprocessor.h"
	"${SRC_DIR}/public/tier3/tier3.h"
	"${SRC_DIR}/public/tier3/tier3dm.h"
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

add_library( tier3 IMPORTED STATIC )
set_target_properties( tier3
	PROPERTIES
		IMPORTED_LOCATION "${LIBPUBLIC_DIR}/tier3${CMAKE_IMPORT_LIBRARY_SUFFIX}"
)
