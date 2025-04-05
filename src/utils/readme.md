# utilities
Includes various widgets

## widgets
* `ansies` An implementation of UTF-8 ANSI Escape Sequences that provides macros or outputable manipulation structures.
* `cmdline` Command line infrastructure to generate hash tables at compile time, including generate function, lookup function
* `debug` Debugging Tools
* `global` Program feature control via global raii
* `install_path` Get the path where the program binary is located, supports many systems
* `intrinsics` Provide some intrinsics functions, like prefetch, etc.
* `io` Provides interfaces to IO settings, (void*) `handle` on NT and Win32, (int) `fd 0 1 2` on POSIX, (FILE*) `stdin` `stdout` `stderr` on AvrLibc.
* `macro` Generic Macro Definitions
* `version` revision structure: 2.major.minor.patch