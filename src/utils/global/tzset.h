/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-21
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
// macro
# include <utils/macro/push_macros.h>
// import
# include <fast_io.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif
UWVM_MODULE_EXPORT namespace utils::global
{
    /// @brief      Declare this via a global variable to get the correct timezone data when the program is run.
    struct tz_set_s
    {
        /// @brief      The tzset() function initializes the tzname variable from the TZ environment variable.
        /// @see        tzset(3)
        UWVM_GNU_COLD inline tz_set_s() noexcept { ::fast_io::posix_tzset(); }
    };
}  // namespace utils::global
