/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @file        prefetch.cppm
 * @brief       cpu prefetch instruction
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
// no import
#else
// macro
# include <utils/macro/push_macros.h>
// include
/// @brief      Including intrin.h in the absence of __builtin_prefetch
# if !__has_builtin(__builtin_prefetch)
#  include <intrin.h>;
# endif
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace utils::intrinsics
{
    /// @brief      Direct conversion to cpu prefetch instructions
    /// @details    write: write or read sensitive
    ///             level == 0 -> nta (Non-Temporal Access)
    ///             level == 1 -> L3
    ///             level == 2 -> L2, L3
    ///             level == 3 -> L1, L2, L3
    /// @param      address address to be prefetched
    /// @see        __builtin_prefetch and _mm_prefetch
    template <bool write = false, int level = 3>
        requires (0 <= level && level <= 3)
    UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL inline void prefetch(void const* address) noexcept
    {
#if __has_builtin(__builtin_prefetch)
        __builtin_prefetch(address, static_cast<int>(write), level);
#else
        ::_mm_prefetch(reinterpret_cast<char const*>(address), static_cast<int>(write) << 2 | level);
#endif
    }

}  // namespace utils::intrinsics

