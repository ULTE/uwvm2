/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-03
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

#include <cstdint>
#include <cstddef>
#include <concepts>
#include <bit>

#include <parser/wasm/feature/feature_push_macro.h>

#ifdef UWVM_MODULE
export module parser.wasm.proposal.half_precision.type:value_type;
#endif

#ifdef UWVM_MODULE
export
#endif
    namespace parser::wasm::proposal::half_precision::value_type
{
    /// @brief      fp16
    /// @details    new feature
    /// @see        https://github.com/WebAssembly/half-precision
#if defined(UWVM_WASM_SUPPORT_FP16)
    using wasm_fp16 = __float16;
#endif

}  // namespace parser::wasm::proposal::half_precision::value_type
