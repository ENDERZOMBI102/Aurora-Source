set( CMAKE_SYSTEM_NAME "Windows" )
set( CMAKE_SYSTEM_PROCESSOR "x86" )

set( CMAKE_SHARED_LIBRARY_SUFFIX ".dll" )
set( CMAKE_SHARED_LIBRARY_PREFIX "" )
set( CMAKE_FIND_LIBRARY_SUFFIXES ".lib;.dll.a;.a" )
set( CMAKE_STATIC_LIBRARY_SUFFIX ".lib" )
set( CMAKE_STATIC_LIBRARY_PREFIX "" )

set( CMAKE_AR "zig-lib" )
set( CMAKE_RC_COMPILER "zig-rc" )
set( CMAKE_RANLIB "zig-ranlib" )

set( CMAKE_C_COMPILER "zig-cxx" )
set( CMAKE_C_COMPILER_TARGET "x86-windows-gnu" )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fms-extensions -Wno-date-time" )
set( CMAKE_CXX_COMPILER "zig-cxx" )
set( CMAKE_CXX_COMPILER_TARGET "x86-windows-gnu" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions -Wno-date-time" )

set( CMAKE_PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/x86-windows-gnu_post.cmake" )
