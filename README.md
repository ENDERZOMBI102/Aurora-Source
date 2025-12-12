# Aurora Source
A "branch" of the source engine, forked off SDK 2013's codebase.

This project aims to recreate the missing pieces of the engine, with completely custom code,
using leaks is completely banned, they only hurt and help nothing.

Planned features include:
- Faster compilers
- Scripting (ala vscript)
- Mapbase compatability
- x64 port
- VTF 7.6 compatability


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

## Credits
- [Spirrwell](https://github.com/Spirrwell), for making the [cmake port](https://github.com/Spirrwell/source-sdk-2013-cmake) and general adaptations this codebase is based upon.
- [JJL772](https://github.com/JJL772), for his [repo](https://github.com/JJL772/source-sdk-2013) which helped me with the ABI difference issues on newer GCC versions, and his [archives of the Source SDKs](https://github.com/Source-SDK-Archives).
- [OzxyBox](https://github.com/ozxybox), for general help during development, for his work on porting the [SDK to VS2022](https://github.com/ozxybox/source-mp13-vs2022), and for all the [examples and PoCs](https://github.com/Source-SDK-Resources) he has done which helped a lot to recreate some of the systems in the engine.
- [Joshua Ashton](https://github.com/Joshua-Ashton), for his work on [VPhysics-Jolt](https://github.com/Joshua-Ashton/VPhysics-Jolt)
- The contributors of the [Source PlusPlus](https://github.com/Joshua-Ashton/Source-PlusPlus) project (above + [SCell555](https://github.com/SCell555) and [Gocnak](https://github.com/Gocnak), for their modified `particles.lib`, which allows modern VS to build.
- [Sortie](https://github.com/sortie), for [the patches](https://github.com/sortie/source-sdk-2013/tree/for-valve-posix-port-vbsp-vvis-vrad-v2-part1) I've referenced to get the compilers to work on linux.
