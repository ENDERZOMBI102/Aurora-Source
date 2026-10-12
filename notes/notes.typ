#set document(
	title: [Notes for the Nothern Lights],
	description: [],
	author: "ENDERZOMBI102",
	keywords: ("Source Engine", "Source SDK 2013 MP"),
)

// styling
#set text( font: "Noto Serif", size: 13pt )

#show math.equation: set text( fill: rgb( "#c246fa" ) )

#set list( indent: 3pt )

#show link: set text( fill: rgb( "#0012aa" ) )

#set heading( numbering: "1." )
#show heading.where( numbering: "1.", level: 1 ): it => {
  pagebreak( weak: true )
  it
}

#show table.cell.where( y: 0 ): set text( weight: "bold" )
#set table( fill: (_, y) => if calc.odd( y ) { rgb( "#EAF2F5" ) } else { none } )

#set quote( block: true )
#show quote: set align( left )
#show quote: set pad( x: 3em )

#let gh( name, path ) = link( "https://github.com/" + path, name )


// Table of content page
#[
  #set page( numbering: "I" )
  #show outline.entry.where( level: 1 ): set text( weight: "bold" )
  #counter( page ).update( 1 )
  #outline()
]
#counter( page ).update( 1 )
#set page( numbering: "1", margin: 2cm )


// Rest of document
= Notable libraries
Libraries which we might want to use for stuff.

#table(
    columns: 3,
    table.header( [Scope], [License], [Purpose] ),
    [Bink Decoder],
        [#gh([Repo], "StrataSource/libbinkdec")],
        [Replace RadGameTools's proprietary BINK decoder],
    [Ogg],
        [#gh([Repo], "xiph/ogg"), #gh([Strata fork], "StrataSource/ogg")],
        [Dependency of webm],
    [Ogg Vorbis],
        [#gh([Repo], "xiph/vorbis"), #gh([Strata fork], "StrataSource/vorbis")],
        [Dependency of webm],
    [VPX],
        [#gh([Repo], "webmproject/libvpx"), #gh([Strata fork], "StrataSource/libvpx")],
        [Dependency of webm],
    [webm],
        [#gh([Repo], "webmproject/libwebm"), #gh([Strata fork], "StrataSource/libwebm")],
        [Alternative video format for playback/encode],
    [Steam Audio],
        [#gh([Repo], "ValveSoftware/steam-audio"), #gh([Strata fork], "StrataSource/steam-audio")],
        [Alternative "middleware" to the Miles Sound System],
    [PocketSphinx],
        [#gh([Repo], "cmusphinx/pocketsphinx")],
        [Replacement for lostware library/sapi used in phonomeextractor],
    [Volt],
        [#gh([Repo], "misyltoad/VPhysics-Jolt"), #gh([Strata fork], "StrataSource/VPhysics-Jolt")],
        [Replacement module for vphysics/Havoc IVP],
    [Qt],
        [#gh([Repo], "qt/qtbase"), #gh([Strata fork], "StrataSource/qtbase")],
        [To write actually portable GUI tooling],
    [ImGui],
        [#gh([Repo], "ocornut/imgui"), #gh([Strata fork], "StrataSource/imgui")],
        [To write good in-engine GUI tooling],
    [RmlUI],
        [#gh([Repo], "mikke89/RmlUi")],
        [Maybe to replace vgui2?],
    [dxvk],
        [#gh([Repo], "doitsujin/dxvk"), #gh([Strata fork], "StrataSource/dxvk")],
        [Better -- and more generic -- togl replacement],
    [Squirrel],
        [#gh([Repo], "albertodemichelis/squirrel")],
        [To reimplement vscript],
    [AngelScript],
        [#link("https://www.angelcode.com/angelscript")[Site]],
        [To implement something akin Strata's scripting, but probably for UI as well],
    [Lua],
        [#link("https://www.lua.org/")[Site], #gh([LuaJIT Repo], "LuaJIT/LuaJIT"),\ #gh([Luau Repo], "luau-lang/luau")],
        [I hate js with passion, i'd rather use Lua for UI scripting],
    [ffmpeg project],
        [#link("https://ffmpeg.org")[Site], #link("https://git.ffmpeg.org/gitweb/ffmpeg.git")[Repo]],
        [Unified "abstraction" over many audio/video formats],
//    [],
//        [],
//        [],
)


= GPU considerations
Using the GPU to accelerate some computations may be an interesting idea, although not all platforms we'll support have
this option, it may be valuable to still explore it, as it may unlock some performace and/or other improvements.

There are various options to make use of GPUs as generic compute devices:
- CUDA
- OpenCL
- OpenGL compute shaders (GL>=4.3)
- Vulkan compute shaders (VK>=1.0)

Any one of them has its pros and cons, but quite a simple note about them makes choosing easy: platform support.
The most cross-platform options are Vulkan, OpenCL and OpenGL; in that order.

== NVidia shenanegans
PhysX is a very powerful physics library, it shines most on liquid, cloth and destructible objects simulation.

CUDA is also a quite interesting GPGPU interface, making the programmer able to use an NVidia GPU as a generic highly
parralel computational device.

Unfortunately, NVidia decided to discontinue general 32bit support in their RTX 50xx series, causing anything that used
those libraries to break completely.

CUDA 12 onwards is not even able to target 32bit, so its kinda of a meh situation as we do target 32bit as well.


= C/++ stuff
== The GCC `textrel` section warning
A static library compiled without the -fpic option was included in a shared library, check the cmake configuration!!
// https://gcc.gnu.org/legacy-ml/gcc-help/2006-11/msg00390.html

== The glibc "cannot enable executable stack" error
In glibc version 2.41 a change was made to `dlopen` and `dlmopen` which reads:
#quote( attribution: link("https://lists.gnu.org/archive/html/info-gnu/2025-01/msg00014.html")[GNU Archives] )[
    `dlopen` and `dlmopen` no longer make the stack executable if a shared
    library requires it, either implicitly because of a missing `GNU_STACK`
    ELF header (and default ABI permission having the executable bit set)
    or explicitly because of the executable bit in `GNU_STACK`, and the
    stack is not already executable. Instead, loading such objects will
    fail.
]
To work around this mess, you may add `GLIBC_TUNABLES=glibc.rtld.execstack\=2` to the environment variables when running
the game.

== Avoiding the preprocessor for conditional code compilation
One may use `if constexpr ( IsDebug() )` and normal `if ( IsDebug() )`s instead of `#if IsDebug()` directives,
Consider the following code:
```cpp
#define IsDebug() false

void function() {
    if ( IsDebug() ) {
        printf("Hello\n");
    }
}
```
In this snippet, as the condition is always `false`, the branch is actually removed from the result binary;
as long as we're using a compiler that supports this, as always, MSVC is the odd-one-out:

#table(
    columns: 2,
    table.header( [Compiler], [Requirement] ),
    [MSVC 19]   , [`-O1`],
    [GCC 13]    , [None],
    [Clang 17]  , [None],
    [Zig >=0.16], [None],
    [Zig <=0.11], [`-O1`],
)

This said, unless the preprocessor is used, code is still analyzed and typechecked, which is an issue when we're using
conditional compilation for cross-platform function implementations; for those, either the preprocessor must still be
used, or functions prototypes of non-current platforms must be included in the build to let the compiler typecheck correctly.

= Source Compilers
== VMPI
VMPI is a Message Passing Interface library written by Valve, it is used to handle compile clusters for maps.
Its original code is mostly broken and/or lost, which means it needs to go; although we still want this functionality.
It will be replaced by a custom implementation, which hopefully will not be abandoned like its Valve cousin.
Additionally, VMPI also handled a MySQL database with statistics on compile times and general cluster info, would be nice to still have it.

== Additional compiler args file
All the map compilers accept additional arguments via a file located at `$modDir/cfg/commandline.cfg`.
It consists in kv1-formatted data, with a main key `CommandLine` with child kv-pairs with the compiler's name as key and
additional args as value.

=== Example
```kdl
// mod_hl2mp/cfg/commandline.cfg
"CommandLine" {
    "vvis" "-fast"
    "vbsp" "-game hl2"
}
```
In this example, we added the `-fast` flag to the vvis compiler, and a `-game hl2` arg to vbsp,
which will cause for vvis to compile in fast mode and for vbsp to add hl2 as a search path respectively.

== Structured exception handling
On windows, Source handles exceptions (see table bellow) with a custom message box (confirm?).
But when tools are used, there is an additional minidump step before it,
which still uses the same [Structured Exception Handling](https://learn.microsoft.com/en-us/windows/win32/debug/structured-exception-handling) system, which needs reimplementation for Linux.

#[
    #show table.cell.where( x: 1 ): set text( size: 0.8em )
    #table(
        columns: 2,
        table.header( [Exception], [Description] ),
        `EXCEPTION_ACCESS_VIOLATION`        , [The thread tried to read from or write to a virtual address for which it does not have the appropriate access.],
        `EXCEPTION_ARRAY_BOUNDS_EXCEEDED`   , [The thread tried to access an array element that is out of bounds and the underlying hardware supports bounds checking.],
        `EXCEPTION_BREAKPOINT`              , [A breakpoint was encountered.],
        `EXCEPTION_DATATYPE_MISALIGNMENT`   , [The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on.],
        `EXCEPTION_FLT_DENORMAL_OPERAND`    , [One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value.],
        `EXCEPTION_FLT_DIVIDE_BY_ZERO`      , [The thread tried to divide a floating-point value by a floating-point divisor of zero.],
        `EXCEPTION_FLT_INEXACT_RESULT`      , [The result of a floating-point operation cannot be represented exactly as a decimal fraction.],
        `EXCEPTION_FLT_INVALID_OPERATION`   , [This exception represents any floating-point exception not included in this list.],
        `EXCEPTION_FLT_OVERFLOW`            , [The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type.],
        `EXCEPTION_FLT_STACK_CHECK`         , [The stack overflowed or underflowed as the result of a floating-point operation.],
        `EXCEPTION_FLT_UNDERFLOW`           , [The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type.],
        `EXCEPTION_ILLEGAL_INSTRUCTION`     , [The thread tried to execute an invalid instruction.],
        `EXCEPTION_IN_PAGE_ERROR`           , [The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network.],
        `EXCEPTION_INT_DIVIDE_BY_ZERO`      , [The thread tried to divide an integer value by an integer divisor of zero.],
        `EXCEPTION_INT_OVERFLOW`            , [The result of an integer operation caused a carry out of the most significant bit of the result.],
        `EXCEPTION_INVALID_DISPOSITION`     , [An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception.],
        `EXCEPTION_NONCONTINUABLE_EXCEPTION`, [The thread tried to continue execution after a noncontinuable exception occurred.],
        `EXCEPTION_PRIV_INSTRUCTION`        , [The thread tried to execute an instruction whose operation is not allowed in the current machine mode.],
        `EXCEPTION_SINGLE_STEP`             , [A trace trap or other single-instruction mechanism signaled that one instruction has been executed.],
        `EXCEPTION_STACK_OVERFLOW`          , [The thread used up its stack.],
    )
]
