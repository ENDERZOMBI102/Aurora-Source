project( vice C CXX )

set( VICE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${VICE_DIR}/vice.cpp"

    # Public Source/Header files
    "${SRC_DIR}/utils/common/cmdlib.cpp"
    "${SRC_DIR}/public/filesystem_helpers.cpp"
    "${SRC_DIR}/public/filesystem_init.cpp"
    "${SRC_DIR}/utils/common/filesystem_tools.cpp"
    "${SRC_DIR}/public/mathlib/IceKey.h"
)

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier0
        tier1
        tier2
        mathlib
)
asource_include_directories(
    PRIVATE
        "${SRC_DIR}/utils/common"
)
