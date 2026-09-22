# Aurora Source
A "branch" of the source engine, forked off SDK 2013's codebase.

This project aims to recreate the missing pieces of the engine, with completely custom code,
using leaks is completely banned, they only hurt and help nothing.

Project goals include:
- Full Linux compatability
- Faster compilers
- Scripting (ala vscript)
- Bring in Mapbase improvements
- Bring in TF2 sdk improvements
- x86_64 port
- Support for most Strata Source formats


## Compiler Support
By default, this targets C++23, so any compliant compiler should work fine. 

### Windows
VS2022 is known to build, but this is untested with older versions.

### Linux
GCC 14 or greater is (probably) needed, haven't tested with older versions.   
Clang is not yet fully tested, so might compile or might not.   
Zig is the same story as clang, as it is used under hood.

### macOS
Support for macOS was removed.

## Building
1. Clone with recursion this repo (`git clone $url --recursive`)
2. Create cmake build directory
3. Configure the build, all configurable options are defined inside `_cmake_scripts/options.cmake`
4. Invoke build action with desired target inside build directory (ex. `cmake --build . -t client_hl2mp --parallel`)
5. Built binaries will be located inside the `game` directory

## License
Aurora Source uses a dual license system:
- Code by or derived from Valve's Source SDKs is under the original [Source 1 SDK license](LICENSE_valve)
- Any reimplementation or code made primarily by us (usually denoted by a "Created by" header) is under the [MPL-2 license](LICENSE_asource)

## Leak Policy
We do not endorse nor allow for any contributions derived from leaked code; this is a leak-free project.

## LLM Policy
We do not allow for LLM-generated output to be PR'd, as LLMs have knowledge and leaked code inside their dataset (GitHub),
one cannot resonably be sure their outputs are clean.

## Credits
- [Spirrwell](https://github.com/Spirrwell), for making the [cmake port](https://github.com/Spirrwell/source-sdk-2013-cmake) and general adaptations this codebase is based upon.
- [JJl772](https://github.com/JJL772), for his [repo](https://github.com/JJL772/source-sdk-2013) which helped me with the ABI difference issues on newer GCC versions, and his [archives of the Source SDKs](https://github.com/Source-SDK-Archives).
- [OzxyBox](https://github.com/ozxybox), for general help during development, for his work on porting the [SDK to VS2022](https://github.com/ozxybox/source-mp13-vs2022), and for all the [examples and PoCs](https://github.com/Source-SDK-Resources) he has made which helped a lot to recreate some of the systems in the engine.
- [Autumn "Misyltoad"](https://github.com/Joshua-Ashton), for her work on [VPhysics-Jolt](https://github.com/misyltoad/VPhysics-Jolt)
- The contributors of the [Source PlusPlus](https://github.com/Joshua-Ashton/Source-PlusPlus) project (above + [SCell555](https://github.com/SCell555) and [Gocnak](https://github.com/Gocnak), for their modified `particles.lib`, which allows modern VS to build.
- [Sortie](https://github.com/sortie), for [the patches](https://github.com/sortie/source-sdk-2013/tree/for-valve-posix-port-vbsp-vvis-vrad-v2-part1) I've referenced to get the compilers to work on linux.
