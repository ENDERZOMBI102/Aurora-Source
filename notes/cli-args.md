# CommandLine arguments
A list, divided in used-by-module section, of all arguments

### `launcher`
- `-vulkan`: .
- `-dedicated`: .
- `-noshaderapi`: .
- `-sleepatstartup`: .
- `-game`: Source mutex

### `inputsystem`
- `-nojoy`: Disabled joystick/gamepad initialization.

### `tier0`
- `-hushasserts`: Makes `dbg.h::HushAsserts()bool` return `true`, which disables some asserts.

### `tier1`
- `-enable_keyvalues_cache`: .
- `-allowdebug`: Checks for debug modules.

### `togl`
- `-gl_enable_pseudobufs`: .
- `-gl_disable_static_buffer`: .
- `-dumpallshaders`: .
- `-disable_srgbtex`: .
- `-glmspewallsrgbflips`: .
- `-glmspewfirstsrgbflips`: .
- `-glmspewfreqsrgbflips`: .
- `-glmspewsrgbcrawls`: .
- `-glmspewsrgbmaxcrawls`: .
- `-nouserclip`: .
- `-noprintconsole`: .
- `-noprintdebugger`: .
- `-noprintglp`: .
- `-glmspew`: .
- `-glmbootspew`: .

### client
- `-makereslists`: Enables the behavior of `C_SoundscapeSystem::TouchSoundFiles`.
- `-textmode`: Sets `g_bTextMode` to `true`.
- `-makedevshots`: Sets `g_MakingDevShots` to `true`.
- `-tools`: .
- `-g15`: Enables Logitech G15 support.
- `-nomouse`: Avoids `CInput::Init_Mouse`.
- `-useforcedmparms`: .
- `-noforcemspd`: .
- `-noforcemaccel`: .
- `-particles`: .

### filesystem_init
- `-insert_search_path`: A `,`-separated list of additional `GAME` and `MOD` search paths.
- `-game`: The current game to mount.
- `-vproject`: Same as `-game`.
- `-tempcontent`: .

### Unsure
- `-profile`: Use basic profiler to log to `game/timestamped.log`.
