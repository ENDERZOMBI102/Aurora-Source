project( mathlib C CXX )

set( MATHLIB_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCE_FILES
	"${MATHLIB_DIR}/color_conversion.cpp"
	"${MATHLIB_DIR}/halton.cpp"
	"${MATHLIB_DIR}/lightdesc.cpp"
	"${MATHLIB_DIR}/mathlib_base.cpp"
	"${MATHLIB_DIR}/powsse.cpp"
	"${MATHLIB_DIR}/sparse_convolution_noise.cpp"
	"${MATHLIB_DIR}/sseconst.cpp"
	"${MATHLIB_DIR}/sse.cpp"
	"${MATHLIB_DIR}/ssenoise.cpp"
	"$<$<OR:${IS_WINDOWS},${IS_LINUX}>:${MATHLIB_DIR}/3dnow.cpp>"
	"${MATHLIB_DIR}/anorms.cpp"
	"${MATHLIB_DIR}/bumpvects.cpp"
	"${MATHLIB_DIR}/IceKey.cpp"
	"${MATHLIB_DIR}/imagequant.cpp"
	"${MATHLIB_DIR}/polyhedron.cpp"
	"${MATHLIB_DIR}/quantize.cpp"
	"${MATHLIB_DIR}/randsse.cpp"
	"${MATHLIB_DIR}/spherical.cpp"
	"${MATHLIB_DIR}/simdvectormatrix.cpp"
	"${MATHLIB_DIR}/vector.cpp"
	"${MATHLIB_DIR}/vmatrix.cpp"
	"${MATHLIB_DIR}/almostequal.cpp"

	# Public Header Files
	"$<$<OR:${IS_WINDOWS},${IS_LINUX}>:${SRC_DIR}/public/mathlib/amd3dx.h>"
	"${SRC_DIR}/public/mathlib/anorms.h"
	"${SRC_DIR}/public/mathlib/bumpvects.h"
	"${SRC_DIR}/public/mathlib/compressed_3d_unitvec.h"
	"${SRC_DIR}/public/mathlib/compressed_light_cube.h"
	"${SRC_DIR}/public/mathlib/compressed_vector.h"
	"${SRC_DIR}/public/mathlib/halton.h"
	"${SRC_DIR}/public/mathlib/IceKey.h"
	"${SRC_DIR}/public/mathlib/lightdesc.h"
	"${SRC_DIR}/public/mathlib/math_pfns.h"
	"${SRC_DIR}/public/mathlib/mathlib.h"
	"${SRC_DIR}/public/mathlib/noise.h"
	"${SRC_DIR}/public/mathlib/polyhedron.h"
	"${SRC_DIR}/public/mathlib/quantize.h"
	"${SRC_DIR}/public/mathlib/simdvectormatrix.h"
	"${SRC_DIR}/public/mathlib/spherical_geometry.h"
	"${SRC_DIR}/public/mathlib/ssemath.h"
	"${SRC_DIR}/public/mathlib/ssequaternion.h"
	"${SRC_DIR}/public/mathlib/vector.h"
	"${SRC_DIR}/public/mathlib/vector2d.h"
	"${SRC_DIR}/public/mathlib/vector4d.h"
	"${SRC_DIR}/public/mathlib/vmatrix.h"
	"${SRC_DIR}/public/mathlib/vplane.h"

	# Header Files
	"${MATHLIB_DIR}/noisedata.h"
	"${MATHLIB_DIR}/sse.h"
	"$<$<OR:${IS_WINDOWS},${IS_LINUX}>:${MATHLIB_DIR}/3dnow.h>"
)

add_library( ${PROJECT_NAME} STATIC )

# Include this to handle all the defines
include( "${CMAKESCRIPTS_DIR}/project-base.cmake" )

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
		tier0
		tier1
)
target_include_directories( ${PROJECT_NAME}
	PRIVATE
		"${SRC_DIR}/public/mathlib"
)
target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
		"MATHLIB_LIB"
)
