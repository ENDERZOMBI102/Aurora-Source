project( filesystem_stdio C CXX )

set( FILESYSTEM_STDIO_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    "${FILESYSTEM_STDIO_DIR}/basefilesystem.cpp"
    "${FILESYSTEM_STDIO_DIR}/filesystem.cpp"
    "${FILESYSTEM_STDIO_DIR}/queuedloader.cpp"
    "${FILESYSTEM_STDIO_DIR}/driver/fsdriver.cpp"
    "${FILESYSTEM_STDIO_DIR}/driver/packfsdriver.cpp"
    "${FILESYSTEM_STDIO_DIR}/driver/plainfsdriver.cpp"
    "${FILESYSTEM_STDIO_DIR}/driver/rootfsdriver.cpp"

    # Header files
    "${FILESYSTEM_STDIO_DIR}/basefilesystem.hpp"
    "${FILESYSTEM_STDIO_DIR}/filesystem.hpp"
    "${FILESYSTEM_STDIO_DIR}/queuedloader.hpp"
    "${FILESYSTEM_STDIO_DIR}/driver/fsdriver.hpp"
    "${FILESYSTEM_STDIO_DIR}/driver/packfsdriver.hpp"
    "${FILESYSTEM_STDIO_DIR}/driver/plainfsdriver.hpp"
    "${FILESYSTEM_STDIO_DIR}/driver/rootfsdriver.hpp"

    # Public
    "${SRC_DIR}/public/filesystem.h"
    "${SRC_DIR}/public/filesystem/IQueuedLoader.h"
    "${SRC_DIR}/public/wildcard/wildcard.cpp"
    "${SRC_DIR}/public/wildcard/wildcard.hpp"
)

add_library( ${PROJECT_NAME} MODULE )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
    PUBLIC
        tier1
        appframework
    PRIVATE
        SDL3::SDL3-shared
        sourcepp::vpkpp
        sourcepp::bsppp
)
