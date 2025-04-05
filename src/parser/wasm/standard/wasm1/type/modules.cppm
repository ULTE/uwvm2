/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-05
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

export module parser.wasm.standard.wasm1.type:modules;

import fast_io;
import :value_type;
import :value_binfmt;
import :section_type;

export namespace parser::wasm::standard::wasm1::type
{
    /// @brief      Indices
    /// @details    Definitionsarereferencedwithzero-basedindices. Eachclassofdefinitionhasitsownindexspace, asdistinguished
    ///             by the following classes.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.1
    using indices = ::parser::wasm::standard::wasm1::type::wasm_u32;

    /// @brief      Function Types
    /// @details    Function types are encoded by the byte 0x60 followed by the respective vectors of parameter and result types.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.2
    struct local_function_type
    {
        ::parser::wasm::standard::wasm1::type::function_type const* func_type{};
        ::fast_io::string_view custom_name{};

        bool is_exported{};
    };

    /// @brief      Functions
    /// @details    The funcs component of a module defines a vector of functions with the following structure.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.3
    struct local_entry
    {
        ::fast_io::u8string_view custom_name{};
        indices count{};
        ::parser::wasm::standard::wasm1::type::value_type type{};
    };

    /// @brief      Exports
    /// @details    The exports component of a module defines a set of exports that become accessible to the host environment once
    ///             the module has been instantiated.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.10
    struct export_type
    {
        ::fast_io::u8string_view export_name{};
        indices index{};
        ::parser::wasm::standard::wasm1::type::external_types kind{};
    };

    /// @brief      Expressions
    /// @details    Function bodies, initialization values for globals, and offsets of element or data segments are given as expressions,
    ///             which are sequences of instructions terminated by an end marker.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.4.6
    struct initializer_exp
    {
        union GlobalStorage
        {
            ::parser::wasm::standard::wasm1::type::wasm_i32 i32;
            ::parser::wasm::standard::wasm1::type::wasm_i64 i64;
            ::parser::wasm::standard::wasm1::type::wasm_f32 f32;
            ::parser::wasm::standard::wasm1::type::wasm_f64 f64;
        } global_storage;

        ::parser::wasm::standard::wasm1::type::op_basic_type type_opcode{};
    };

    /// @brief      Globals
    /// @details    The globals component of a module defines a vector of global variables (or globals for short)
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.6
    struct local_global_type
    {
        ::fast_io::u8string_view custom_name;
        ::parser::wasm::standard::wasm1::type::global_type type{};
        initializer_exp init{};
    };

    /// @brief      Element Segments
    /// @details    The initial contents of a table is uninitialized. The elem component of a module defines a vector of element segments
    ///             that initialize a subrange of a table, at a given offset, from a static vector of elements.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.7
    struct elem_segment_type
    {
        indices table{};
        initializer_exp offset{};
        ::fast_io::vector<indices> init{};
    };

    /// @brief      Data Segments
    /// @details    The initial contents of a memory are zero-valued bytes. The data component of a module defines a vector of data
    ///             segments that initialize a range of memory, at a given offset, with a static vector of bytes.
    /// @details    New feature
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.5.8
    struct data_segment
    {
        indices data{};
        initializer_exp offset{};
        ::parser::wasm::standard::wasm1::type::vec_byte init{};
    };

}  // namespace parser::wasm::standard::wasm1::type
