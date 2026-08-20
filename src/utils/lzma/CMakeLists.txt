project( lzma C CXX )

set( LZMA_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files
	"${LZMA_DIR}/C/Alloc.c"
	"${LZMA_DIR}/C/LzFind.c"
	"${LZMA_DIR}/C/LzmaDec.c"
	"${LZMA_DIR}/C/LzmaEnc.c"
	"${LZMA_DIR}/C/LzmaLib.c"
	"${LZMA_DIR}/Lzma.cpp"

	# Public Source/Header files
	"${SRC_DIR}/common/lzma/lzma.h"
)

# Target type
set( KIND "STATIC" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

asource_compile_definitions(
	PRIVATE
		_7ZIP_ST
)
