#================================================#
#
# Base for all projects
# Separated from library-base, etc. because it's easier
# NOTE: Please add ALL of the base stuff into this
# NOTE AGAIN: I might merge this with source-base.cmake
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
if ( NOT TARGET ${PROJECT_NAME} )
	message( FATAL_ERROR "Project `${PROJECT_NAME}` does not define a target named after itself, this is invalid for a Source target!" )
endif ()

get_target_property( TRGT_TYPE ${PROJECT_NAME} TYPE )
if ( TRGT_TYPE STREQUAL "SHARED_LIBRARY" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_SHARED_LIB 1 )
	list( APPEND DEFINES -D_USRDLL -D_SHAREDLIB -D_DLL_ -D_DLL )
	set( FOLDER "Library" )
elseif ( TRGT_TYPE STREQUAL "STATIC_LIBRARY" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_STATIC_LIB 1 )
	list( APPEND DEFINES -D_LIB -DLIB )
	set( FOLDER "Library" )
elseif ( TRGT_TYPE STREQUAL "MODULE_LIBRARY" )
	set( THIS_IS_A_LIBRARY 1 )
	set( THIS_IS_A_MODULE_LIB 1 )
	list( APPEND DEFINES -D_LIB -DLIB )
	set( FOLDER "Module" )
elseif ( TRGT_TYPE STREQUAL "EXECUTABLE" )
    set( THIS_IS_A_EXE 1 )
    set( FOLDER "Executable" )
endif ()
if ( "${IDE_FOLDER}" STREQUAL "" )
	set( IDE_FOLDER ${FOLDER} )
endif ()
unset( FOLDER )


#================================================#
# Handle compile options
#================================================#
if ( ${IS_POSIX} )
	if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
		target_compile_options( ${PROJECT_NAME} PRIVATE "-g" "-Og" )
	elseif ( CMAKE_BUILD_TYPE STREQUAL "Release" )
		target_compile_options( ${PROJECT_NAME} PRIVATE "-g" "-O3" )
	endif ()

	target_compile_options( ${PROJECT_NAME}
		PRIVATE
			"-fdiagnostics-color"
			"-ffast-math"
			"-march=i686"
			"-msse3"
			"-Bsymbolic"
	)

	# NO undefined in shared libs
	set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}" )

	# Warnings
	target_compile_options( ${PROJECT_NAME}
		PRIVATE
#			"-fpermissive"
			# convert a few warnings to errors
			"-Werror=return-type"
#			"-Werror=conversion"
			# silence others
			"-Wno-invalid-offsetof"
			"-Wno-enum-compare"
#			"-Wno-format-security"
			"-Wno-multichar"
			"-Wno-ignored-attributes"
			"-Wno-conversion-null"
#			"-Wno-write-strings"
	)
	if ( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0 )
		target_compile_options( ${PROJECT_NAME}
			PRIVATE
				"-Wno-narrowing"
				$<$<COMPILE_LANGUAGE:CXX>:-fabi-compat-version=2>
		)
	endif ()

	if ( ${IS_LINUX} )
		target_compile_options( ${PROJECT_NAME} PRIVATE "-U_FORTIFY_SOURCE" )
		add_link_options( "-l:-rpath,\$ORIGIN" )
		if ( ${IS_64BIT} )
			add_link_options( "-l:ld-linux-x86_64.so.2" )
			set( CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/" )
		else ()
			add_link_options( "-l:ld-linux.so.2" )
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
# 	-	_ALLOW_MSCC_VER_MISMATCHs
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
    NO_MALLOC_OVERRIDE
)
list( APPEND WINDOWS_DEFINES
    "_WIN32"
    "WIN32"
    "WINDOWS"
    "_ALLOW_MSC_VER_MISMATCH"
    "PLATFORM_WINDOWS"
)
list( APPEND WIN32_DEFINES
    "PLATFORM_WINDOWS_PC32"
)
list( APPEND WIN64_DEFINES
    "PLATFORM_WINDOWS_PC64"
)

#list( APPEND DEFINES         "_CRT_SECURE_NO_DEPRECATE" "_CRT_NONSTDC_NO_DEPRECATE" "_ALLOW_RUNTIME_LIBRARY_MISMATCH" "_ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH" "-U_HAS_ITERATOR_DEBUGGING" "_HAS_ITERATOR_DEBUGGING=0" )
list( APPEND POSIX_DEFINES
    "DX_TO_GL_ABSTRACTION"
    "PLATFORM_POSIX"
    $<${IS_LINUX}:PLATFORM_LINUX>
)
list( APPEND POSIX32_DEFINES )
list( APPEND POSIX64_DEFINES )

# For debug/release builds
if ( CMAKE_BUILD_TYPE EQUAL "Release" )
	list( APPEND DEFINES "NDEBUG" "_NDEBUG" "RELEASEASSERTS" "PLATFORM_RELEASE" )
else()
	list( APPEND DEFINES "DEBUG" "_DEBUG" "PLATFORM_DEBUG" )
endif()

if ( ${IS_WINDOWS} )
	list( APPEND DEFINES ${WINDOWS_DEFINES} )
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
# Now handle the sources
#================================================#
if ( ${IS_WINDOWS} )
	list( APPEND SOURCE_FILES ${WINDOWS_SOURCE_FILES} )
endif()

if ( ${IS_POSIX} )
	list( APPEND SOURCE_FILES ${POSIX_SOURCE_FILES} )
endif()

#================================================#
# Now handle the link libraries
# (at least the user defined ones)
#================================================#

# needed for dlls and exes on windows
if ( THIS_IS_A_EXE EQUAL 1 OR THIS_IS_A_SHARED_LIB EQUAL 1 )
	list( APPEND WINDOWS_LINK_LIBS "shell32.lib" "user32.lib" "advapi32.lib" "gdi32.lib" "comdlg32.lib" "ole32.lib" )
endif ()
list( APPEND POSIX_LINK_LIBS tcmalloc_minimal )

if ( ${IS_WINDOWS} )
	# Generic windows libs
	list( APPEND LINK_LIBS ${WINDOWS_LINK_LIBS} )

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
	# Generic posix libs
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
list( APPEND POSIX32_INCLUDE_DIRS ${POSIX32_INCLUDE_DIRS} )
# For windows only
list( APPEND WINDOWS_INCLUDE_DIRS "${DX9SDK}/Include/" )

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
# For windows only
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
# Handle special cases
#================================================#
set( ACTUAL_LIBS )

# For needed packages
foreach ( package IN LISTS PACKAGES )
	find_package( ${package} REQUIRED )
	if ( NOT ${package}_FOUND )
		message( FATAL_ERROR "Unable to find package ${package}!" )
	else()
		list( APPEND ACTUAL_LIBS ${${package}_LIBRARIES} )
		list( APPEND INCLUDE_DIRS ${${package}_INCLUDE_DIRS} )
	endif()
endforeach()

#================================================#
# Add the target
#================================================#
target_link_directories( ${PROJECT_NAME}
	PRIVATE
		${LIBPUBLIC_DIR}
		${LIBCOMMON_DIR}
)

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

# We can loop through all the libs and use find library to find everything the user specified
foreach( link_lib IN LISTS LINK_LIBS )
	if ( NOT ${IS_WINDOWS} )
		set( LIB_${link_lib} "lib_path-NOTFOUND" )
		find_library( LIB_${link_lib} NAMES ${link_lib} PATHS ${LINK_DIRS} )
		
		# If libs are not found...
		if ( LIB_${link_lib} EQUAL "LIB_${link_lib}-NOTFOUND" )
			message( WARNING "Unable to find library ${link_lib}!" )
		else()
			list( APPEND ACTUAL_LIBS ${LIB_${link_lib}} )
		endif()
	endif()
endforeach()

target_sources( ${PROJECT_NAME} PRIVATE ${SOURCE_FILES} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} )
target_link_libraries( ${PROJECT_NAME} PUBLIC ${DEPENDENCIES} )
if ( ${IS_WINDOWS} )
	target_link_libraries( ${PROJECT_NAME} ${LINK_LIBS} )
endif ()
target_compile_definitions( ${PROJECT_NAME} PUBLIC ${DEFINES} )
set_target_properties( ${PROJECT_NAME}
	PROPERTIES
		FOLDER "${IDE_FOLDER}"
		LINKER_LANGUAGE CXX
)

set_property( DIRECTORY ${ROOT_DIR} APPEND PROPERTY ASRC_${IDE_FOLDER} "${PROJECT_NAME}" )

if ( ${THIS_IS_A_STATIC_LIB} )
	set_target_properties( ${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON )
endif ()
if ( ${THIS_IS_A_MODULE_LIB} )
	set_target_properties( ${PROJECT_NAME} PROPERTIES PREFIX "" )
endif ()

if ( ${PRECOMPILED_HEADERS} )
	target_precompile_headers( ${PROJECT_NAME} PUBLIC ${PRECOMPILED_HEADERS} )
endif()
