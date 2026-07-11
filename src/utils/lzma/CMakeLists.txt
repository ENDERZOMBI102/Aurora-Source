project( lzma C CXX )

set( LZMA_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files
	"${LZMA_DIR}/C/Alloc.c"
	"${LZMA_DIR}/C/LzFind.c"
	"${LZMA_DIR}/C/LzmaDec.c"
	"${LZMA_DIR}/C/LzmaEnc.c"
	"${LZMA_DIR}/C/LzmaLib.c"
	"${LZMA_DIR}/Lzma.cpp"

	# Private Header files

	# Public Source files

	# Public Header files
	"${SRC_DIR}/common/lzma/lzma.h"
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

add_library( lzma STATIC )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )
target_compile_definitions( lzma PRIVATE _7ZIP_ST )
