# lzma.cmake

set( LZMA_DIR ${CMAKE_CURRENT_LIST_DIR} )

set( LZMA_SOURCE_FILES
	"${LZMA_DIR}/C/Alloc.c"
	"${LZMA_DIR}/C/LzFind.c"
	"${LZMA_DIR}/C/LzmaDec.c"
	"${LZMA_DIR}/C/LzmaEnc.c"
	"${LZMA_DIR}/C/LzmaLib.c"
	"${LZMA_DIR}/Lzma.cpp"
)


add_library( lzma STATIC ${LZMA_SOURCE_FILES} )

target_compile_definitions( lzma PRIVATE -D_7ZIP_ST )
