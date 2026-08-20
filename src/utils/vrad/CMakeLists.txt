project( vrad_dll C CXX )

set( VRAD_DLL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files
	"${VRAD_DLL_DIR}/disp_vrad.cpp"
	"${VRAD_DLL_DIR}/disp_vrad.h"
	"${VRAD_DLL_DIR}/iincremental.h"
	"${VRAD_DLL_DIR}/imagepacker.cpp"
	"${VRAD_DLL_DIR}/imagepacker.h"
	"${VRAD_DLL_DIR}/incremental.cpp"
	"${VRAD_DLL_DIR}/incremental.h"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.cpp"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.h"
	"${VRAD_DLL_DIR}/lightmap.cpp"
	"${VRAD_DLL_DIR}/lightmap.h"
	"${VRAD_DLL_DIR}/macro_texture.cpp"
	"${VRAD_DLL_DIR}/macro_texture.h"
	"${VRAD_DLL_DIR}/radial.cpp"
	"${VRAD_DLL_DIR}/radial.h"
	"${VRAD_DLL_DIR}/samplehash.cpp"
	"${VRAD_DLL_DIR}/trace.cpp"
	"${VRAD_DLL_DIR}/vismat.cpp"
	"${VRAD_DLL_DIR}/vismat.h"
	"${VRAD_DLL_DIR}/vrad.cpp"
	"${VRAD_DLL_DIR}/vrad.h"
	"${VRAD_DLL_DIR}/vrad_dispcoll.cpp"
	"${VRAD_DLL_DIR}/vrad_dispcoll.h"
	"${VRAD_DLL_DIR}/vraddetailprops.cpp"
	"${VRAD_DLL_DIR}/vraddetailprops.h"
	"${VRAD_DLL_DIR}/vraddisps.cpp"
	"${VRAD_DLL_DIR}/vraddll.cpp"
	"${VRAD_DLL_DIR}/vraddll.h"
	"${VRAD_DLL_DIR}/vradstaticprops.cpp"

	# Public Source/Header files
	"${SRC_DIR}/public/appframework/IAppSystem.h"
	"${SRC_DIR}/public/basehandle.h"
	"${SRC_DIR}/public/bitvec.h"
	"${SRC_DIR}/public/bspfile.h"
	"${SRC_DIR}/public/bspflags.h"
	"${SRC_DIR}/public/bsptreedata.cpp"
	"${SRC_DIR}/public/bsptreedata.h"
	"${SRC_DIR}/public/builddisp.cpp"
	"${SRC_DIR}/public/builddisp.h"
	"${SRC_DIR}/public/chunkfile.cpp"
	"${SRC_DIR}/public/chunkfile.h"
	"${SRC_DIR}/public/cmodel.h"
	"${SRC_DIR}/public/collisionutils.cpp"
	"${SRC_DIR}/public/collisionutils.h"
	"${SRC_DIR}/public/const.h"
	"${SRC_DIR}/public/coordsize.h"
	"${SRC_DIR}/public/disp_common.cpp"
	"${SRC_DIR}/public/disp_common.h"
	"${SRC_DIR}/public/disp_powerinfo.cpp"
	"${SRC_DIR}/public/disp_powerinfo.h"
	"${SRC_DIR}/public/disp_vertindex.h"
	"${SRC_DIR}/public/dispcoll_common.cpp"
	"${SRC_DIR}/public/dispcoll_common.h"
	"${SRC_DIR}/public/filesystem.h"
	"${SRC_DIR}/public/filesystem_helpers.cpp"
	"${SRC_DIR}/public/filesystem_helpers.h"
	"${SRC_DIR}/public/filesystem_init.cpp"
	"${SRC_DIR}/public/gamebspfile.h"
	"${SRC_DIR}/public/gametrace.h"
	"${SRC_DIR}/public/ihandleentity.h"
	"${SRC_DIR}/public/iscratchpad3d.h"
	"${SRC_DIR}/public/ivraddll.h"
	"${SRC_DIR}/public/loadcmdline.cpp"
	"${SRC_DIR}/public/lumpfiles.cpp"
	"${SRC_DIR}/public/map_utils.h"
	"${SRC_DIR}/public/materialsystem/hardwareverts.h"
	"${SRC_DIR}/public/materialsystem/imaterial.h"
	"${SRC_DIR}/public/materialsystem/imaterialsystem.h"
	"${SRC_DIR}/public/materialsystem/imaterialvar.h"
	"${SRC_DIR}/public/materialsystem/materialsystem_config.h"
	"${SRC_DIR}/public/optimize.h"
	"${SRC_DIR}/public/phyfile.h"
	"${SRC_DIR}/public/scratchpad3d.cpp"
	"${SRC_DIR}/public/scratchpad3d.h"
	"${SRC_DIR}/public/scratchpadutils.cpp"
	"${SRC_DIR}/public/scratchpadutils.h"
	"${SRC_DIR}/public/string_t.h"
	"${SRC_DIR}/public/studio.h"
	"${SRC_DIR}/public/trace.h"
	"${SRC_DIR}/public/vcollide.h"
	"${SRC_DIR}/public/vphysics_interface.h"
	"${SRC_DIR}/public/wadtypes.h"
	"${SRC_DIR}/public/worldsize.h"
	"${SRC_DIR}/public/zip_utils.cpp"
	"${SRC_DIR}/utils/common/bsplib.cpp"
	"${SRC_DIR}/utils/common/bsplib.h"
	"${SRC_DIR}/utils/common/cmdlib.cpp"
	"${SRC_DIR}/utils/common/cmdlib.h"
	"${SRC_DIR}/utils/common/consolewnd.h"
	"${SRC_DIR}/utils/common/filesystem_tools.cpp"
	"${SRC_DIR}/utils/common/map_shared.cpp"
	"${SRC_DIR}/utils/common/map_shared.h"
	"${SRC_DIR}/utils/common/mpi_stats.h"
	"${SRC_DIR}/utils/common/pacifier.cpp"
	"${SRC_DIR}/utils/common/pacifier.h"
	"${SRC_DIR}/utils/common/physdll.cpp"
	"${SRC_DIR}/utils/common/physdll.h"
	"${SRC_DIR}/utils/common/polylib.cpp"
	"${SRC_DIR}/utils/common/polylib.h"
	"${SRC_DIR}/utils/common/scriplib.cpp"
	"${SRC_DIR}/utils/common/scriplib.h"
	"${SRC_DIR}/utils/common/threads.cpp"
	"${SRC_DIR}/utils/common/threads.h"
	"${SRC_DIR}/utils/common/tools_minidump.cpp"
	"${SRC_DIR}/utils/common/tools_minidump.h"
	"${SRC_DIR}/utils/common/tools_stub.cpp"
	"${SRC_DIR}/utils/common/utilmatlib.cpp"
	"${SRC_DIR}/utils/common/utilmatlib.h"
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
