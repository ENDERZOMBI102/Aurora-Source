# filesystem_stdio.cmake

set( FILESYSTEM_STDIO_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( FILESYSTEM_STDIO_SOURCE_FILES
	"${FILESYSTEM_STDIO_DIR}/basefilesystem.cpp"
	"${FILESYSTEM_STDIO_DIR}/filesystem.cpp"
	"${FILESYSTEM_STDIO_DIR}/system/isystemclient.cpp"
	"${FILESYSTEM_STDIO_DIR}/system/vpksystemclient.cpp"

	# Header files
	"${FILESYSTEM_STDIO_DIR}/basefilesystem.hpp"
	"${FILESYSTEM_STDIO_DIR}/filesystem.hpp"
	"${FILESYSTEM_STDIO_DIR}/system/isystemclient.hpp"
	"${FILESYSTEM_STDIO_DIR}/system/vpksystemclient.hpp"

	# Public
	"${SRCDIR}/public/filesystem.h"
	"${SRCDIR}/public/filesystem/IQueuedLoader.h"
)

add_library( filesystem_stdio MODULE ${FILESYSTEM_STDIO_SOURCE_FILES} )
target_link_libraries( filesystem_stdio
	PUBLIC
		tier1
		appframework
	PRIVATE
		SDL3-shared
)
set_target_properties( filesystem_stdio
	PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${GAMEDIR}/bin"
		PREFIX ""
)