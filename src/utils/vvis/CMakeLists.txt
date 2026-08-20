project( vvis_dll C CXX )

set( VVIS_DLL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files
	"${VVIS_DLL_DIR}/flow.cpp"
	"${VVIS_DLL_DIR}/vvis.cpp"
	"${VVIS_DLL_DIR}/vvis.hpp"
	"${VVIS_DLL_DIR}/WaterDist.cpp"

	# Public Source/Header files
	"${SRC_DIR}/public/bspfile.h"
	"${SRC_DIR}/public/bspflags.h"
	"${SRC_DIR}/public/bsptreedata.h"
	"${SRC_DIR}/public/cmodel.h"
	"${SRC_DIR}/public/collisionutils.cpp"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/gamebspfile.h"
	"${SRC_DIR}/public/loadcmdline.cpp"
	"${SRC_DIR}/public/lumpfiles.cpp"
	"${SRC_DIR}/public/scratchpad3d.cpp"
	"${SRC_DIR}/public/vcollide.h"
	"${SRC_DIR}/public/wadtypes.h"
	"${SRC_DIR}/public/zip_utils.cpp"
	"${SRC_DIR}/utils/common/bsplib.cpp"
	"${SRC_DIR}/utils/common/bsplib.h"
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/scratchpad_helpers.cpp"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/utils/common/threads.cpp"
	"${SRC_DIR}/utils/common/threads.h"
	"${SRC_DIR}/utils/common/tools_minidump.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.h"
	"${SRC_DIR}/utils/common/tools_stub.cpp"
)

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		$<${IS_WINDOWS}:odbc32>
		$<${IS_WINDOWS}:odbccp32>
		$<${IS_WINDOWS}:ws2_32>

		lzma
		tier0
		tier1
		mathlib
		vstdlib
		tier2
)
asource_include_directories(
	PRIVATE
		"${SRC_DIR}/utils/common"
)
asource_compile_definitions(
	PRIVATE
		PROTECTED_THINGS_DISABLE
)
