### Using `IsDebug()` and normal `if`s instead of directives
Consider the following code:
```c++
#define IsDebug() false

void function() {
    if ( IsDebug() ) {
        printf("Hello\n");
    }
}
```
One would think that, as the condition is always `false`, the branch is removed;
which is the case under specific circumstances, which we'll enumerate in the following table:

| Compiler | Requirement  |
|----------|--------------|
| MSVC 19  | `-O1`        |
| GCC 13   | Already done |
| Clang 17 | Already done |
| Zig 0.11 | `-O1`        |

### The GCC `textrel` section warning
https://gcc.gnu.org/legacy-ml/gcc-help/2006-11/msg00390.html


### The glibc "cannot enable executable stack" error
workaround: add `GLIBC_TUNABLES=glibc.rtld.execstack\=2` to env variables