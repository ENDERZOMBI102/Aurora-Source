project( phonemeextractor C CXX )

set( PHONOMEEXTRACTOR_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${PHONOMEEXTRACTOR_DIR}/phonemeextractor.cpp"
    "${PHONOMEEXTRACTOR_DIR}/phonemeconverter.cpp"
    "${PHONOMEEXTRACTOR_DIR}/phonemeconverter.h"

    # Public Source/Header files
)
# Target type
set( KIND "EXEC" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        mathlib
)
