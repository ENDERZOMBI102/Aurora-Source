project( choreoobjects C CXX )

set( SOURCE_FILES
    # Public Source/Header files
    "${SRC_DIR}/game/shared/choreoactor.cpp"
    "${SRC_DIR}/game/shared/choreoactor.h"
    "${SRC_DIR}/game/shared/choreochannel.cpp"
    "${SRC_DIR}/game/shared/choreochannel.h"
    "${SRC_DIR}/game/shared/choreoevent.cpp"
    "${SRC_DIR}/game/shared/choreoscene.cpp"
    "${SRC_DIR}/game/shared/choreoscene.h"
    "${SRC_DIR}/game/shared/ichoreoeventcallback.h"
    "${SRC_DIR}/game/shared/sceneimage.cpp"
    "${SRC_DIR}/game/shared/sceneimage.h"
)

# Target type
set( KIND "STATIC" )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/choreoobjects" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_libraries(
    PRIVATE
        tier0
        tier1
)
asource_include_directories(
    PUBLIC
        "${SRC_DIR}/utils/common"
)