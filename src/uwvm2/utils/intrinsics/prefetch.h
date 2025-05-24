/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @file        prefetch.cppm
 * @brief       cpu prefetch instruction
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

#ifdef UWVM_MODULE
// no import
#else
// macro
# include <uwvm2/utils/macro/push_macros.h>
// include
/// @brief      Including intrin.h in the absence of __builtin_prefetch
# if !UWVM_HAS_BUILTIN(__builtin_prefetch)
#  include <intrin.h>;
# endif
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::utils::intrinsics::universal
{
    enum class pfc_mode
    {
        read = 0,
        write = 1
    };

    enum class pfc_level
    {
        nta = 0,
        L3 = 1,
        L2 = 2,
        L1 = 3
    };

    /// @brief      Direct conversion to cpu prefetch instructions
    /// @details    write: write or read sensitive
    ///             level == 0 -> nta (Non-Temporal Access)
    ///             level == 1 -> L3
    ///             level == 2 -> L2, L3
    ///             level == 3 -> L1, L2, L3
    /// @param      address address to be prefetched
    /// @see        __builtin_prefetch and _mm_prefetch
    template <pfc_mode prefetch_write = pfc_mode::write, pfc_level prefetch_level = pfc_level::nta>
        requires ((0 <= static_cast<int>(prefetch_write) && static_cast<int>(prefetch_write) <= 1) &&
                  (0 <= static_cast<int>(prefetch_level) && static_cast<int>(prefetch_level) <= 3))
    UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL UWVM_GNU_NODEBUG inline void prefetch(void const* address) noexcept
    {
#if UWVM_HAS_BUILTIN(__builtin_prefetch)
        __builtin_prefetch(address, static_cast<int>(prefetch_write), static_cast<int>(prefetch_level));
#else
        ::_mm_prefetch(reinterpret_cast<char const*>(address), static_cast<int>(prefetch_write) << 2u | static_cast<int>(prefetch_level));
#endif
    }

}  // namespace uwvm2::utils::intrinsics::universal

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif
