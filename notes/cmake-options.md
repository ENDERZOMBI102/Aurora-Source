## CMake options the project may search for
Notes
- all options are, well, optional
- `[]` indicates a comma-separated list of inner type
- `bool` indicates a boolean value (`1`, `on`, `true`, `0`, `off`, `false`)

| Name                    | Description                                                          | Accepted values                      |
|-------------------------|----------------------------------------------------------------------|--------------------------------------|
| BUILD_GROUP             | What targets should we define?                                       | everything, game, compilers, shaders |
| BUILD_GAME              | Which game are we building?                                          | hl2mp, sdk                           |
| RETAIL                  | Build in retail mode.                                                | bool                                 |
| STAGING_ONLY            | Build with staging asserts and code enabled.                         | bool                                 |
| USE_TOGL                | Use the `togl` translation layer.                                    | bool                                 |
| BUILD_REPLAY            | Build replay support.                                                | bool                                 |
| ASOURCE_OVERRIDE_MALLOC | Enables the `tier0` global allocator override (memalloc.cpp)         | bool                                 |
| ASOURCE_3RD_PARTY_LOGS  | Enables 3rd party libraries cmake output                             | bool                                 |
| ASOURCE_SKIP_x86_CHECK  | Skip the configure checks to ensure we're building for i686.         | bool                                 |
| ASOURCE_USE_REIMPLS     | Used to select what type of libraries will be used during the build. | 0, 1, \[target]                      |
