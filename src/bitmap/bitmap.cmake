# bitmap.cmake

set( BITMAP_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( BITMAP_SOURCE_FILES
	# Sources
	"${BITMAP_DIR}/bitmap.cpp"
	"${BITMAP_DIR}/tgaloader.cpp"
	"${BITMAP_DIR}/tgawriter.cpp"
	"${BITMAP_DIR}/tgaspec.hpp"

	# Public units

	# Public headers
	"${SRCDIR}/public/bitmap/bitmap.h"
	"${SRCDIR}/public/bitmap/cubemap.h"
	"${SRCDIR}/public/bitmap/float_bm.h"
	"${SRCDIR}/public/bitmap/imageformat.h"
	"${SRCDIR}/public/bitmap/psd.h"
	"${SRCDIR}/public/bitmap/tgaloader.h"
	"${SRCDIR}/public/bitmap/tgawriter.h"
	"${SRCDIR}/public/filesystem.h"
)

add_library( bitmap2 STATIC ${BITMAP_SOURCE_FILES} )

target_include_directories( bitmap2
	PRIVATE
		"${SRCDIR}/common"
		"${SRCDIR}/public"
)
target_link_libraries( bitmap2
	PRIVATE
		tier0
		vstdlib
)

add_library( bitmap IMPORTED STATIC )

set_target_properties( bitmap
	PROPERTIES
		IMPORTED_LOCATION "${LIBPUBLIC}/bitmap.a"
)
