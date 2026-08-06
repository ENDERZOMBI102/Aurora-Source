project( togl C CXX )

set( TOGL_DIR "${CMAKE_CURRENT_LIST_DIR}/linuxwin" )
set( SOURCE_FILES
    # Source Files
    "${TOGL_DIR}/dx9asmtogl2.cpp"
    "${TOGL_DIR}/dxabstract.cpp"
    "${TOGL_DIR}/glentrypoints.cpp"
    "${TOGL_DIR}/glmgr.cpp"
    "${TOGL_DIR}/glmgrbasics.cpp"
    $<${IS_OSX}:"${TOGL_DIR}/glmgrcocoa.mm">
    $<${IS_OSX}:"${TOGL_DIR}/intelglmallocworkaround.cpp">
    $<${IS_OSX}:"${TOGL_DIR}/mach_override.c">
    "${TOGL_DIR}/cglmtex.cpp"
    "${TOGL_DIR}/cglmfbo.cpp"
    "${TOGL_DIR}/cglmprogram.cpp"
    "${TOGL_DIR}/cglmbuffer.cpp"
    "${TOGL_DIR}/cglmquery.cpp"

    # Header Files
    "${TOGL_DIR}/dx9asmtogl2.h"
    "${TOGL_DIR}/glmgr_flush.inl"
    $<${IS_OSX}:"${TOGL_DIR}/intelglmallocworkaround.h">
    $<${IS_OSX}:"${TOGL_DIR}/mach_override.h">

    # Public Header Files
    "${SRC_DIR}/public/togl/rendermechanism.h"
    "${SRC_DIR}/public/togl/linuxwin/dxabstract.h"
    "${SRC_DIR}/public/togl/linuxwin/dxabstract_types.h"
    "${SRC_DIR}/public/togl/linuxwin/glbase.h"
    "${SRC_DIR}/public/togl/linuxwin/glentrypoints.h"
    "${SRC_DIR}/public/togl/linuxwin/glmgr.h"
    "${SRC_DIR}/public/togl/linuxwin/glmdebug.h"
    "${SRC_DIR}/public/togl/linuxwin/glmgrbasics.h"
    "${SRC_DIR}/public/togl/linuxwin/glmgrext.h"
    "${SRC_DIR}/public/togl/linuxwin/glmdisplay.h"
    "${SRC_DIR}/public/togl/linuxwin/glmdisplaydb.h"
    "${SRC_DIR}/public/togl/linuxwin/glfuncs.h"
    "${SRC_DIR}/public/togl/linuxwin/cglmtex.h"
    "${SRC_DIR}/public/togl/linuxwin/cglmfbo.h"
    "${SRC_DIR}/public/togl/linuxwin/cglmprogram.h"
    "${SRC_DIR}/public/togl/linuxwin/cglmbuffer.h"
    "${SRC_DIR}/public/togl/linuxwin/cglmquery.h"
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
        SDL3::SDL3-shared
)
target_compile_definitions( ${PROJECT_NAME}
    PRIVATE
        serverplugin_emptyONLY
        TOGL_DLL_EXPORT
#        PROTECTED_THINGS_ENABLE
#        strncpy=use_Q_strncpy_instead
#        _snprintf=use_Q_snprintf_instead
)

