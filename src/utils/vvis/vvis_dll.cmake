# vvis_dll.cmake

set( VVIS_DLL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( VVIS_DLL_SOURCE_FILES
	"${SRCDIR}/utils/common/bsplib.cpp"
	"${SRCDIR}/utils/common/cmdlib.cpp"
	"${SRCDIR}/public/collisionutils.cpp"
	"${SRCDIR}/public/filesystem_helpers.cpp"
	"${SRCDIR}/utils/common/filesystem_tools.cpp"
	"${SRCDIR}/public/filesystem_init.cpp"
	"${VVIS_DLL_DIR}/flow.cpp"
	"${SRCDIR}/public/loadcmdline.cpp"
	"${SRCDIR}/public/lumpfiles.cpp"
	"${SRCDIR}/utils/common/pacifier.cpp"
	"${SRCDIR}/public/scratchpad3d.cpp"
	"${SRCDIR}/utils/common/scratchpad_helpers.cpp"
	"${SRCDIR}/utils/common/scriplib.cpp"
	"${SRCDIR}/utils/common/threads.cpp"
	"${SRCDIR}/utils/common/tools_minidump.cpp"
	"${VVIS_DLL_DIR}/vvis.cpp"
	"${VVIS_DLL_DIR}/WaterDist.cpp"
	"${SRCDIR}/public/zip_utils.cpp"
	"${SRCDIR}/utils/common/tools_stub.cpp"

	# Header Files
	"${SRCDIR}/public/mathlib/amd3dx.h"
	"${SRCDIR}/public/tier0/basetypes.h"
	"${SRCDIR}/public/bspfile.h"
	"${SRCDIR}/public/bspflags.h"
	"${SRCDIR}/utils/common/bsplib.h"
	"${SRCDIR}/public/bsptreedata.h"
	"${SRCDIR}/public/mathlib/bumpvects.h"
	"${SRCDIR}/public/tier1/byteswap.h"
	"${SRCDIR}/public/tier1/checksum_crc.h"
	"${SRCDIR}/public/tier1/checksum_md5.h"
	"${SRCDIR}/utils/common/cmdlib.h"
	"${SRCDIR}/public/cmodel.h"
	"${SRCDIR}/public/tier0/commonmacros.h"
	"${SRCDIR}/public/gamebspfile.h"
	"${SRCDIR}/public/mathlib/mathlib.h"
	"${SRCDIR}/utils/common/pacifier.h"
	"${SRCDIR}/utils/common/scriplib.h"
	"${SRCDIR}/public/tier1/strtools.h"
	"${SRCDIR}/utils/common/threads.h"
	"${SRCDIR}/utils/common/tools_minidump.h"
	"${SRCDIR}/public/tier1/utlbuffer.h"
	"${SRCDIR}/public/tier1/utllinkedlist.h"
	"${SRCDIR}/public/tier1/utlmemory.h"
	"${SRCDIR}/public/tier1/utlrbtree.h"
	"${SRCDIR}/public/tier1/utlsymbol.h"
	"${SRCDIR}/public/tier1/utlvector.h"
	"${SRCDIR}/public/vcollide.h"
	"${SRCDIR}/public/mathlib/vector.h"
	"${SRCDIR}/public/mathlib/vector2d.h"
	"${VVIS_DLL_DIR}/vvis.hpp"
	"${SRCDIR}/public/vstdlib/vstdlib.h"
	"${SRCDIR}/public/wadtypes.h"
)

set(
	vvis_dll_exclude_source
		"${SRCDIR}/public/tier0/memoverride.cpp"
)

add_library( vvis_dll MODULE ${VVIS_DLL_SOURCE_FILES} )

set_target_properties( vvis_dll
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${GAMEDIR}/bin"
		PREFIX ""
)

target_include_directories( vvis_dll
	PRIVATE "${SRCDIR}/utils/common"
)

target_compile_definitions( vvis_dll
	PRIVATE PROTECTED_THINGS_DISABLE
)

target_link_libraries( vvis_dll
	PRIVATE
		$<${IS_WINDOWS}:odbc32>
		$<${IS_WINDOWS}:odbccp32>
		$<${IS_WINDOWS}:ws2_32>

		lzma
		${ASRC_DR_tier0}  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
		tier1
		mathlib
		${ASRC_DR_vstdlib}
		tier2
)