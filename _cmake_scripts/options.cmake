# options.cmake

# This is a way to emulate groups.vgc
set( BUILD_GROUP "game" CACHE STRING "Build Group" )
set_property( CACHE BUILD_GROUP PROPERTY STRINGS
    "everything"
    "game"
    "shaders"
    "compilers"
)

# Which game are we building?
set( BUILD_GAME "hl2mp" CACHE STRING "Which game to build" )
set_property( CACHE BUILD_GAME PROPERTY STRINGS
    "hl2mp"
    "sdk"
)

option( RETAIL "Build in retail mode" OFF )
option( STAGING_ONLY "Staging only" OFF )
option( USE_TOGL "Use the `togl` translation layer" ${IS_LINUX} )
option( BUILD_REPLAY "Build replay support" OFF )
option( ASOURCE_OVERRIDE_MALLOC "Enable the tier0 global allocator override (memalloc.cpp)" OFF )
option( ASOURCE_3RD_PARTY_LOGS "Toggles 3rd party libraries cmake output" OFF )
set( ASOURCE_SKIP_x86_CHECK ${ASOURCE_SKIP_x86_CHECK} CACHE STRING "Skip the 64bit build checks" )
set( ASOURCE_REIMPL ${ASOURCE_REIMPL} CACHE STRING "Either a ,-separated list of targets for which enable building or 1 for enable all" )
set( ASOURCE_DX9SDK_PATH CACHE STRING "Absolute path to the dx9 sdk" )

# Technically options, but hardcoded (for now at least)
set( IS_SOURCESDK 1 )
set( RAD_TELEMETRY_DISABLED ${IS_SOURCESDK} )
set( TF_BETA 0 )
