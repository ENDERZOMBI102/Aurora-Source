# windows_base.cmake
message( NOTICE "Platform   : Windows" )

add_compile_definitions(
	WIN32
	_WIN32
	_WINDOWS
	_X86_
)

if ( MSVC )
	include( "${CMAKE_CURRENT_LIST_DIR}/msvc_base.cmake" )
endif()

list( APPEND ADDITIONAL_SOURCES_EXE
	"${SRCDIR}/public/tier0/memoverride.cpp"
	"$<$<NOT:${IS_SOURCESDK}>:${SRCDIR}/public/windows_default.manifest>"
)

list( APPEND ADDITIONAL_SOURCES_DLL
	"${SRCDIR}/public/tier0/memoverride.cpp"
	"$<$<NOT:${IS_SOURCESDK}>:${SRCDIR}/common/debug_dll_check.cpp>"
)
list( APPEND ADDITIONAL_SOURCES_LIB
	"$<$<NOT:${IS_SOURCESDK}>:${SRCDIR}/common/debug_lib_check.cpp>"
)
