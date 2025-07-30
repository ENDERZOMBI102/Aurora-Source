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
function(link_to_bin)
	cmake_parse_arguments( LTB "" "TARGET" "" ${ARGN} )
	if ( NOT DEFINED "LTB_TARGET" )
		message( SEND_ERROR "Missing `TARGET` parameter!" )
		return()
	endif ()

	add_custom_command(
		TARGET ${LTB_TARGET}
		POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E $<IF:$<BOOL:${WIN32}>,copy,create_symlink> $<TARGET_FILE:${LTB_TARGET}> ${GAMEDIR}/bin/$<TARGET_FILE_NAME:${LTB_TARGET}>
	)
endfunction()

# Declares that a target may be replaced by another via `-DASRC_USE_REIMPLS=1`,
# or the more granular `-DASRC_USE_REIMPLS=$names`, where `$names` is a comma-separated list of replaced libraries names.
# As example, to link to the `tier0` or its reimplementation, you can do `target_link_libraries( ${target} ${vis} ${ASRC_tier0} )`
function(declare_replacement)
	cmake_parse_arguments( DR "" "TARGET;FOR" "" ${ARGN} )
	if ( NOT DEFINED "DR_TARGET" )
		message( SEND_ERROR "Missing `TARGET` parameter!" )
		return()
	endif ()
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
		set( "ASRC_DR_${DR_FOR}" $<IF:$<BOOL:${WIN32}>,$<TARGET_NAME:${DR_TARGET}>,$<TARGET_FILE:${DR_TARGET}>> PARENT_SCOPE )
		message( NOTICE "* using reimplemented library `${DR_TARGET}` for `${DR_FOR}`" )
	else ()
		set( "ASRC_DR_${DR_FOR}" $<IF:$<BOOL:${WIN32}>,$<TARGET_NAME:${DR_FOR}>,$<TARGET_FILE:${DR_FOR}>> PARENT_SCOPE )
		message( NOTICE "* using original library `${DR_FOR}`" )
	endif ()
endfunction()
