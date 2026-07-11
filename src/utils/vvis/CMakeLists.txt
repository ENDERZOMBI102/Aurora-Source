project( vvis_dll C CXX )

set( VVIS_DLL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${VVIS_DLL_DIR}/flow.cpp"
	"${VVIS_DLL_DIR}/vvis.cpp"
	"${VVIS_DLL_DIR}/WaterDist.cpp"

	# Private Header files
	"${VVIS_DLL_DIR}/vvis.hpp"

	# Public Source files
	"${SRC_DIR}/utils/common/bsplib.cpp"
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/public/collisionutils.cpp"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/loadcmdline.cpp"
	"${SRC_DIR}/public/lumpfiles.cpp"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/public/scratchpad3d.cpp"
	"${SRC_DIR}/utils/common/scratchpad_helpers.cpp"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/threads.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.cpp"
	"${SRC_DIR}/public/zip_utils.cpp"
	"${SRC_DIR}/utils/common/tools_stub.cpp"

	# Public Header files
	"${SRC_DIR}/public/mathlib/amd3dx.h"
	"${SRC_DIR}/public/tier0/basetypes.h"
	"${SRC_DIR}/public/bspfile.h"
	"${SRC_DIR}/public/bspflags.h"
	"${SRC_DIR}/utils/common/bsplib.h"
	"${SRC_DIR}/public/bsptreedata.h"
	"${SRC_DIR}/public/mathlib/bumpvects.h"
	"${SRC_DIR}/public/tier1/byteswap.h"
	"${SRC_DIR}/public/tier1/checksum_crc.h"
	"${SRC_DIR}/public/tier1/checksum_md5.h"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${SRC_DIR}/public/cmodel.h"
	"${SRC_DIR}/public/tier0/commonmacros.h"
	"${SRC_DIR}/public/gamebspfile.h"
	"${SRC_DIR}/public/mathlib/mathlib.h"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/public/tier1/strtools.h"
	"${SRC_DIR}/utils/common/threads.h"
	"${SRC_DIR}/utils/common/tools_minidump.h"
	"${SRC_DIR}/public/tier1/utlbuffer.h"
	"${SRC_DIR}/public/tier1/utllinkedlist.h"
	"${SRC_DIR}/public/tier1/utlmemory.h"
	"${SRC_DIR}/public/tier1/utlrbtree.h"
	"${SRC_DIR}/public/tier1/utlsymbol.h"
	"${SRC_DIR}/public/tier1/utlvector.h"
	"${SRC_DIR}/public/vcollide.h"
	"${SRC_DIR}/public/mathlib/vector.h"
	"${SRC_DIR}/public/mathlib/vector2d.h"
	"${SRC_DIR}/public/vstdlib/vstdlib.h"
	"${SRC_DIR}/public/wadtypes.h"
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

add_library( vvis_dll MODULE )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_include_directories( vvis_dll
	PRIVATE
		"${SRC_DIR}/utils/common"
)
target_compile_definitions( vvis_dll
	PRIVATE
		PROTECTED_THINGS_DISABLE
)
target_link_libraries( vvis_dll
	PRIVATE
		$<${IS_WINDOWS}:odbc32>
		$<${IS_WINDOWS}:odbccp32>
		$<${IS_WINDOWS}:ws2_32>

		lzma
		tier0  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
		tier1
		mathlib
		vstdlib
		tier2
)
