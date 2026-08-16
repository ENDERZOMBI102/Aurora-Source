project( shaderlib C CXX )

set( SHADERLIB_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	# Sources
	"${SHADERLIB_DIR}/baseshader.cpp"
	"${SHADERLIB_DIR}/shaderdll.cpp"
	"${SHADERLIB_DIR}/shaderdll.hpp"
	"${SHADERLIB_DIR}/shaderdll_global.h"
	"${SHADERLIB_DIR}/shaderlib_cvar.cpp"
	"${SHADERLIB_DIR}/shaderlib_cvar.h"
	"${SHADERLIB_DIR}/ishadersystem.h"

	# Public units

	# Public headers
	"${SRC_DIR}/public/shaderlib/BaseShader.h"
	"${SRC_DIR}/public/shaderlib/cshader.h"
	"${SRC_DIR}/public/shaderlib/ShaderDLL.h"
)

# Set the output file name
set( OUTPUT_FILE_NAME "shaderlib" )

# Target type
set( KIND "STATIC" )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/shaderlib" )

# Include this to handle all the defines and actually create the target
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )

asource_link_libraries(
	PRIVATE
		tier0
		tier1
		mathlib
)
