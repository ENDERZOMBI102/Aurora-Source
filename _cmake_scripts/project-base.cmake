#================================================#
#
# Base for all projects
# NOTE: Please add ALL of the base stuff into this
#================================================#
#
# This is the place where all link libs are located, yes
#
#================================================#
# Vars that should be defined in including files
# TARGET: the name of the target
# 
#================================================#
# CMake vars defined by source base:
#	-	LIBCOMMON_DIR
#	-	LIBPUBLIC_DIR
#	-	PUBLIC_INCLUDE
#	-	COMMON_INCLUDE
#================================================#

# === Handle project type & name
if ( "${PROJECT}" STREQUAL "" )
	set( PROJECT "${PROJECT_NAME}" )
endif ()
if ( TARGET ${PROJECT} )
	message( SEND_ERROR "Project `${PROJECT}` pre-defines a target named after itself, this is invalid for a Source target!" )
endif ()

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
#
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
	$<$<BOOL:${ASOURCE_OVERRIDE_MALLOC}>:NO_MALLOC_OVERRIDE>
)

list( APPEND WIN_DEFINES "_WIN32" "WIN32" "WINDOWS" "_ALLOW_MSC_VER_MISMATCH" "PLATFORM_WINDOWS" )
#list( APPEND WIN_DEFINES "_CRT_SECURE_NO_DEPRECATE" "_CRT_NONSTDC_NO_DEPRECATE" "_ALLOW_RUNTIME_LIBRARY_MISMATCH" "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH" "-U_HAS_ITERATOR_DEBUGGING" "_HAS_ITERATOR_DEBUGGING=0" )
list( APPEND WIN32_DEFINES "PLATFORM_WINDOWS_PC32" )
list( APPEND WIN64_DEFINES "PLATFORM_WINDOWS_PC64" )

list( APPEND POSIX_DEFINES "DX_TO_GL_ABSTRACTION" "PLATFORM_POSIX" $<${IS_LINUX}:PLATFORM_LINUX> )
list( APPEND POSIX32_DEFINES )
list( APPEND POSIX64_DEFINES )

# For debug/release builds
if ( CMAKE_BUILD_TYPE EQUAL "Release" )
	list( APPEND DEFINES "NDEBUG" "_NDEBUG" "RELEASEASSERTS" "PLATFORM_RELEASE" )
else()
	list( APPEND DEFINES "DEBUG" "_DEBUG" "PLATFORM_DEBUG" )
endif()

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

set( CMAKE_CXX_VISIBILITY_PRESET hidden )
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
# Now handle the link libraries
# (at least the user defined ones)
#================================================#

# needed for dlls and exes on windows
if ( "${THIS_IS_A_EXE}" OR "${THIS_IS_A_SHARED_LIB}" )
	list( APPEND WIN_LINK_LIBS "shell32.lib" "user32.lib" "advapi32.lib" "gdi32.lib" "comdlg32.lib" "ole32.lib" )
endif ()
list( APPEND POSIX_LINK_LIBS tcmalloc_minimal )  # TODO: Remove

if ( ${IS_WINDOWS} )
	list( APPEND LINK_LIBS ${WIN_LINK_LIBS} )
	# WIN32 libs
	if ( NOT ${IS_64BIT} )
		list( APPEND LINK_LIBS ${WIN32_LINK_LIBS} )
	endif()

	# WIN64 libs
	if ( ${IS_64BIT} )
		list( APPEND LINK_LIBS ${WIN64_LINK_LIBS} )
	endif()
endif()

if( ${IS_POSIX} )
	list( APPEND LINK_LIBS ${POSIX_LINK_LIBS} )

	# POSIX32 libs
	if ( NOT ${IS_64BIT} )
		list( APPEND LINK_LIBS ${POSIX32_LINK_LIBS} )
	endif()

	# POSIX64 libs
	if ( ${IS_64BIT} )
		list( APPEND LINK_LIBS ${POSIX64_LINK_LIBS} )
	endif()
endif()

#================================================#
# Handle the include dirs
#================================================#
list( APPEND INCLUDE_DIRS
	"${SRC_DIR}/common"
	"${SRC_DIR}/public"
	"${SRC_DIR}/public/tier0"
	"${SRC_DIR}/public/tier1"
)
list( APPEND WIN_INCLUDE_DIRS "${DX9SDK}/Include/" )

if ( ${IS_WINDOWS} )
	list( APPEND INCLUDE_DIRS ${WINDOWS_INCLUDE_DIRS} )
	# WIN32 includes
	if ( NOT ${IS_64BIT} )
		list( APPEND INCLUDE_DIRS ${WIN32_INCLUDE_DIRS} )
	endif ()

	# WIN64 includes
	if ( ${IS_64BIT} )
		list( APPEND INCLUDE_DIRS ${WIN64_INCLUDE_DIRS} )
	endif ()
endif ()
if ( ${IS_POSIX} )
	list( APPEND INCLUDE_DIRS ${POSIX_INCLUDE_DIRS} )
	# POSIX32 includes
	if ( NOT ${IS_64BIT} )
		list( APPEND INCLUDE_DIRS ${POSIX32_INCLUDE_DIRS} )
	endif ()

	# POSIX64 includes
	if ( ${IS_64BIT} )
		list( APPEND INCLUDE_DIRS ${POSIX64_INCLUDE_DIRS} )
	endif ()
endif()


#================================================#
# Handle the link directories
#================================================#
list( APPEND POSIX32_LINK_DIRS ${POSIX32_LINK_DIRS} )
list( APPEND POSIX64_LINK_DIRS ${POSIX64_LINK_DIRS} )
list( APPEND WINDOWS_LINK_DIRS "${DX9SDK}/Lib/" )

if ( ${IS_WINDOWS} )
	list( APPEND LINK_DIRS ${WINDOWS_LINK_DIRS} )
	# WIN32 includlinkes
	if ( NOT ${IS_64BIT} )
		list( APPEND LINK_DIRS ${WIN32_LINK_DIRS} )
	endif ()

	# WIN64 link
	if ( ${IS_64BIT} )
		list( APPEND LINK_DIRS ${WIN64_LINK_DIRS} )
	endif ()
endif()

if ( ${IS_POSIX} )
	list( APPEND LINK_DIRS ${POSIX_LINK_DIRS} )
	# POSIX32 link
	if ( NOT ${IS_64BIT} )
		list( APPEND LINK_DIRS ${POSIX32_LINK_DIRS} )
		set( CMAKE_IGNORE_PATH "${CMAKE_IGNORE_PATH} ${POSIX64_LINK_DIRS}" )
	endif ()

	# POSIX64 link
	if ( ${IS_64BIT} )
		list( APPEND LINK_DIRS ${POSIX64_LINK_DIRS} )
		set( CMAKE_IGNORE_PATH "${CMAKE_IGNORE_PATH} ${POSIX32_LINK_DIRS}" )
	endif ()
endif()

#================================================#
# Add the target
#================================================#
if ( NOT ${TRGT_IMPORTED} )
	target_link_directories( ${PROJECT}
		PRIVATE
			${LIBPUBLIC_DIR}
			${LIBCOMMON_DIR}
	)
endif ()

#================================================#
# Handle all the link libraries
#================================================#
#
# For Win32, we need to link against these by default:
#	-	shell32.lib
#	-	user32.lib
#	-	advapi32.lib
#	-	gdi32.lib
#	-	comdlg32.lib
#	-	ole32.lib
#
# For all projects, we need to link against these:
# 	-	vstdlib
# 	-	tier0
# 	-	tier1
#

# finally, declare the target
if ( ${TRGT_IMPORTED} )
	set_target_properties( ${PROJECT} PROPERTIES IMPORTED_LOCATION "${REIMPLEMENTS}${EXTENSION}" )

	target_link_libraries( ${PROJECT} INTERFACE ${LINK_LIBS} )
else ()
	target_sources( ${PROJECT} PRIVATE ${SOURCE_FILES} )

	target_include_directories( ${PROJECT} PUBLIC ${INCLUDE_DIRS} )

	target_link_libraries( ${PROJECT} PUBLIC ${LINK_LIBS} )

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
