project( motionmapper C CXX )

set( MOTIONMAPPER_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${MOTIONMAPPER_DIR}/motionmapper.cpp"
    "${MOTIONMAPPER_DIR}/motionmapper.h"

    # Public Source/Header files
    "${SRC_DIR}/utils/common/cmdlib.cpp"
    "${SRC_DIR}/utils/common/cmdlib.h"
    "${SRC_DIR}/public/filesystem_helpers.cpp"
    "${SRC_DIR}/public/filesystem_helpers.h"
    "${SRC_DIR}/public/filesystem_init.cpp"
    "${SRC_DIR}/public/filesystem_init.h"
    "${SRC_DIR}/utils/common/filesystem_tools.cpp"
    "${SRC_DIR}/utils/common/filesystem_tools.h"
    "${SRC_DIR}/utils/common/scriplib.cpp"
    "${SRC_DIR}/utils/common/scriplib.h"
    "${SRC_DIR}/public/Color.h"
    "${SRC_DIR}/public/studio.h"
)

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier0
        tier1
        vstdlib
        mathlib
        tier2
)
asource_include_directories(
    PRIVATE
        "${SRC_DIR}/utils/common"
)
asource_compile_definitions(
    PRIVATE
        PROTECTED_THINGS_DISABLE
)
