# options.cmake

# asource_option( $name $desc $default (BOOL|STRING|PATH|ENUM $entry...) )
#   Declares a cmake configure, user-facing, option for the project.
#   All declared options are prefixed by `ASOURCE_`, to namespace them.
function( asource_option name desc default )
    cmake_parse_arguments( AO "BOOL;STRING;PATH" "" "ENUM" ${ARGN} )
    # first get the actual value, we don't want to override the user's option by accident
    if ( DEFINED ASOURCE_${name} )
        set( actual ${ASOURCE_${name}} )
    else ()
        set( actual ${default} )
    endif ()

    # define the option
    if ( ${AO_BOOL} )
        option( ASOURCE_${name} ${desc} ${default} )
    elseif ( ${AO_STRING} )
        set( ASOURCE_${name} ${actual} CACHE STRING ${desc} )
    elseif ( ${AO_PATH} )
        set( ASOURCE_${name} ${actual} CACHE PATH ${desc} )
        # TODO: Check path
    elseif ( NOT "${AO_ENUM}" STREQUAL "" )
        set( ASOURCE_${name} ${actual} CACHE STRING ${desc} )
        set_property( CACHE ASOURCE_${name} PROPERTY STRINGS ${AO_ENUM} )
    else ()
        message( WARNING "No known option type was passed to `asource_option` for ${name}" )
    endif ()
endfunction()


asource_option( BUILD_GROUP "What targets to define" "game" ENUM "everything" "engine" "game" "tools" "shaders" )
asource_option( BUILD_GAME "Which game/mod to build" "hl2mp" ENUM "hl2mp" "sdk" )

asource_option( RETAIL "Build in retail mode" OFF BOOL )
asource_option( STAGING_ONLY "Build with staging asserts and code enabled" OFF BOOL )
asource_option( USE_TOGL "Use the `togl` translation layer" ${IS_LINUX} BOOL )
asource_option( BUILD_REPLAY "Build replay support" OFF BOOL )
asource_option( OVERRIDE_MALLOC "Enable the tier0 global allocator override (memalloc.cpp)" OFF BOOL )
asource_option( 3RD_PARTY_LOGS "Toggles 3rd party libraries cmake output" OFF BOOL )
asource_option( SKIP_x86_CHECK "Skip the configure checks to ensure we're building for i686" OFF BOOL )
asource_option( REIMPL "Either a comma-separated list of targets for which enable building or 1 for enable all" "" STRING )
asource_option( DX9SDK_PATH "Absolute path to the dx9 sdk" "" PATH )

# Technically options, but hardcoded (for now at least)
set( IS_SOURCESDK 1 )
set( RAD_TELEMETRY_DISABLED ${IS_SOURCESDK} )
set( TF_BETA 0 )
