# groups.cmake

# get what build groups we support
get_property( _BUILD_GROUPS CACHE "BUILD_GROUP" PROPERTY "STRINGS" )
if ( NOT DEFINED BUILD_GROUP )
    message( FATAL_ERROR "No build group was passed, please choose one of the following: ${_BUILD_GROUPS}" )
elseif ( NOT ("${BUILD_GROUP}" IN_LIST _BUILD_GROUPS) )
    message( FATAL_ERROR "Invalid build group `${BUILD_GROUP}`, valid groups are: ${_BUILD_GROUPS}" )
endif()

# add_group_subdir( $path IN $group0 $group1 ... [WINDOWS_ONLY] [LINUX_ONLY] )
#   All included projects are assumed to be cross-platform,
#   it is up to the maintainer to mark them as closed-platform with the respective options.
function( add_group_subdir path )
    cmake_parse_arguments( GP "WINDOWS_ONLY;LINUX_ONLY" "" "IN" ${ARGN} )

    # everything is truly everything!
    list( APPEND GP_IN "everything" )

    # check pre-conditions...
    if ( ${GP_WINDOWS_ONLY} AND NOT ${IS_WINDOWS} )
        return()
    elseif ( ${GP_LINUX_ONLY} AND NOT ${IS_LINUX} )
        return()
    elseif ( NOT (${BUILD_GROUP} IN_LIST GP_IN) )
        return()
    endif ()

    # all pre-conditions were met, lets add it!
    add_subdirectory( "${path}" )

    # check that all declared build groups have been defined, so to be consistent
    foreach ( GROUP ${GP_IN} )
        if ( NOT (${GROUP} IN_LIST _BUILD_GROUPS) )
            message( WARNING "Project at `${path}` used unknown build group `${GROUP}`, was this intentional?" )
        endif ()
    endforeach ()
endfunction()
