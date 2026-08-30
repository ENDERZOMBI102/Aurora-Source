project( height2normal C CXX )

set( HEIGHT2NORMAL_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${HEIGHT2NORMAL_DIR}/height2normal.cpp"
)

# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier1
        bitmap
        mathlib
        tier2
)
asource_include_directories(
    PRIVATE
        "${SRC_DIR}/utils/common"
)
asource_compile_definitions(
    PRIVATE
        _HAS_ITERATOR_DEBUGGING=0
        _CONSOLE
        _ALLOW_RUNTIME_LIBRARY_MISMATCH
        _ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH
        _ALLOW_MSC_VER_MISMATCH
)
