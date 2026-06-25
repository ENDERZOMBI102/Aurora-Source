project( bitmap CXX )

set( BITMAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Sources
	"${BITMAP_DIR}/bitmap.cpp"
	"${BITMAP_DIR}/imageformat.cpp"
	"${BITMAP_DIR}/tgaloader.cpp"
	"${BITMAP_DIR}/tgawriter.cpp"
	"${BITMAP_DIR}/tgaspec.hpp"

	# Public units

	# Public headers
	"${SRC_DIR}/public/bitmap/bitmap.h"
	"${SRC_DIR}/public/bitmap/cubemap.h"
	"${SRC_DIR}/public/bitmap/float_bm.h"
	"${SRC_DIR}/public/bitmap/imageformat.h"
	"${SRC_DIR}/public/bitmap/psd.h"
	"${SRC_DIR}/public/bitmap/tgaloader.h"
	"${SRC_DIR}/public/bitmap/tgawriter.h"
	"${SRC_DIR}/public/filesystem.h"
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

add_library( bitmap STATIC )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC}/bitmap" )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( bitmap
	PRIVATE
		tier0
		tier1
		vstdlib
)
target_compile_definitions( bitmap
	PRIVATE
		"-DIMAGE_LOADER_NO_DXTC"
)