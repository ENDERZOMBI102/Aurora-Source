# helpers.cmake
include_guard(GLOBAL)

function(target_strip_symbols target)
	if ( ${IS_LINUX} )
		add_custom_command(
			TARGET ${target}
			POST_BUILD
				COMMAND ${CMAKE_OBJCOPY} "$<TARGET_FILE:${target}>" "$<TARGET_FILE:${target}>.dbg"
				COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink="$<TARGET_FILE:${target}>.dbg" "$<TARGET_FILE:${target}>"
				COMMAND ${CMAKE_STRIP} -x "$<TARGET_FILE:${target}>" $<$<CONFIG:Release>:-S>
		)
	endif()
endfunction()

# Creates a symlink from the target's output binary to the game/bin directory
function(link_to_bin target)
	add_custom_command(
		TARGET ${target}
		POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E $<IF:$<BOOL:${WIN32}>,copy,create_symlink> $<TARGET_FILE:${target}> ${GAMEDIR}/bin/$<TARGET_FILE_NAME:${target}>
	)
endfunction()

# Declares that a target may be replaced by another via `-DASRC_USE_REIMPLS=1`,
# or the more granular `-DASRC_USE_REIMPLS=$names`, where `$names` is a comma-separated list of replaced libraries names.
# As example, to link to the `tier0` or its reimplementation, you can do `target_link_libraries( ${target} ${vis} asrc::dr::tier0 )`
function(declare_replacement target)
	cmake_parse_arguments( DR "" "FOR" "" ${ARGN} )
	if ( NOT DEFINED "DR_FOR" )
		message( SEND_ERROR "Missing `FOR` parameter!" )
		return()
	endif ()

	set( replace 0 )
	if ( DEFINED "ASRC_USE_REIMPLS" )
		if ( "${ASRC_USE_REIMPLS}" STREQUAL "1" )
			set( replace 1 )
		elseif ( "${ASRC_USE_REIMPLS}" MATCHES "${DR_FOR},?" )
			set( replace 1 )
		endif ()
	endif ()

	if ( ${replace} )
		add_library( asrc::dr::${DR_FOR} ALIAS ${target} )
		message( NOTICE "  * using reimplemented library `${target}` for `${DR_FOR}`" )
	else ()
		add_library( asrc::dr::${DR_FOR} ALIAS ${DR_FOR} )
		message( NOTICE "  * using original library `${DR_FOR}`" )
	endif ()
endfunction()
