/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-15
 * @copyright   APL-2 License
 */

/****************************************
 *  _   _ __        ____     __ __  __  *
 * | | | |\ \      / /\ \   / /|  \/  | *
 * | | | | \ \ /\ / /  \ \ / / | |\/| | *
 * | |_| |  \ V  V /    \ V /  | |  | | *
 *  \___/    \_/\_/      \_/   |_|  |_| *
 *                                      *
 ****************************************/

#pragma once

#ifdef UWVM_MODULE
import fast_io;
#else
// std
# include <cstdint>
# include <cstddef>
# include <concepts>
# include <cstdlib>
# include <memory>
// macro
# include "ansi_push_macro.h"
// import
# include <fast_io.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace utils::ansies
{
    namespace details
    {
#if !(defined(_WIN32) && !defined(__CYGWIN__) && !defined(__WINE__))
# if defined(__DARWIN_C_LEVEL) || defined(__MSDOS__)
        extern char* libc_getenv(char const*) noexcept __asm__("_getenv");
# else
        extern char* libc_getenv(char const*) noexcept __asm__("getenv");
# endif
#endif
    }  // namespace details

    inline bool check_has_no_color() noexcept
    {
#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__WINE__)
# ifndef _WIN32_WINDOWS
        auto const curr_peb{::fast_io::win32::nt::nt_get_current_peb()};
        decltype(auto) env_str{u"NO_COLOR"};
        ::fast_io::win32::nt::unicode_string env_us{.Length = sizeof(env_str) - sizeof(char16_t),
                                                    .MaximumLength = sizeof(env_str),
                                                    .Buffer = const_cast<char16_t*>(env_str)};
        ::fast_io::win32::nt::unicode_string out_us{};
        auto status{
            ::fast_io::win32::nt::RtlQueryEnvironmentVariable_U(curr_peb->ProcessParameters->Environment, ::std::addressof(env_us), ::std::addressof(out_us))};
        return status == 0xc0000023 || status == 0x00000000;
# else
        auto no_color_env{::fast_io::win32::GetEnvironmentVariableA(reinterpret_cast<char const*>(u8"NO_COLOR"), nullptr, 0)};
        return static_cast<bool>(no_color_env);
# endif
#else
        auto no_color_env{details::libc_getenv(reinterpret_cast<char const*>(u8"NO_COLOR"))};
        return static_cast<bool>(no_color_env);
#endif
    }

    inline bool const put_color{!check_has_no_color()};  // No global variable dependencies from other translation units

}  // namespace utils::ansies
