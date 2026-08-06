project( serverplugin_empty C CXX )

set( SERVERPLUGIN_EMPTY_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Source Files
    "${SERVERPLUGIN_EMPTY_DIR}/serverplugin_bot.cpp"
    "${SERVERPLUGIN_EMPTY_DIR}/serverplugin_empty.cpp"

    # Header Files

    # Public Header Files
    "${SRC_DIR}/public/tier0/basetypes.h"
    "${SRC_DIR}/public/Color.h"
    "${SRC_DIR}/public/tier0/dbg.h"
    "${SRC_DIR}/public/eiface.h"
    "${SRC_DIR}/public/filesystem.h"
    "${SRC_DIR}/public/tier0/icommandline.h"
    "${SRC_DIR}/public/igameevents.h"
    "${SRC_DIR}/public/tier1/interface.h"
    "${SRC_DIR}/public/game/server/iplayerinfo.h"
    "${SRC_DIR}/public/engine/iserverplugin.h"
    "${SRC_DIR}/public/tier1/KeyValues.h"
    "${SRC_DIR}/public/tier0/mem.h"
    "${SRC_DIR}/public/tier0/memalloc.h"
    "${SRC_DIR}/public/tier0/memdbgon.h"
    "${SRC_DIR}/public/tier1/strtools.h"
    "${SRC_DIR}/public/tier1/utlbuffer.h"
    "${SRC_DIR}/public/tier1/utlmemory.h"
    "${SRC_DIR}/public/tier1/utlvector.h"
    "${SRC_DIR}/public/vstdlib/vstdlib.h"
)

add_library( ${PROJECT_NAME} MODULE )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        tier0
        tier1
        vstdlib
        tier2
        mathlib
)
target_compile_definitions( ${PROJECT_NAME}
    PRIVATE
        serverplugin_emptyONLY
        _MBCS
)

