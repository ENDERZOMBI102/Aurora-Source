project( fgdlib CXX )

set( FGDLIB_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${FGDLIB_DIR}/gamedata.cpp"
	"${FGDLIB_DIR}/gdclass.cpp"
	"${FGDLIB_DIR}/gdvar.cpp"
	"${FGDLIB_DIR}/inputoutput.cpp"
	"${FGDLIB_DIR}/wckeyvalues.cpp"

	# Header Files
	"${SRC_DIR}/public/fgdlib/fgdlib.h"
	"${SRC_DIR}/public/fgdlib/gamedata.h"
	"${SRC_DIR}/public/fgdlib/gdclass.h"
	"${SRC_DIR}/public/fgdlib/gdvar.h"
	"${SRC_DIR}/public/fgdlib/helperinfo.h"
	"${SRC_DIR}/public/fgdlib/ieditortexture.h"
	"${SRC_DIR}/public/fgdlib/inputoutput.h"
	"${SRC_DIR}/public/fgdlib/wckeyvalues.h"
)

# Target type
set( KIND "STATIC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
)
target_include_directories( ${PROJECT_NAME}
	PRIVATE
		"${SRC_DIR}/utils/common"
)