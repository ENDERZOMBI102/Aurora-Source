project( vbsp C CXX )

set( VBSP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${VBSP_DIR}/boundbox.cpp"
	"${VBSP_DIR}/brushbsp.cpp"
	"${SRC_DIR}/public/collisionutils.cpp"
	"${VBSP_DIR}/csg.cpp"
	"${VBSP_DIR}/cubemap.cpp"
	"${VBSP_DIR}/detail.cpp"
	"${VBSP_DIR}/detailobjects.cpp"
	"${SRC_DIR}/public/disp_common.cpp"
	"${VBSP_DIR}/disp_ivp.cpp"
	"${SRC_DIR}/public/disp_powerinfo.cpp"
	"${VBSP_DIR}/disp_vbsp.cpp"
	"${VBSP_DIR}/faces.cpp"
	"${VBSP_DIR}/glfile.cpp"
	"${VBSP_DIR}/ivp.cpp"
	"${VBSP_DIR}/leakfile.cpp"
	"${SRC_DIR}/public/loadcmdline.cpp"
	"${SRC_DIR}/public/lumpfiles.cpp"
	"${VBSP_DIR}/map.cpp"
	"${VBSP_DIR}/manifest.cpp"
	"${VBSP_DIR}/materialpatch.cpp"
	"${VBSP_DIR}/materialsub.cpp"
	"${SRC_DIR}/utils/common/mstristrip.cpp"
	"${VBSP_DIR}/nodraw.cpp"
	"${VBSP_DIR}/normals.cpp"
	"${VBSP_DIR}/overlay.cpp"
	"${SRC_DIR}/utils/common/physdll.cpp"
	"${VBSP_DIR}/portals.cpp"
	"${VBSP_DIR}/prtfile.cpp"
	"${SRC_DIR}/public/scratchpad3d.cpp"
	"${SRC_DIR}/utils/common/scratchpad_helpers.cpp"
	"${VBSP_DIR}/staticprop.cpp"
	"${VBSP_DIR}/textures.cpp"
	"${VBSP_DIR}/tree.cpp"
	"${SRC_DIR}/utils/common/utilmatlib.cpp"
	"${VBSP_DIR}/vbsp.cpp"
	"${VBSP_DIR}/worldvertextransitionfixup.cpp"
	"${VBSP_DIR}/writebsp.cpp"
	"${SRC_DIR}/public/zip_utils.cpp"

	# Common Files
	"${SRC_DIR}/utils/common/bsplib.cpp"
	"${SRC_DIR}/public/builddisp.cpp"
	"${SRC_DIR}/public/chunkfile.cpp"
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"
	"${SRC_DIR}/utils/common/map_shared.cpp"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/utils/common/polylib.cpp"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/threads.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.h"
	"${SRC_DIR}/utils/common/tools_stub.cpp"

	# Header Files
	"${VBSP_DIR}/boundbox.h"
	"${VBSP_DIR}/csg.h"
	"${VBSP_DIR}/detail.h"
	"${SRC_DIR}/public/disp_powerinfo.h"
	"${VBSP_DIR}/disp_vbsp.h"
	"${SRC_DIR}/public/disp_vertindex.h"
	"${VBSP_DIR}/faces.h"
	"${VBSP_DIR}/map.h"
	"${VBSP_DIR}/manifest.h"
	"${VBSP_DIR}/materialpatch.h"
	"${VBSP_DIR}/materialsub.h"
	"${SRC_DIR}/utils/common/scratchpad_helpers.h"
	"${VBSP_DIR}/vbsp.h"
	"${VBSP_DIR}/worldvertextransitionfixup.h"
	"${VBSP_DIR}/writebsp.h"

	# Common Header Files
	"${SRC_DIR}/utils/common/bsplib.h"
	"${SRC_DIR}/public/builddisp.h"
	"${SRC_DIR}/public/chunkfile.h"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${VBSP_DIR}/disp_ivp.h"
	"${SRC_DIR}/public/filesystem.h"
	"${SRC_DIR}/public/filesystem_helpers.h"
	"${SRC_DIR}/utils/common/filesystem_tools.h"
	"${SRC_DIR}/public/gamebspfile.h"
	"${SRC_DIR}/public/tier1/interface.h"
	"${VBSP_DIR}/ivp.h"
	"${SRC_DIR}/utils/common/map_shared.h"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/polylib.h"
	"${SRC_DIR}/public/tier1/tokenreader.h"
	"${SRC_DIR}/utils/common/utilmatlib.h"
	"${SRC_DIR}/public/zip_uncompressed.h"

	# Public Headers
	"${SRC_DIR}/public/mathlib/amd3dx.h"
	"${SRC_DIR}/public/arraystack.h"
	"${SRC_DIR}/public/tier0/basetypes.h"
	"${SRC_DIR}/public/bspfile.h"
	"${SRC_DIR}/public/bspflags.h"
	"${SRC_DIR}/public/bsptreedata.h"
	"${SRC_DIR}/public/mathlib/bumpvects.h"
	"${SRC_DIR}/public/tier1/byteswap.h"
	"${SRC_DIR}/public/cmodel.h"
	"${SRC_DIR}/public/collisionutils.h"
	"${SRC_DIR}/public/tier0/commonmacros.h"
	"${SRC_DIR}/public/tier0/dbg.h"
	"${SRC_DIR}/public/disp_common.h"
	"${SRC_DIR}/public/iscratchpad3d.h"
	"${SRC_DIR}/public/mathlib/mathlib.h"
	"${SRC_DIR}/utils/common/mstristrip.h"
	"${SRC_DIR}/public/nmatrix.h"
	"${SRC_DIR}/public/ntree.h"
	"${SRC_DIR}/public/nvector.h"
	"${SRC_DIR}/public/phyfile.h"
	"${SRC_DIR}/utils/common/physdll.h"
	"${SRC_DIR}/utils/common/qfiles.h"
	"${SRC_DIR}/public/scratchpad3d.h"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/public/studio.h"
	"${SRC_DIR}/utils/common/threads.h"
	"${SRC_DIR}/public/tier1/utlbuffer.h"
	"${SRC_DIR}/public/tier1/utllinkedlist.h"
	"${SRC_DIR}/public/tier1/utlmemory.h"
	"${SRC_DIR}/public/tier1/utlrbtree.h"
	"${SRC_DIR}/public/tier1/utlsymbol.h"
	"${SRC_DIR}/public/tier1/utlvector.h"
	"${SRC_DIR}/public/vcollide.h"
	"${SRC_DIR}/public/mathlib/vector.h"
	"${SRC_DIR}/public/mathlib/vector2d.h"
	"${SRC_DIR}/public/mathlib/vector4d.h"
	"${SRC_DIR}/public/mathlib/vmatrix.h"
	"${SRC_DIR}/public/vphysics_interface.h"
	"${SRC_DIR}/public/mathlib/vplane.h"
	"${SRC_DIR}/public/wadtypes.h"
	"${SRC_DIR}/public/worldsize.h"
)

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		$<${IS_WINDOWS}:ws2_32>
		$<${IS_WINDOWS}:odbc32>
		$<${IS_WINDOWS}:odbccp32>
		$<${IS_WINDOWS}:winmm>

		tier0
		tier1
		vstdlib
		tier2
		mathlib
		fgdlib
		lzma
		vtf
		bitmap
	INTERFACE
		SDL3::SDL3-shared
)
asource_include_directories(
	PRIVATE
		"${SRC_DIR}/utils/common"
)
asource_compile_definitions(
	PRIVATE
		MACRO_MATHLIB
		PROTECTED_THINGS_DISABLE
)
