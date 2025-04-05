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

module;

#include <cstdint>
#include <cstddef>
#include <concepts>
#include <bit>

#include <parser/wasm/feature/feature_push_macro.h>

export module parser.wasm.proposal.relaxed_simd.type:value_type;

import fast_io;

export namespace parser::wasm::proposal::relaxed_simd::value_type
{

    /// @brief      bf16
    /// @details    new feature
    /// @see        https://github.com/WebAssembly/relaxed-simd/issues/77
#if defined(UWVM_WASM_SUPPORT_BF16)
    using wasm_bf16 = decltype(0.0bf16);
#endif

}  // namespace parser::wasm::proposal::relaxed_simd::value_type
