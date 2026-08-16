#================================================#
# Base for all projects
# NOTE: Please add ALL of the base stuff into this
#================================================#
# This is the place where all link libs are located, yes
#================================================#
# Vars that should be defined in including files
# TARGET: the name of the target
#================================================#


# Ensure we have a free target name
if ( "${PROJECT}" STREQUAL "" )
	set( PROJECT "${PROJECT_NAME}" )
endif ()
if ( TARGET ${PROJECT} )
	message( SEND_ERROR "Project `${PROJECT}` pre-defines a target named after itself, this is invalid for a Source target!" )
endif ()

# Evaluate base target properties
if ( KIND STREQUAL "SHARED" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_SHARED_LIB 1 )
	list( APPEND DEFINES -D_USRDLL -D_SHAREDLIB -D_DLL_ -D_DLL )
	set( FOLDER "Library" )
	set( EXTENSION ${CMAKE_SHARED_LIBRARY_SUFFIX} )
elseif ( KIND STREQUAL "STATIC" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_STATIC_LIB 1 )
	list( APPEND DEFINES -D_LIB -DLIB )
	set( FOLDER "Library" )
	set( EXTENSION ${CMAKE_STATIC_LIBRARY_SUFFIX} )
elseif ( KIND STREQUAL "MODULE" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_MODULE_LIB 1 )
	list( APPEND DEFINES -D_LIB -DLIB )
	set( FOLDER "Module" )
	set( EXTENSION ${CMAKE_SHARED_MODULE_SUFFIX} )
elseif ( KIND STREQUAL "EXEC" )
    set( THIS_IS_A_EXE 1 )
    set( FOLDER "Executable" )
	set( EXTENSION ${CMAKE_EXECUTABLE_SUFFIX} )
endif ()

# Imported project?
if ( "${VENDORED}" STREQUAL "1" )
	set( TRGT_IMPORTED 1 )
elseif ( NOT "${REIMPLEMENTS}" STREQUAL "" )
	if ( ("${ASOURCE_REIMPL}" STREQUAL "1") OR ("${ASOURCE_REIMPL}" MATCHES "${PROJECT},?") )
		set( TRGT_IMPORTED 0 )
	else ()
		set( TRGT_IMPORTED 1 )
	endif ()
else ()
	set( TRGT_IMPORTED 0 )
endif ()

# Create the target
if ( ${TRGT_IMPORTED} )
	if ( "${THIS_IS_A_SHARED_LIB}" )
		add_library( ${PROJECT} SHARED IMPORTED )
	elseif ( "${THIS_IS_A_STATIC_LIB}" )
		add_library( ${PROJECT} STATIC IMPORTED )
	else ()
		message( SEND_ERROR "Project ${PROJECT} declared an invalid imported target type!" )
	endif ()
else ()
	if ( "${THIS_IS_A_SHARED_LIB}" )
		add_library( ${PROJECT} SHARED )
	elseif ( "${THIS_IS_A_STATIC_LIB}" )
		add_library( ${PROJECT} STATIC )
	elseif ( "${THIS_IS_A_MODULE_LIB}" )
		add_library( ${PROJECT} MODULE )
	elseif ( "${THIS_IS_A_EXE}" )
		add_executable( ${PROJECT} )
	else ()
		message( SEND_ERROR "Project ${PROJECT} declared an invalid target type!" )
	endif ()
endif ()

# Virtual folders
if ( "${IDE_FOLDER}" STREQUAL "" )
	set( IDE_FOLDER ${FOLDER} )
endif ()
unset( FOLDER )


#================================================#
# Handle compile options
#================================================#
if ( ${IS_POSIX} AND NOT ${TRGT_IMPORTED} )
	if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		target_compile_options( ${PROJECT} PRIVATE "-g" "-Og" )
	elseif ( CMAKE_BUILD_TYPE STREQUAL "Release" )
		target_compile_options( ${PROJECT} PRIVATE "-g" "-O3" )
	endif ()

	target_compile_options( ${PROJECT}
		PRIVATE
			"-fdiagnostics-color"
			"-ffast-math"
			"-march=i686"
			"-msse3"
			"-Bsymbolic"
	)

	# NO undefined in shared libs
	if ( ${THIS_IS_A_SHARED_LIB} )
		target_link_options( ${PROJECT}
			PRIVATE
				"LINKER:--no-undefined"
		)
	endif ()

	# Warnings
	target_compile_options( ${PROJECT}
		PRIVATE
			# convert a few warnings to errors
			"-Werror=return-type"
#			"-Werror=conversion"
			# silence others
			$<$<COMPILE_LANGUAGE:CXX>:-Wno-invalid-offsetof>
			"-Wno-enum-compare"
#			"-Wno-format-security"
			"-Wno-multichar"
			"-Wno-ignored-attributes"
			$<$<COMPILE_LANGUAGE:CXX>:-Wno-conversion-null>
#			"-Wno-write-strings"
	)
	if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0 )
		target_compile_options( ${PROJECT}
			PRIVATE
				"-Wno-narrowing"
				$<$<COMPILE_LANGUAGE:CXX>:-fabi-compat-version=2>
		)
	endif ()

	if ( ${IS_LINUX} )
		target_compile_options( ${PROJECT} PRIVATE "-U_FORTIFY_SOURCE" )
		target_link_options( ${PROJECT} PRIVATE "LINKER:-rpath,\$ORIGIN" )
		if ( ${IS_64BIT} )
			target_link_options( ${PROJECT} PRIVATE "-l:ld-linux-x86_64.so.2" )
			set( CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/" )
		else ()
			target_link_options( ${PROJECT} PRIVATE "-l:ld-linux.so.2" )
			set( CMAKE_LIBRARY_PATH "/usr/lib/i386-linux-gnu/ /usr/lib32" )
		endif ()
	endif ()
endif()


#================================================#
# First we should handle the preprocessor defs
#================================================#
# For All debug:
#	-	_DEBUG, _CRT_SECURE_NO_DEPRECATE, _CRT_NONSTDC_NO_DEPRECATE
#	-	_HAS_ITERATOR_DEBUGGING, DEBUG, _ALLOW_RUNTIME_LIBRARY_MISMATCH
# For win debug:
# 	-	_ALLOW_MSCC_VER_MISMATCH
list( APPEND DEFINES
	# compile toggles
	$<$<BOOL:${RETAIL}>:_RETAIL>
	$<$<BOOL:${STAGING_ONLY}>:STAGING_ONLY>
	$<${TF_BETA}:TF_BETA>
	$<${RAD_TELEMETRY_DISABLED}:RAD_TELEMETRY_DISABLED>

    # compiler detection
    $<$<CXX_COMPILER_ID:MSVC>:COMPILER_MSVC=1>
    $<$<CXX_COMPILER_ID:Clang>:COMPILER_CLANG=1>
    $<$<CXX_COMPILER_ID:GNU>:COMPILER_GCC=1>

    # platform detection
    $<${IS_64BIT}:PLATFORM_64BITS>
    $<$<BOOL:${RETAIL}>:PLATFORM_RETAIL>

    # misc
    USE_SDL # We use SDL instead of whatever windows provides
    _DLL_EXT=${CMAKE_SHARED_LIBRARY_SUFFIX}
    FRAME_POINTER_OMISSION_DISABLED
	$<$<NOT:$<BOOL:${ASOURCE_OVERRIDE_MALLOC}>>:NO_MALLOC_OVERRIDE>
)
# For debug/release builds
if ( CMAKE_BUILD_TYPE EQUAL "Release" )
	list( APPEND DEFINES "NDEBUG" "_NDEBUG" "RELEASEASSERTS" "PLATFORM_RELEASE" )
else()
	list( APPEND DEFINES "DEBUG" "_DEBUG" "PLATFORM_DEBUG" )
endif()

list( APPEND WIN_DEFINES "_WIN32" "WIN32" "WINDOWS" "_ALLOW_MSC_VER_MISMATCH" "PLATFORM_WINDOWS" )
#list( APPEND WIN_DEFINES "_CRT_SECURE_NO_DEPRECATE" "_CRT_NONSTDC_NO_DEPRECATE" "_ALLOW_RUNTIME_LIBRARY_MISMATCH" "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH" "-U_HAS_ITERATOR_DEBUGGING" "_HAS_ITERATOR_DEBUGGING=0" )
list( APPEND WIN32_DEFINES "PLATFORM_WINDOWS_PC32" )
list( APPEND WIN64_DEFINES "PLATFORM_WINDOWS_PC64" )

list( APPEND POSIX_DEFINES "DX_TO_GL_ABSTRACTION" "PLATFORM_POSIX" $<${IS_LINUX}:PLATFORM_LINUX> )
list( APPEND POSIX32_DEFINES )
list( APPEND POSIX64_DEFINES )

if ( ${IS_WINDOWS} )
	list( APPEND DEFINES ${WIN_DEFINES} )
	# WIN32 defines
	if ( NOT ${IS_64BIT} )
		list( APPEND DEFINES ${WIN32_DEFINES} )
	endif ()

	# WIN64 defines
	if ( ${IS_64BIT} )
		list( APPEND DEFINES ${WIN32_DEFINES} )
	endif ()
endif()
if ( ${IS_POSIX} )
	list( APPEND DEFINES ${POSIX_DEFINES} )
	# POSIX32 defines
	if ( NOT ${IS_64BIT} )
		list( APPEND DEFINES ${POSIX32_DEFINES} )
	endif ()

	# POSIX64 defines
	if ( ${IS_64BIT} )
		list( APPEND DEFINES ${POSIX64_DEFINES} )
	endif ()
endif()


#================================================#
# Finish setting up the target
#================================================#
# For Win32, we need to link against these by default:
#	-	shell32.lib
#	-	user32.lib
#	-	advapi32.lib
#	-	gdi32.lib
#	-	comdlg32.lib
#	-	ole32.lib
# For all projects, we need to link against these:
# 	-	vstdlib
# 	-	tier0
# 	-	tier1
if ( ${TRGT_IMPORTED} )
	set_target_properties( ${PROJECT} PROPERTIES IMPORTED_LOCATION "${REIMPLEMENTS}${EXTENSION}" )

	target_link_libraries( ${PROJECT} INTERFACE ${LINK_LIBS} )

	target_compile_definitions( ${PROJECT} INTERFACE ${DEFINES} )
else ()
	target_sources( ${PROJECT} PRIVATE ${SOURCE_FILES} )

	target_include_directories( ${PROJECT} PRIVATE
		"${SRC_DIR}/common"
		"${SRC_DIR}/public"
		"${SRC_DIR}/public/tier0"
		"${SRC_DIR}/public/tier1"
	)

	target_link_directories( ${PROJECT}
		PRIVATE
			${LIBPUBLIC_DIR}
			${LIBCOMMON_DIR}
	)

	target_link_libraries( ${PROJECT} PUBLIC ${LINK_LIBS} )
	if ( ${IS_WINDOWS} )
		target_link_libraries( ${PROJECT} PRIVATE "shell32.lib" "user32.lib" "advapi32.lib" "gdi32.lib" "comdlg32.lib" "ole32.lib" )
	endif()
	if( ${IS_POSIX} )
		#	target_link_libraries( ${PROJECT} PRIVATE "tcmalloc_minimal" )
	endif()

	target_compile_definitions( ${PROJECT} PUBLIC ${DEFINES} )

	if ( DEFINED OUTPUT_FILE_DIR )
		set_target_properties( ${PROJECT}
			PROPERTIES
				RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_FILE_DIR}"
				LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_FILE_DIR}"
		)
	endif ()

	if ( DEFINED OUTPUT_FILE_NAME )
		set_target_properties( ${PROJECT} PROPERTIES OUTPUT_NAME "${OUTPUT_FILE_NAME}" )
	endif ()

	if ( ${PRECOMPILED_HEADERS} )
		target_precompile_headers( ${PROJECT} PUBLIC ${PRECOMPILED_HEADERS} )
	endif()

	if ( "${THIS_IS_A_STATIC_LIB}" )
		set_target_properties( ${PROJECT} PROPERTIES POSITION_INDEPENDENT_CODE ON )
	endif ()
endif ()

set_target_properties( ${PROJECT}
	PROPERTIES
		FOLDER "${IDE_FOLDER}"
		LINKER_LANGUAGE CXX
)

block()
	if ( ${TRGT_IMPORTED} )
		set( PROJECT "${PROJECT}*" )
	endif ()
	set_property( DIRECTORY ${ROOT_DIR} APPEND PROPERTY ASOURCE_${IDE_FOLDER} "${PROJECT}" )
endblock()

if ( "${THIS_IS_A_MODULE_LIB}" )
	set_target_properties( ${PROJECT} PROPERTIES PREFIX "" )
endif ()


#================================================#
# Declare dependency functions
#================================================#
function( asource_link_directories )
	cmake_parse_arguments( TSLL "" "" "PRIVATE;PUBLIC" ${ARGN} )

	if ( ${TRGT_IMPORTED} )
		target_link_directories( ${PROJECT} INTERFACE ${TSLL_PUBLIC} )
	else ()
		target_link_directories( ${PROJECT} PUBLIC ${TSLL_PUBLIC} PRIVATE ${TSLL_PRIVATE} )
	endif ()
endfunction()

function( asource_link_libraries )
	cmake_parse_arguments( TSLL "" "" "PRIVATE;PUBLIC" ${ARGN} )

	if ( ${TRGT_IMPORTED} )
		target_link_libraries( ${PROJECT} INTERFACE ${TSLL_PUBLIC} )
	else ()
		target_link_libraries( ${PROJECT} PUBLIC ${TSLL_PUBLIC} PRIVATE ${TSLL_PRIVATE} )
	endif ()
endfunction()

function( asource_include_directories )
	cmake_parse_arguments( TSLL "" "" "PRIVATE;PUBLIC" ${ARGN} )

	if ( ${TRGT_IMPORTED} )
		target_include_directories( ${PROJECT} INTERFACE ${TSLL_PUBLIC} )
	else ()
		target_include_directories( ${PROJECT} PUBLIC ${TSLL_PUBLIC} PRIVATE ${TSLL_PRIVATE} )
	endif ()
endfunction()

function( asource_compile_definitions )
	cmake_parse_arguments( TSLL "" "" "PRIVATE;PUBLIC" ${ARGN} )

	if ( ${TRGT_IMPORTED} )
		target_compile_definitions( ${PROJECT} INTERFACE ${TSLL_PUBLIC} )
	else ()
		target_compile_definitions( ${PROJECT} PUBLIC ${TSLL_PUBLIC} PRIVATE ${TSLL_PRIVATE} )
	endif ()
endfunction()
