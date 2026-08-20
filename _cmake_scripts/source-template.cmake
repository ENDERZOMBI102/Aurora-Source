project( <invalid> C CXX )

set( PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Private Source/Header files

	# Public Source/Header files
)

# Preprocessor defs
set( DEFINES         )
set( WIN_DEFINES     )
set( WIN32_DEFINES   )
set( WIN64_DEFINES   )
set( POSIX_DEFINES   )
set( POSIX32_DEFINES )
set( POSIX64_DEFINES )

# Set the output file name
set( OUTPUT_FILE_NAME "name" )
# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/${BUILD_GAME}/bin/" )

# Where to put the project in IDEs.
# When left undefined/unspecified, will use the target type to derive it.
set( IDE_FOLDER )

# Target type
set( KIND "SHARED|STATIC|MODULE|EXEC" )
# If should always be imported
set( VENDORED 1 )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/<invalid>" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

asource_link_directories( PUBLIC ... PRIVATE ... )
asource_link_libraries( PUBLIC ... PRIVATE ... )
asource_include_directories( PUBLIC ... PRIVATE ... )
asource_compile_definitions( PUBLIC ... PRIVATE ... )

add_dependencies( ${PROJECT_NAME} )
