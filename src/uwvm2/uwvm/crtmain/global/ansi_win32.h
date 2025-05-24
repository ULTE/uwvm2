/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-21
 * @copyright   ASHP-1.0 License
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

/// @brief      only support on winnt (with win32 api)
#if (defined(_WIN32) && !defined(__CYGWIN__)) && !defined(_WIN32_WINDOWS)

# ifdef UWVM_MODULE
import fast_io;
# else
// std
#  include <cstdint>
#  include <memory>
// macro
#  include <uwvm2/utils/macro/push_macros.h>
// import
#  include <fast_io.h>
# endif

# ifndef UWVM_MODULE_EXPORT
#  define UWVM_MODULE_EXPORT
# endif

UWVM_MODULE_EXPORT namespace uwvm2::uwvm::global
{
    /// @brief      cmd on windows nt does not enable ansi escaping by default.
    /// @details    Declare this via a global variable to set up ansi escaping at program runtime.
    ///             No need to restore, the console is automatically restored at the end of the program
    struct enable_win32_ansi
    {
        inline static constexpr ::std::uint_least32_t enable_virtual_terminal_processing{0x0004u /*ENABLE_VIRTUAL_TERMINAL_PROCESSING*/};

        UWVM_GNU_COLD inline enable_win32_ansi() noexcept
        {
            ::std::uint_least32_t out_omode{};
            ::std::uint_least32_t err_omode{};
            void* out_handle{::fast_io::win32::GetStdHandle(::fast_io::win32_stdout_number)};
            void* err_handle{::fast_io::win32::GetStdHandle(::fast_io::win32_stderr_number)};
            ::fast_io::win32::GetConsoleMode(out_handle, ::std::addressof(out_omode));
            ::fast_io::win32::GetConsoleMode(err_handle, ::std::addressof(err_omode));
            ::fast_io::win32::SetConsoleMode(out_handle, out_omode | enable_virtual_terminal_processing);
            ::fast_io::win32::SetConsoleMode(err_handle, err_omode | enable_virtual_terminal_processing);
        }
    };
}  // namespace uwvm2::uwvm::global

# ifndef UWVM_MODULE
// macro
#  include <uwvm2/utils/macro/pop_macros.h>
# endif
#endif

