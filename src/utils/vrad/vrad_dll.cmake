# vrad_dll.cmake

set(VRAD_DLL_DIR ${CMAKE_CURRENT_LIST_DIR})
set(VRAD_DLL_SOURCE_FILES
	"${SRCDIR}/public/bsptreedata.cpp"
	"${SRCDIR}/public/disp_common.cpp"
	"${SRCDIR}/public/disp_powerinfo.cpp"
	"${VRAD_DLL_DIR}/disp_vrad.cpp"
	"${VRAD_DLL_DIR}/imagepacker.cpp"
	"${VRAD_DLL_DIR}/incremental.cpp"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.cpp"
	"${VRAD_DLL_DIR}/lightmap.cpp"
	"${SRCDIR}/public/loadcmdline.cpp"
	"${SRCDIR}/public/lumpfiles.cpp"
	"${VRAD_DLL_DIR}/macro_texture.cpp"
	"${SRCDIR}/utils/common/pacifier.cpp"
	"${SRCDIR}/utils/common/physdll.cpp"
	"${VRAD_DLL_DIR}/radial.cpp"
	"${VRAD_DLL_DIR}/samplehash.cpp"
	"${VRAD_DLL_DIR}/trace.cpp"
	"${SRCDIR}/utils/common/utilmatlib.cpp"
	"${VRAD_DLL_DIR}/vismat.cpp"
	"${VRAD_DLL_DIR}/vrad.cpp"
	"${VRAD_DLL_DIR}/vrad_dispcoll.cpp"
	"${VRAD_DLL_DIR}/vraddetailprops.cpp"
	"${VRAD_DLL_DIR}/vraddisps.cpp"
	"${VRAD_DLL_DIR}/vraddll.cpp"
	"${VRAD_DLL_DIR}/vradstaticprops.cpp"
	"${SRCDIR}/public/zip_utils.cpp"

	# Common Files
	"${SRCDIR}/utils/common/bsplib.cpp"
	"${SRCDIR}/public/builddisp.cpp"
	"${SRCDIR}/public/chunkfile.cpp"
	"${SRCDIR}/utils/common/cmdlib.cpp"
	"${SRCDIR}/public/dispcoll_common.cpp"
	"${SRCDIR}/utils/common/map_shared.cpp"
	"${SRCDIR}/utils/common/polylib.cpp"
	"${SRCDIR}/utils/common/scriplib.cpp"
	"${SRCDIR}/utils/common/threads.cpp"
	"${SRCDIR}/utils/common/tools_minidump.cpp"
	"${SRCDIR}/utils/common/tools_minidump.h"
	"${SRCDIR}/utils/common/tools_stub.cpp"

	# Public Files
	"${SRCDIR}/public/collisionutils.cpp"
	"${SRCDIR}/public/filesystem_helpers.cpp"
	"${SRCDIR}/utils/common/filesystem_tools.cpp"
	"${SRCDIR}/public/filesystem_init.cpp"
	"${SRCDIR}/public/scratchpad3d.cpp"
	"${SRCDIR}/public/scratchpadutils.cpp"

	# Header Files
	"${VRAD_DLL_DIR}/disp_vrad.h"
	"${VRAD_DLL_DIR}/iincremental.h"
	"${VRAD_DLL_DIR}/imagepacker.h"
	"${VRAD_DLL_DIR}/incremental.h"
	"${VRAD_DLL_DIR}/leaf_ambient_lighting.h"
	"${VRAD_DLL_DIR}/lightmap.h"
	"${VRAD_DLL_DIR}/macro_texture.h"
	"${SRCDIR}/public/map_utils.h"
	"${VRAD_DLL_DIR}/radial.h"
	"${SRCDIR}/public/bitmap/tgawriter.h"
	"${VRAD_DLL_DIR}/vismat.h"
	"${VRAD_DLL_DIR}/vrad.h"
	"${VRAD_DLL_DIR}/vrad_dispcoll.h"
	"${VRAD_DLL_DIR}/vraddetailprops.h"
	"${VRAD_DLL_DIR}/vraddll.h"

	# Common Header Files
	"${SRCDIR}/utils/common/bsplib.h"
	"${SRCDIR}/utils/common/cmdlib.h"
	"${SRCDIR}/utils/common/consolewnd.h"
	"${SRCDIR}/utils/common/map_shared.h"
	"${SRCDIR}/utils/common/mpi_stats.h"
	"${SRCDIR}/utils/common/pacifier.h"
	"${SRCDIR}/utils/common/polylib.h"
	"${SRCDIR}/utils/common/scriplib.h"
	"${SRCDIR}/utils/common/threads.h"
	"${SRCDIR}/utils/common/utilmatlib.h"

	# Public Header Files
	"${SRCDIR}/public/mathlib/amd3dx.h"
	"${SRCDIR}/public/mathlib/anorms.h"
	"${SRCDIR}/public/basehandle.h"
	"${SRCDIR}/public/tier0/basetypes.h"
	"${SRCDIR}/public/tier1/bitbuf.h"
	"${SRCDIR}/public/bitvec.h"
	"${SRCDIR}/public/bspfile.h"
	"${SRCDIR}/public/bspflags.h"
	"${SRCDIR}/public/bsptreedata.h"
	"${SRCDIR}/public/builddisp.h"
	"${SRCDIR}/public/mathlib/bumpvects.h"
	"${SRCDIR}/public/tier1/byteswap.h"
	"${SRCDIR}/public/tier1/characterset.h"
	"${SRCDIR}/public/tier1/checksum_crc.h"
	"${SRCDIR}/public/tier1/checksum_md5.h"
	"${SRCDIR}/public/chunkfile.h"
	"${SRCDIR}/public/cmodel.h"
	"${SRCDIR}/public/collisionutils.h"
	"${SRCDIR}/public/tier0/commonmacros.h"
	"${SRCDIR}/public/mathlib/compressed_vector.h"
	"${SRCDIR}/public/const.h"
	"${SRCDIR}/public/coordsize.h"
	"${SRCDIR}/public/tier0/dbg.h"
	"${SRCDIR}/public/disp_common.h"
	"${SRCDIR}/public/disp_powerinfo.h"
	"${SRCDIR}/public/disp_vertindex.h"
	"${SRCDIR}/public/dispcoll_common.h"
	"${SRCDIR}/public/tier0/fasttimer.h"
	"${SRCDIR}/public/filesystem.h"
	"${SRCDIR}/public/filesystem_helpers.h"
	"${SRCDIR}/public/gamebspfile.h"
	"${SRCDIR}/public/gametrace.h"
	"${SRCDIR}/public/mathlib/halton.h"
	"${SRCDIR}/public/materialsystem/hardwareverts.h"
	"${SRCDIR}/public/appframework/IAppSystem.h"
	"${SRCDIR}/public/tier0/icommandline.h"
	"${SRCDIR}/public/ihandleentity.h"
	"${SRCDIR}/public/materialsystem/imaterial.h"
	"${SRCDIR}/public/materialsystem/imaterialsystem.h"
	"${SRCDIR}/public/materialsystem/imaterialvar.h"
	"${SRCDIR}/public/tier1/interface.h"
	"${SRCDIR}/public/iscratchpad3d.h"
	"${SRCDIR}/public/ivraddll.h"
	"${SRCDIR}/public/materialsystem/materialsystem_config.h"
	"${SRCDIR}/public/mathlib/mathlib.h"
	"${SRCDIR}/public/tier0/memdbgon.h"
	"${SRCDIR}/public/optimize.h"
	"${SRCDIR}/public/phyfile.h"
	"${SRCDIR}/utils/common/physdll.h"
	"${SRCDIR}/public/tier0/platform.h"
	"${SRCDIR}/public/tier0/protected_things.h"
	"${SRCDIR}/public/scratchpad3d.h"
	"${SRCDIR}/public/scratchpadutils.h"
	"${SRCDIR}/public/string_t.h"
	"${SRCDIR}/public/tier1/strtools.h"
	"${SRCDIR}/public/studio.h"
	"${SRCDIR}/public/tier1/tokenreader.h"
	"${SRCDIR}/public/trace.h"
	"${SRCDIR}/public/tier1/utlbuffer.h"
	"${SRCDIR}/public/tier1/utldict.h"
	"${SRCDIR}/public/tier1/utlhash.h"
	"${SRCDIR}/public/tier1/utllinkedlist.h"
	"${SRCDIR}/public/tier1/utlmemory.h"
	"${SRCDIR}/public/tier1/utlrbtree.h"
	"${SRCDIR}/public/tier1/utlsymbol.h"
	"${SRCDIR}/public/tier1/utlvector.h"
	"${SRCDIR}/public/vcollide.h"
	"${SRCDIR}/public/mathlib/vector.h"
	"${SRCDIR}/public/mathlib/vector2d.h"
	"${SRCDIR}/public/mathlib/vector4d.h"
	"${SRCDIR}/public/mathlib/vmatrix.h"
	"${SRCDIR}/public/vphysics_interface.h"
	"${SRCDIR}/public/mathlib/vplane.h"
	"${SRCDIR}/public/tier0/vprof.h"
	"${SRCDIR}/public/vstdlib/vstdlib.h"
	"${SRCDIR}/public/vtf/vtf.h"
	"${SRCDIR}/public/wadtypes.h"
	"${SRCDIR}/public/worldsize.h"
)

add_library(vrad_dll MODULE ${VRAD_DLL_SOURCE_FILES})

set_target_properties( vrad_dll
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${GAMEDIR}/bin"
		PREFIX ""
)

target_include_directories( vrad_dll
	PRIVATE
		"${SRCDIR}/utils/common"
)

target_compile_definitions( vrad_dll
	PRIVATE
		PROTECTED_THINGS_DISABLE
		VRAD
)

target_link_libraries( vrad_dll
	PRIVATE
		$<${IS_WINDOWS}:ws2_32>

		raytrace
		bitmap
		tier2
		${ASRC_DR_tier0}  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
		${ASRC_DR_vstdlib}
		tier1
		lzma
		mathlib
		vtf
)