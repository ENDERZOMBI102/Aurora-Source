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

# Preprocessor defs
set( DEFINES "" )

# Platform-specific preprocessor defines
set( WIN32_DEFINES   )
set( POSIX32_DEFINES )
set( WIN64_DEFINES   )
set( POSIX64_DEFINES )
set( WINDOWS_DEFINES )
set( POSIX_DEFINES   )

add_library( shaderlib STATIC )

# What this library reimplements
set( REIMPLEMENTS "${LIBPUBLIC_DIR}/shaderlib" )

# Include this to handle all the defines
include( ${CMAKESCRIPTS_DIR}/project-base.cmake )
target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
		mathlib
)
