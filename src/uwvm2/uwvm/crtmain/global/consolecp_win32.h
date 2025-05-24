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
    /// @brief      The ConsoleCP of Windows is affected by system environment variables.
    ///             By setting SetConsoleCP and SetConsoleOutputCP, it can be unified to UTF-8.
    ///             No need to restore, the console is automatically restored at the end of the program
    /// @see        https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
    struct set_win32_console_io_cp_to_utf8
    {
        inline static constexpr ::std::uint_least32_t utf8_coding{65001u /*Unicode (UTF-8)*/};

        UWVM_GNU_COLD inline set_win32_console_io_cp_to_utf8() noexcept
        {
            ::fast_io::win32::SetConsoleOutputCP(utf8_coding);
            ::fast_io::win32::SetConsoleCP(utf8_coding);
        }
    };

}  // namespace uwvm2::uwvm::global

# ifndef UWVM_MODULE
// macro
#  include <uwvm2/utils/macro/pop_macros.h>
# endif
#endif

