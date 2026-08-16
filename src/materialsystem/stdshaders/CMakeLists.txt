project( shaders C CXX )

set( SHADERS_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
    "${SHADERS_DIR}/BaseVSShader.cpp"

    "${SHADERS_DIR}/example_model_dx9.cpp"
    "${SHADERS_DIR}/example_model_dx9_helper.cpp"

    "${SHADERS_DIR}/Bloom.cpp"
    "${SHADERS_DIR}/screenspace_general.cpp"

    # Header Files
    "${SHADERS_DIR}/BaseVSShader.h"
    "${SHADERS_DIR}/common_fxc.h"
    "${SHADERS_DIR}/common_hlsl_cpp_consts.h"
    "${SHADERS_DIR}/common_ps_fxc.h"
    "${SHADERS_DIR}/common_vertexlitgeneric_dx9.h"
    "${SHADERS_DIR}/common_vs_fxc.h"
    "${SHADERS_DIR}/shader_constant_register_map.h"

    "${SHADERS_DIR}/example_model_dx9_helper.h"

    # Miscellaneous
    "${SHADERS_DIR}/buildsdkshaders.bat"
    "${SHADERS_DIR}/buildshaders.bat"

    "${SHADERS_DIR}/stdshader_dx9_20b.txt"
    "${SHADERS_DIR}/stdshader_dx9_30.txt"
)

include( "game_shader_dx9_${BUILD_GAME}.cmake" )

asource_link_libraries(
    PRIVATE
        "$<${IS_WINDOWS}:version;winmm>"
        tier0
        tier1
        vstdlib
        mathlib
        shaderlib
)
asource_include_directories(
    PRIVATE
        "${SHADERS_DIR}/fxctmp9"
        "${SHADERS_DIR}/vshtmp9"
)
asource_compile_definitions(
    PRIVATE
        STDSHADER_DX9_DLL_EXPORT
        FAST_MATERIALVAR_ACCESS
        GAME_SHADER_DLL
        $<$<NOT:$<BOOL:${USE_TOGL}>>:USE_ACTUAL_DX>
)
