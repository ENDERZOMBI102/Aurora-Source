project( tier0 C CXX )

set( PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source files

	# Private Header files

	# Public Source files

	# Public Header files
)

# Preprocessor defs
set( DEFINES         )
set( WIN_DEFINES     )
set( WIN32_DEFINES   )
set( WIN64_DEFINES   )
set( POSIX_DEFINES   )
set( POSIX32_DEFINES )
set( POSIX64_DEFINES )

# Links dirs to search for link libs in
set( LINK_DIRS         )
set( WIN_LINK_DIRS     )
set( WIN32_LINK_DIRS   )
set( WIN64_LINK_DIRS   )
set( POSIX_LINK_DIRS   )
set( POSIX32_LINK_DIRS )
set( POSIX64_LINK_DIRS )

# Generic libs to link against
set( LINK_LIBS         )
set( WIN32_LINK_LIBS   )
set( WIN64_LINK_LIBS   )
set( POSIX32_LINK_LIBS )
set( POSIX64_LINK_LIBS )

# Generic include dirs
set( INCLUDE_DIRS )
set( WIN32_INCLUDE_DIRS   )
set( WIN64_INCLUDE_DIRS   )
set( POSIX32_INCLUDE_DIRS )
set( POSIX64_INCLUDE_DIRS )

# Set the output file name
set( OUTPUT_FILE_NAME "name" )
# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/${BUILD_GAME}/bin/" )

# Where to put the project in IDEs.
# When left undefined/unspecified, will use the target type to derive it.
set( IDE_FOLDER )

# Target type
add_library( ${PROJECT_NAME} )
add_executable( ${PROJECT_NAME} )

# What this library reimplements
set( REIMPLEMENTS )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME} )
target_include_directories( ${PROJECT_NAME} )
target_compile_definitions( ${PROJECT_NAME} )

add_dependencies( ${PROJECT_NAME} )
