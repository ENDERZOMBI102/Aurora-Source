# tier2.cmake

set( TIER2_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( TIER2_SOURCE_FILES
	"${TIER2_DIR}/vconfig.cpp"
	"${TIER2_DIR}/tier2.cpp"
	"${TIER2_DIR}/tier2dm.cpp"

	# Header files
#	"${TIER2_DIR}/memalloc.hpp"

	# Public
	"${SRCDIR}/public/tier2/beamsegdraw.h"
	"${SRCDIR}/public/tier2/camerautils.h"
	"${SRCDIR}/public/tier2/fileutils.h"
	"${SRCDIR}/public/tier2/keybindings.h"
	"${SRCDIR}/public/tier2/meshutils.h"
	"${SRCDIR}/public/tier2/p4helpers.h"
	"${SRCDIR}/public/tier2/renderutils.h"
	"${SRCDIR}/public/tier2/riff.h"
	"${SRCDIR}/public/tier2/soundutils.h"
	"${SRCDIR}/public/tier2/tier2.h"
	"${SRCDIR}/public/tier2/tier2dm.h"
	"${SRCDIR}/public/tier2/utlstreambuffer.h"
	"${SRCDIR}/public/tier2/vconfig.h"
)

add_library( tier22 STATIC ${TIER2_SOURCE_FILES} )
target_link_libraries( tier22
	PRIVATE
		asrc::dr::tier0  # may use reimpl or valve's based on -DASRC_USE_REIMPLS
)
set_target_properties( tier1
	PROPERTIES
		POSITION_INDEPENDENT_CODE ON
)


add_library( tier2 IMPORTED STATIC )
set_target_properties( tier2
	PROPERTIES
		IMPORTED_LOCATION "${LIBPUBLIC}/tier2${CMAKE_IMPORT_LIBRARY_SUFFIX}"
)

declare_replacement( tier22 FOR tier2 )
