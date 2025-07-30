## CMake options the project may search for
Notes
- all options are, well, optional
- `[]` indicates a comma-separated list of inner type
- `bool` indicates a boolean value (`on`, `1`, `true`, `off`, `0`, `false`)

| Name                    | Description                                                          | Accepted values                      |
|-------------------------|----------------------------------------------------------------------|--------------------------------------|
| BUILD_GROUP             | What targets should we define?                                       | everything, game, compilers, shaders |
| BUILD_GAME              | Which game are we building?                                          | hl2mp, sdk                           |
| RETAIL                  | If we're building in retail mode.                                    | bool                                 |
| STAGING_ONLY            | If we're building with staging asserts and code enabled.             | bool                                 |
| USE_TOGL                | Whether to use `togl` for graphics.                                  | bool                                 |
| ASRC_NO_MALLOC_OVERRIDE | Disables overriding the standard allocator in `tier0/memoverride.h`. | bool                                 |
| ASRC_USE_REIMPLS        | Used to select what type of libraries will be used during the build. | 0, 1, \[target]                      |
