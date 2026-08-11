# game_shader_dx9_sdk.cmake
set( PROJECT game_shader_dx9_sdk )

list( APPEND SOURCE_FILES
	# Private Source files

	# Private Header files

	# Public Source files

	# Public Header files
)

# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/mod_sdk/bin" )

add_library( ${PROJECT} MODULE )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )
