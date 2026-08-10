# init.cmake

# Function to add a git module as project
function( submodule name folder )
	# check for existence
	if ( NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${folder}/CMakeLists.txt" )
		message( FATAL_ERROR "Third-party submodule library `${name}` was not found! Did you clone with `--recursive`?\nNote: you may run `git submodule init && git submodule update` to fix" )
	endif()

	add_subdirectory( "${CMAKE_CURRENT_LIST_DIR}/${folder}" EXCLUDE_FROM_ALL SYSTEM )
endfunction()


# For git submodules, declare them here
# ----- SDL -----
set( SDL_STATIC ON )
set( SDL_SHARED ON )
set( SDL_ATOMIC OFF )
set( SDL_AUDIO  OFF )
set( SDL_VIDEO  ON )
set( SDL_VIDEO  ON )
set( SDL_CAMERA OFF )
set( SDL_GPU    OFF )
set( SDL_HAPTIC ON )
# `SDL_HIDAPI` is needed for bug on `src/joystick/linux/SDL_sysjoystick.c:323`,
# where an usage of `IsVirtualJoystick` (hidden behind SDL_HIDAPI) isn't disabled when the flag is not given.
set( SDL_HIDAPI ON )
set( SDL_POWER  OFF )
set( SDL_SENSOR OFF )
set( SDL_DIALOG ON )
set( SDL_FILE   OFF )
set( SDL_LOADSO ON )  # needed by other modules
set( SDL_FILESYSTEM OFF )
set( SDL_LOCALE OFF )
set( SDL_MISC   ON )
submodule( SDL "SDL" )
# ----- SourcePP -----
set( SOURCEPP_LIBS_START_ENABLED OFF CACHE INTERNAL "" )
set( SOURCEPP_USE_VPKPP ON CACHE INTERNAL "" )
set( SOURCEPP_USE_VTFPP ON CACHE INTERNAL "" )
set( SOURCEPP_USE_BSPPP ON CACHE INTERNAL "" )
set( SOURCEPP_USE_STEAMPP ON CACHE INTERNAL "" )
set( SOURCEPP_VTFPP_SUPPORT_EXR OFF CACHE INTERNAL "" )
set( SOURCEPP_VTFPP_SUPPORT_QOI OFF CACHE INTERNAL "" )
set( SOURCEPP_VTFPP_SUPPORT_WEBP OFF CACHE INTERNAL "" )
set( SOURCEPP_VTFPP_BUILD_WITH_COMPRESSONATOR OFF CACHE INTERNAL "" )
set( XZ_ASM_I386 OFF CACHE INTERNAL "" )
set( XZ_NLS OFF )
set( MZ_BZIP2 OFF )
submodule( SourcePP "sourcepp" )
# ----- tracy -----
submodule( Tracy "tracy" )
# ----- mimalloc -----
set( MI_BUILD_TESTS OFF )
set( MI_OVERRIDE OFF )
set( MI_OSX_INTERPOSE OFF )
set( MI_OSX_ZONE OFF )
set( MI_WIN_REDIRECT OFF )
set( MI_BUILD_STATIC OFF )
set( MI_BUILD_OBJECT OFF )
submodule( MiMalloc "mimalloc" )
