project( tier0 C CXX )

set( TIER0_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${TIER0_DIR}/dbg.cpp"
	"${TIER0_DIR}/commandline.cpp"
	"${TIER0_DIR}/platform.cpp"
	"${TIER0_DIR}/threadtools.cpp"
	"${TIER0_DIR}/memalloc.cpp"
	"${TIER0_DIR}/mem.cpp"
	"${TIER0_DIR}/vprof.cpp"
	"${TIER0_DIR}/fasttimer.cpp"

	# Private Header files
	"${TIER0_DIR}/memalloc.hpp"
	"${TIER0_DIR}/commandline.hpp"

	# Public Header files
	"${SRC_DIR}/public/tier0/annotations.h"
	"${SRC_DIR}/public/tier0/basetypes.h"
	"${SRC_DIR}/public/tier0/commonmacros.h"
	"${SRC_DIR}/public/tier0/cpumonitoring.h"
	"${SRC_DIR}/public/tier0/dbg.h"
	"${SRC_DIR}/public/tier0/dbgflag.h"
	"${SRC_DIR}/public/tier0/dynfunction.h"
	"${SRC_DIR}/public/tier0/etwprof.h"
	"${SRC_DIR}/public/tier0/EventMasks.h"
	"${SRC_DIR}/public/tier0/EventModes.h"
	"${SRC_DIR}/public/tier0/fasttimer.h"
	"${SRC_DIR}/public/tier0/icommandline.h"
	"${SRC_DIR}/public/tier0/IOCTLCodes.h"
	"${SRC_DIR}/public/tier0/K8PerformanceCounters.h"
	"${SRC_DIR}/public/tier0/l2cache.h"
	"${SRC_DIR}/public/tier0/mem.h"
	"${SRC_DIR}/public/tier0/memalloc.h"
	"${SRC_DIR}/public/tier0/memdbgoff.h"
	"${SRC_DIR}/public/tier0/memdbgon.h"
	"${SRC_DIR}/public/tier0/memoverride.cpp"
	"${SRC_DIR}/public/tier0/minidump.h"
	"${SRC_DIR}/public/tier0/platform.h"
#	$<$<BOOL:${WIN32}>:"${SRC_DIR}/public/tier0/pointeroverride.asm">
	"${SRC_DIR}/public/tier0/progressbar.h"
	"${SRC_DIR}/public/tier0/protected_things.h"
	"${SRC_DIR}/public/tier0/stacktools.h"
	"${SRC_DIR}/public/tier0/systeminformation.h"
	"${SRC_DIR}/public/tier0/testthread.h"
	"${SRC_DIR}/public/tier0/threadtools.h"
	"${SRC_DIR}/public/tier0/tmapi_dummy.h"
	"${SRC_DIR}/public/tier0/tslist.h"
	"${SRC_DIR}/public/tier0/validator.h"
	"${SRC_DIR}/public/tier0/valobject.h"
	"${SRC_DIR}/public/tier0/valve_off.h"
	"${SRC_DIR}/public/tier0/valve_on.h"
	"${SRC_DIR}/public/tier0/vprof.h"
	"${SRC_DIR}/public/tier0/vprof_telemetry.h"
	"${SRC_DIR}/public/tier0/wchartypes.h"
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
set( OUTPUT_FILE_NAME "libtier0" )

add_library( tier0 SHARED )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC}/tier0" )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( tier0
	PRIVATE
		mimalloc
	PUBLIC
		SDL3::SDL3-shared
)
target_compile_definitions( tier0
	PRIVATE
		"TIER0_DLL_EXPORT"
)
