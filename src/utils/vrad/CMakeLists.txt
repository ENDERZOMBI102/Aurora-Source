project( vrad_dll C CXX )

set( VRAD_DLL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${SRC_DIR}/public/bsptreedata.cpp"
	"${SRC_DIR}/public/disp_common.cpp"
	"${SRC_DIR}/public/disp_powerinfo.cpp"
	"${VRAD_DLL_DIR}/disp_vrad.cpp"
	"${VRAD_DLL_DIR}/imagepacker.cpp"
	"${VRAD_DLL_DIR}/incremental.cpp"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.cpp"
	"${VRAD_DLL_DIR}/lightmap.cpp"
	"${SRC_DIR}/public/loadcmdline.cpp"
	"${SRC_DIR}/public/lumpfiles.cpp"
	"${VRAD_DLL_DIR}/macro_texture.cpp"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/utils/common/physdll.cpp"
	"${VRAD_DLL_DIR}/radial.cpp"
	"${VRAD_DLL_DIR}/samplehash.cpp"
	"${VRAD_DLL_DIR}/trace.cpp"
	"${SRC_DIR}/utils/common/utilmatlib.cpp"
	"${VRAD_DLL_DIR}/vismat.cpp"
	"${VRAD_DLL_DIR}/vrad.cpp"
	"${VRAD_DLL_DIR}/vrad_dispcoll.cpp"
	"${VRAD_DLL_DIR}/vraddetailprops.cpp"
	"${VRAD_DLL_DIR}/vraddisps.cpp"
	"${VRAD_DLL_DIR}/vraddll.cpp"
	"${VRAD_DLL_DIR}/vradstaticprops.cpp"
	"${SRC_DIR}/public/zip_utils.cpp"

	# Common Files
	"${SRC_DIR}/utils/common/bsplib.cpp"
	"${SRC_DIR}/public/builddisp.cpp"
	"${SRC_DIR}/public/chunkfile.cpp"
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/public/dispcoll_common.cpp"
	"${SRC_DIR}/utils/common/map_shared.cpp"
	"${SRC_DIR}/utils/common/polylib.cpp"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/threads.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.h"
	"${SRC_DIR}/utils/common/tools_stub.cpp"

	# Public Files
	"${SRC_DIR}/public/collisionutils.cpp"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/scratchpad3d.cpp"
	"${SRC_DIR}/public/scratchpadutils.cpp"

	# Header Files
	"${VRAD_DLL_DIR}/disp_vrad.h"
	"${VRAD_DLL_DIR}/iincremental.h"
	"${VRAD_DLL_DIR}/imagepacker.h"
	"${VRAD_DLL_DIR}/incremental.h"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.h"
	"${VRAD_DLL_DIR}/lightmap.h"
	"${VRAD_DLL_DIR}/macro_texture.h"
	"${SRC_DIR}/public/map_utils.h"
	"${VRAD_DLL_DIR}/radial.h"
	"${SRC_DIR}/public/bitmap/tgawriter.h"
	"${VRAD_DLL_DIR}/vismat.h"
	"${VRAD_DLL_DIR}/vrad.h"
	"${VRAD_DLL_DIR}/vrad_dispcoll.h"
	"${VRAD_DLL_DIR}/vraddetailprops.h"
	"${VRAD_DLL_DIR}/vraddll.h"

	# Common Header Files
	"${SRC_DIR}/utils/common/bsplib.h"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${SRC_DIR}/utils/common/consolewnd.h"
	"${SRC_DIR}/utils/common/map_shared.h"
	"${SRC_DIR}/utils/common/mpi_stats.h"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/polylib.h"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/utils/common/threads.h"
	"${SRC_DIR}/utils/common/utilmatlib.h"

	# Public Header Files
	"${SRC_DIR}/public/mathlib/amd3dx.h"
	"${SRC_DIR}/public/mathlib/anorms.h"
	"${SRC_DIR}/public/basehandle.h"
	"${SRC_DIR}/public/tier0/basetypes.h"
	"${SRC_DIR}/public/tier1/bitbuf.h"
	"${SRC_DIR}/public/bitvec.h"
	"${SRC_DIR}/public/bspfile.h"
	"${SRC_DIR}/public/bspflags.h"
	"${SRC_DIR}/public/bsptreedata.h"
	"${SRC_DIR}/public/builddisp.h"
	"${SRC_DIR}/public/mathlib/bumpvects.h"
	"${SRC_DIR}/public/tier1/byteswap.h"
	"${SRC_DIR}/public/tier1/characterset.h"
	"${SRC_DIR}/public/tier1/checksum_crc.h"
	"${SRC_DIR}/public/tier1/checksum_md5.h"
	"${SRC_DIR}/public/chunkfile.h"
	"${SRC_DIR}/public/cmodel.h"
	"${SRC_DIR}/public/collisionutils.h"
	"${SRC_DIR}/public/tier0/commonmacros.h"
	"${SRC_DIR}/public/mathlib/compressed_vector.h"
	"${SRC_DIR}/public/const.h"
	"${SRC_DIR}/public/coordsize.h"
	"${SRC_DIR}/public/tier0/dbg.h"
	"${SRC_DIR}/public/disp_common.h"
	"${SRC_DIR}/public/disp_powerinfo.h"
	"${SRC_DIR}/public/disp_vertindex.h"
	"${SRC_DIR}/public/dispcoll_common.h"
	"${SRC_DIR}/public/tier0/fasttimer.h"
	"${SRC_DIR}/public/filesystem.h"
	"${SRC_DIR}/public/filesystem_helpers.h"
	"${SRC_DIR}/public/gamebspfile.h"
	"${SRC_DIR}/public/gametrace.h"
	"${SRC_DIR}/public/mathlib/halton.h"
	"${SRC_DIR}/public/materialsystem/hardwareverts.h"
	"${SRC_DIR}/public/appframework/IAppSystem.h"
	"${SRC_DIR}/public/tier0/icommandline.h"
	"${SRC_DIR}/public/ihandleentity.h"
	"${SRC_DIR}/public/materialsystem/imaterial.h"
	"${SRC_DIR}/public/materialsystem/imaterialsystem.h"
	"${SRC_DIR}/public/materialsystem/imaterialvar.h"
	"${SRC_DIR}/public/tier1/interface.h"
	"${SRC_DIR}/public/iscratchpad3d.h"
	"${SRC_DIR}/public/ivraddll.h"
	"${SRC_DIR}/public/materialsystem/materialsystem_config.h"
	"${SRC_DIR}/public/mathlib/mathlib.h"
	"${SRC_DIR}/public/tier0/memdbgon.h"
	"${SRC_DIR}/public/optimize.h"
	"${SRC_DIR}/public/phyfile.h"
	"${SRC_DIR}/utils/common/physdll.h"
	"${SRC_DIR}/public/tier0/platform.h"
	"${SRC_DIR}/public/tier0/protected_things.h"
	"${SRC_DIR}/public/scratchpad3d.h"
	"${SRC_DIR}/public/scratchpadutils.h"
	"${SRC_DIR}/public/string_t.h"
	"${SRC_DIR}/public/tier1/strtools.h"
	"${SRC_DIR}/public/studio.h"
	"${SRC_DIR}/public/tier1/tokenreader.h"
	"${SRC_DIR}/public/trace.h"
	"${SRC_DIR}/public/tier1/utlbuffer.h"
	"${SRC_DIR}/public/tier1/utldict.h"
	"${SRC_DIR}/public/tier1/utlhash.h"
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
	"${SRC_DIR}/public/tier0/vprof.h"
	"${SRC_DIR}/public/vstdlib/vstdlib.h"
	"${SRC_DIR}/public/vtf/vtf.h"
	"${SRC_DIR}/public/wadtypes.h"
	"${SRC_DIR}/public/worldsize.h"
)

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		$<${IS_WINDOWS}:ws2_32>

		tier0
		tier1
		vstdlib
		mathlib
		raytrace
		bitmap
		vtf
		tier2
		lzma
)
asource_include_directories(
	PRIVATE
		"${SRC_DIR}/utils/common"
)
asource_compile_definitions(
	PRIVATE
		PROTECTED_THINGS_DISABLE
		VRAD
)
