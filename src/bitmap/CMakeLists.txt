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

# Target type
set( KIND "STATIC" )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/bitmap" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
	PRIVATE
		tier0
		tier1
		vstdlib
)
asource_compile_definitions(
	PRIVATE
		"-DIMAGE_LOADER_NO_DXTC"
)
