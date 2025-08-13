# CommandLine arguments
A list, divided in used-by-module section, of all arguments

### `launcher`
- `-vulkan`: Enables the use of the DXVK library to translate Direct3D graphics calls to the Vulkan API.
- `-dedicated`:
  - Starts a Source dedicated server instead of a client.
- `-noshaderapi`:
  - Loads a non-existent shader API dll, `shaderapiempty.dll`.
  - Effectively disables shader and texture loading completely.
  - May be useful with `-textmode` to load the game quickly since a GUI is not required.
- `-shaderdll`: Loads a different shader dll. Default is `shaderapidx9.dll`.
- `-sleepatstartup`: Sleeps for 5s upon entering `LauncherMain`.
- `-game`:
  - Specifies which game/mod to run.
  - Accepts a path to a `gameinfo.txt`.
  - Used to determine what Source mutex to use.

### `inputsystem`
- `-nojoy`: Disabled joystick/gamepad initialization.

### `tier0`
- `-hushasserts`: Makes `dbg.h::HushAsserts()bool` return `true`, which disables some asserts.

### `tier1`
- `-enable_keyvalues_cache`:
  - Enables the caching of keyvalues.
  - Only works in a `STAGING` build.
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
- `-makereslists`:
  - Makes reslists.
  - Needs to run with `-textmode`.
  - Passing a parameter here uses a script file to control more complex makereslists operations (multiple passes, etc.).
  - Enables the behavior of `C_SoundscapeSystem::TouchSoundFiles`.
- `-textmode`:
  - Runs the game without graphics, and instead launches a command prompt that displays the Developer Console outputs.
  - If the game is already running, launching the game with this command will simply boot the game up, like `-allowmultiple` or `-multirun`.
  - Sets `g_bTextMode` to `true`.
- `-makedevshots`:
  - Used for taking screenshots, causing entities to not fade.
  - Enables the use of the `devshots_nextmap` concommand.
  - Also disables the automatic loading of menu background maps.
  - Sets `g_MakingDevShots` to `true`.
- `-tools`: Enables [engine tools](engine-tools.md).
- `-g15`: Enables Logitech G15 support.
- `-nomouse`: Disables in-game mouse support.
- `-useforcedmparms`: Allows the use of `-noforcemspd` and `-noforcemaccel`.
- `-noforcemspd`:
  - Use the Windows mouse speed settings.
  - Only works if `-useforcedmparms` is also given.
- `-noforcemaccel`:
  - Use the Windows mouse acceleration settings.
  - Only works if `-useforcedmparms` is also given.
- `-particles`: Sets the number of beam trails to allow (2048 by default, minimum is 512).

### filesystem_init
- `-insert_search_path`: A `,`-separated list of additional `GAME` and `MOD` search paths.
- `-game`: The current game to mount.
- `-vproject`: Same as `-game`.
- `-tempcontent`: Searches for game content in a folder called `_tempcontent` relative to the absolute game path.

### Unsure
- `-profile`: Use basic profiler to log to `game/timestamped.log`.
