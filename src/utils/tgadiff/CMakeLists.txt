project( tgadiff C CXX )

set( TGADIFF_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${TGADIFF_DIR}/tgadiff.cpp"
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
        bitmap
        mathlib
        tier2
)
