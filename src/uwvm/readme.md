# UWVM command-line program
Providing a UWVM command line program

* `main.cpp` main function for linking
* `cmdline` uwvm program-specialized command line processing
* `crtmain` Stores C++ global variables for raii control, C++ utf-8 main functions, and special command line parsing on windows NT.
* `custom` User-defined structures such as version information
* `run` Run the wasm program
* `wasm` Storing wasm-related stuff