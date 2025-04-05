/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-04
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

export module parser.wasm.standard.wasm3.type:section_type;

import fast_io;
import parser.wasm.standard.wasm2;

export namespace parser::wasm::standard::wasm3::type
{
    /// @brief      Limits
    /// @details    Limits classify the size range of resizeable storage associated with memory types and table types.
    /// @details    Modified limits structure in "WebAssembly Release 1.0 (2019-07-20) § 2.3.4", content forward compatible, structure cannot be inherited.
    /// @see        WebAssembly Release 3.0 (Draft 2024-09-21) § 2.3.12
    struct limits
    {
        ::parser::wasm::standard::wasm1::type::wasm_u64 min{};
        ::parser::wasm::standard::wasm1::type::wasm_u64 max{};
        bool present_max{};
    };

}  // namespace parser::wasm::standard::wasm3::type
