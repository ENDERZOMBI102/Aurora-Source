project( inputsystem C CXX )

set( INPUTSYSTEM_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    # Private Source/Header files
    "${INPUTSYSTEM_DIR}/inputsystem.cpp"
    "${INPUTSYSTEM_DIR}/inputsystem.hpp"
    "${INPUTSYSTEM_DIR}/inputmaps.cpp"
    "${INPUTSYSTEM_DIR}/inputmaps.hpp"

    # Public Source files

    # Public Header files
    "${SRC_DIR}/public/inputsystem/analogcode.h"
    "${SRC_DIR}/public/inputsystem/buttoncode.h"
    "${SRC_DIR}/public/inputsystem/iinputsystem.h"
    "${SRC_DIR}/public/inputsystem/inputenums.h"
)

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier0
        tier1
        vstdlib
        tier2
        appframework
        SDL3::SDL3-shared
)
