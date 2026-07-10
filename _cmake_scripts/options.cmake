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
set( BUILD_GAME "hl2mp" CACHE STRING "Build Game" )
set_property( CACHE BUILD_GAME PROPERTY STRINGS
    "hl2mp"
    "sdk"
)

option( RETAIL "Build in retail mode" OFF )
option( STAGING_ONLY "Staging only" OFF )
option( USE_TOGL "Use the `togl` translation layer" ${IS_LINUX} )
option( BUILD_REPLAY "Build replay support" OFF )
set( ASRC_SKIP_x86_CHECK ${ASRC_SKIP_x86_CHECK} CACHE STRING "Skip the 64bit build checks" )

# Technically options, but hardcoded (for now at least)
set( IS_SOURCESDK 1 )
set( RAD_TELEMETRY_DISABLED ${IS_SOURCESDK} )
set( TF_BETA 0 )
