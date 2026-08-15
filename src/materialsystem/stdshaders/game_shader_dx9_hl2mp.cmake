# game_shader_dx9_hl2mp.cmake
set( PROJECT game_shader_dx9_hl2mp )

list( APPEND SOURCE_FILES
	# Private Source files

	# Private Header files

	# Public Source files

	# Public Header files
)

# Set the output file location
set( OUTPUT_FILE_DIR "${GAME_DIR}/mod_sdk/bin" )

# Target type
set( KIND "MODULE" )

# Include this to handle all the defines and actually create the target
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )
