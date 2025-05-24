> [!IMPORTANT]
> This project is currently only developer stable
>

<div style="text-align:center">
    <h1>Ultimate WebAssembly Virtual Machine</h1>
    <a href="https://github.com/UlteSoft/uwvm2/actions?query=workflow%3ACI">
        <img src="https://img.shields.io/github/actions/workflow/status/UlteSoft/uwvm2/ci.yml?branch=master" alt="github-ci" />
    </a>
    <a href="LICENSE.md">
        <img src="https://img.shields.io/badge/License-ASHP%201.0-green.svg" , alt="License" />
    </a>
    <a href="https://en.cppreference.com">
        <img src="https://img.shields.io/badge/language-c++26-blue.svg" ,alt="cppreference" />
    </a>
</div>

## Introduce
Ultimate WebAssembly Virtual Machine (Version 2), the abbreviation is uwvm2.

## Features
### WASM Feature Extensions
Most wasm standards are supported. See [feature.md](documents/features.md)

### Supports multiple platforms
Supports over 100 triplet platforms, including DOS series, POSIX series, Windows 9x series, Windows NT series, and the Host C Library Series. Supports interpretation execution (INT), just-in-time compilation (JIT), and tiered compilation (TC). See [support.md](documents/support.md) for details.

## How to build
* Windows (aka. unknown-windows-msvc). See [windows.md](documents/how-to-build/windows.md)
* MinGW (aka. unknown-windows-gnu, unknown-w64-mingw32). See [mingw.md](documents/how-to-build/mingw.md)
* Linux (aka. unknown-linux-unknown). See [linux.md](documents/how-to-build/linux.md)
* Darwin (aka. unknown-apple-darwin). See [darwin.md](documents/how-to-build/darwin.md)
* FreeBSD (aka. unknown-freebsd(Version)). See [freebsd.md](documents/how-to-build/freebsd.md)
* WASM-WASI (aka. [wasm32|wasm64]-[wasip1|wasip2]-(threads)). See [freebsd.md](documents/how-to-build/wasm-wasi.md)