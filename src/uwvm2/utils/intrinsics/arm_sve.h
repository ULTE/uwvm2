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
 * @date        2025-05-16
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

#if defined(__ARM_FEATURE_SVE)

# ifdef UWVM_MODULE
// no import
# else
// std
#  include <cstddef>
#  include <cstdint>
# endif

# ifndef UWVM_MODULE_EXPORT
#  define UWVM_MODULE_EXPORT
# endif

UWVM_MODULE_EXPORT namespace uwvm2::utils::intrinsics::arm_sve
{
# if defined(__clang__)

    // Try to avoid the need for [[clang::__overloadable__]] code

    // clang-format off

    using svbool_t = __SVBool_t;
    using svuint8_t = __SVUint8_t;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svptrue_b8)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svbool_t svptrue_b8() noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svdup_n_u8)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svuint8_t svdup_n_u8(::std::uint8_t) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svptest_any)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern bool svptest_any(svbool_t, svbool_t) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svwhilelt_b8_u64)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svbool_t svwhilelt_b8_u64(::std::uint64_t, ::std::uint64_t) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svwhilelt_b8_u32)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svbool_t svwhilelt_b8_u32(::std::uint32_t, ::std::uint32_t) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svld1_u8)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svuint8_t svld1_u8(svbool_t, ::std::uint8_t const *) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svcmpge_n_u8)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern svbool_t svcmpge_n_u8(svbool_t, svuint8_t, ::std::uint8_t) noexcept;

    [[clang::__clang_arm_builtin_alias(__builtin_sve_svcntp_b8)]]
    [[__gnu__::__always_inline__]]
    [[__gnu__::__nodebug__]]
    extern ::std::uint64_t svcntp_b8(svbool_t, svbool_t);

    // clang-format on

# elif defined(__GNUC__)

    /* NOTE: This implementation of arm_sve.h is intentionally short.  It does
       not define the SVE types and intrinsic functions directly in C and C++
       code, but instead uses the following pragma to tell GCC to insert the
       necessary type and function definitions itself.  The net effect is the
       same, and the file is a complete implementation of arm_sve.h.  */

#  pragma GCC aarch64 "arm_sve.h"

# endif
}  // namespace uwvm2::utils::intrinsics::arm

#endif
