project( vstdlib C CXX )

set( VSTDLIB_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VSTDLIB_DIR}/cvarsystem.cpp"
	"${VSTDLIB_DIR}/random.cpp"
	"${VSTDLIB_DIR}/keyvaluessystem.cpp"
	"${VSTDLIB_DIR}/pcgengine.cpp"
	"${VSTDLIB_DIR}/jobthread.cpp"
	"${VSTDLIB_DIR}/osversion.cpp"
	"${VSTDLIB_DIR}/processutils.cpp"
	"${VSTDLIB_DIR}/cvar.cpp"

	# Private Header files
	"${VSTDLIB_DIR}/cvarsystem.hpp"
	"${VSTDLIB_DIR}/jobthread.hpp"
	"${VSTDLIB_DIR}/keyvaluessystem.hpp"
	"${VSTDLIB_DIR}/processutils.hpp"

	# Public Source files

	# Public Header files
	"${SRC_DIR}/public/vstdlib/vstdlib.h"
	"${SRC_DIR}/public/vstdlib/vcover.h"
	"${SRC_DIR}/public/vstdlib/random.h"
	"${SRC_DIR}/public/vstdlib/osversion.h"
	"${SRC_DIR}/public/vstdlib/jobthread.h"
	"${SRC_DIR}/public/vstdlib/iprocessutils.h"
	"${SRC_DIR}/public/vstdlib/IKeyValuesSystem.h"
	"${SRC_DIR}/public/vstdlib/cvar.h"
	"${SRC_DIR}/public/vstdlib/coroutine.h"
	"${SRC_DIR}/public/vstdlib/pcgengine.hpp"
)

# Target type
set( KIND "SHARED" )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/vstdlib" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

if ( NOT ${TRGT_IMPORTED} )
	target_link_libraries( ${PROJECT_NAME}
		PRIVATE
			tier0
			tier1
	)
	target_compile_definitions( ${PROJECT_NAME}
		PRIVATE
			"VSTDLIB_DLL_EXPORT"
	)
endif ()
