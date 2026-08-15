project( tier1 C CXX )

set( TIER1_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${TIER1_DIR}/bitbuf.cpp"
	"${TIER1_DIR}/newbitbuf.cpp"
	"${TIER1_DIR}/byteswap.cpp"
	"${TIER1_DIR}/characterset.cpp"
	"${TIER1_DIR}/checksum_crc.cpp"
	"${TIER1_DIR}/checksum_md5.cpp"
	"${TIER1_DIR}/checksum_sha1.cpp"
	"${TIER1_DIR}/commandbuffer.cpp"
	"${TIER1_DIR}/convar.cpp"
	"${TIER1_DIR}/datamanager.cpp"
	"${TIER1_DIR}/diff.cpp"
	"${TIER1_DIR}/generichash.cpp"
	"${TIER1_DIR}/ilocalize.cpp"
	"${TIER1_DIR}/interface.cpp"
	"${TIER1_DIR}/KeyValues.cpp"
	"${TIER1_DIR}/kvpacker.cpp"
	"${TIER1_DIR}/lzmaDecoder.cpp"
	"$<$<NOT:${IS_SOURCESDK}>:${TIER1_DIR}/lzss.cpp>"
	"${TIER1_DIR}/mempool.cpp"
	"${TIER1_DIR}/memstack.cpp"
	"${TIER1_DIR}/NetAdr.cpp"
	"${TIER1_DIR}/splitstring.cpp"
	"$<${IS_WINDOWS}:${TIER1_DIR}/processor_detect_windows.cpp>"
	"$<${IS_POSIX}:${TIER1_DIR}/processor_detect_linux.cpp>"
	"$<${IS_LINUX}:${TIER1_DIR}/qsort_s.cpp>"
	"${TIER1_DIR}/rangecheckedvar.cpp"
	"${TIER1_DIR}/reliabletimer.cpp"
	"${TIER1_DIR}/stringpool.cpp"
	"${TIER1_DIR}/strtools.cpp"
	"${TIER1_DIR}/strtools_unicode.cpp"
	"${TIER1_DIR}/tier1.cpp"
	"${TIER1_DIR}/tokenreader.cpp"
	"${TIER1_DIR}/sparsematrix.cpp"
	"${TIER1_DIR}/utlbuffer.cpp"
	"${TIER1_DIR}/utlbufferutil.cpp"
	"${TIER1_DIR}/utlstring.cpp"
	"${TIER1_DIR}/utlsymbol.cpp"
	"${TIER1_DIR}/utlbinaryblock.cpp"
	"$<${IS_LINUX}:${TIER1_DIR}/pathmatch.cpp>"
	"${TIER1_DIR}/snappy.cpp"
	"${TIER1_DIR}/snappy-sinksource.cpp"
	"${TIER1_DIR}/snappy-stubs-internal.cpp"
	"${TIER1_DIR}/uniqueid.cpp"

	# Private Header files
	"${TIER1_DIR}/snappy-internal.h"
	"${TIER1_DIR}/snappy-stubs-internal.h"

	# Public Source files
	"${SRC_DIR}/utils/lzma/C/LzmaDec.h"
	"${SRC_DIR}/utils/lzma/C/LzmaDec.c"
	"${SRC_DIR}/utils/lzma/C/7zTypes.h"

	# Public Header files
	"${SRC_DIR}/public/tier1/bitbuf.h"
	"${SRC_DIR}/public/tier1/byteswap.h"
	"${SRC_DIR}/public/tier1/callqueue.h"
	"${SRC_DIR}/public/tier1/characterset.h"
	"${SRC_DIR}/public/tier1/checksum_crc.h"
	"${SRC_DIR}/public/tier1/checksum_md5.h"
	"${SRC_DIR}/public/tier1/uniqueid.h"
	"${SRC_DIR}/public/tier1/checksum_sha1.h"
	"${SRC_DIR}/public/tier1/CommandBuffer.h"
	"${SRC_DIR}/public/tier1/convar.h"
	"${SRC_DIR}/public/tier1/datamanager.h"
	"${SRC_DIR}/public/datamap.h"
	"${SRC_DIR}/public/tier1/delegates.h"
	"${SRC_DIR}/public/tier1/diff.h"
	"${SRC_DIR}/public/tier1/fmtstr.h"
	"${SRC_DIR}/public/tier1/functors.h"
	"${SRC_DIR}/public/tier1/generichash.h"
	"${SRC_DIR}/public/tier1/iconvar.h"
	"${SRC_DIR}/public/tier1/ilocalize.h"
	"${SRC_DIR}/public/tier1/interface.h"
	"${SRC_DIR}/public/tier1/KeyValues.h"
	"${SRC_DIR}/public/tier1/kvpacker.h"
	"${SRC_DIR}/public/tier1/lzmaDecoder.h"
	"${SRC_DIR}/public/tier1/lzss.h"
	"${SRC_DIR}/public/tier1/mempool.h"
	"${SRC_DIR}/public/tier1/memstack.h"
	"${SRC_DIR}/public/tier1/netadr.h"
	"${SRC_DIR}/public/tier1/processor_detect.h"
	"${SRC_DIR}/public/tier1/rangecheckedvar.h"
	"${SRC_DIR}/public/tier1/refcount.h"
	"${SRC_DIR}/public/tier1/smartptr.h"
	"${SRC_DIR}/public/tier1/snappy.h"
	"${SRC_DIR}/public/tier1/snappy-sinksource.h"
	"${SRC_DIR}/public/tier1/stringpool.h"
	"${SRC_DIR}/public/tier1/strtools.h"
	"${SRC_DIR}/public/tier1/tier1.h"
	"${SRC_DIR}/public/tier1/tokenreader.h"
	"${SRC_DIR}/public/tier1/utlbidirectionalset.h"
	"${SRC_DIR}/public/tier1/utlblockmemory.h"
	"${SRC_DIR}/public/tier1/utlbuffer.h"
	"${SRC_DIR}/public/tier1/utlbufferutil.h"
	"${SRC_DIR}/public/tier1/utlcommon.h"
	"${SRC_DIR}/public/tier1/utldict.h"
	"${SRC_DIR}/public/tier1/utlenvelope.h"
	"${SRC_DIR}/public/tier1/utlfixedmemory.h"
	"${SRC_DIR}/public/tier1/utlhandletable.h"
	"${SRC_DIR}/public/tier1/utlhash.h"
	"${SRC_DIR}/public/tier1/utlhashtable.h"
	"${SRC_DIR}/public/tier1/utllinkedlist.h"
	"${SRC_DIR}/public/tier1/utlmap.h"
	"${SRC_DIR}/public/tier1/utlmemory.h"
	"${SRC_DIR}/public/tier1/utlmultilist.h"
	"${SRC_DIR}/public/tier1/utlpriorityqueue.h"
	"${SRC_DIR}/public/tier1/utlqueue.h"
	"${SRC_DIR}/public/tier1/utlrbtree.h"
	"${SRC_DIR}/public/tier1/UtlSortVector.h"
	"${SRC_DIR}/public/tier1/utlstack.h"
	"${SRC_DIR}/public/tier1/utlstring.h"
	"${SRC_DIR}/public/tier1/UtlStringMap.h"
	"${SRC_DIR}/public/tier1/utlsymbol.h"
	"${SRC_DIR}/public/tier1/utlsymbollarge.h"
	"${SRC_DIR}/public/tier1/utlvector.h"
	"${SRC_DIR}/public/tier1/utlbinaryblock.h"
	"$<${IS_WINDOWS}:${SRC_DIR}/common/xbox/xboxstubs.h>"
)

if ( "${IS_LINUX}" AND CMAKE_C_COMPILER_VERSION GREATER 5 )
	list( APPEND SOURCE_FILES "${TIER1_DIR}/math_proxy.cpp" )
endif()

# Preprocessor defs
set( DEFINES "TIER1_STATIC_LIB" )

set_source_files_properties( "$<${IS_WINDOWS}:${TIER1_DIR}/processor_detect.cpp>" PROPERTIES COMPILE_FLAGS /EHsc )

# Target type
set( KIND "STATIC" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
)
