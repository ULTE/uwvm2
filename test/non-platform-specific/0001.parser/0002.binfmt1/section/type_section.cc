/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @details     This example is used to test whether a jump table can be generated instead of a continuous if judgment
 * @version     2.0.0
 * @date        2025-04-13
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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <memory>

#include <utils/macro/push_macros.h>

#ifdef UWVM_MODULE
import fast_io;
import parser.wasm.base;
import uwvm.wasm.storage;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.binfmt.binfmt_ver1;
import parser.wasm.standard.wasm1.features;
#else
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/tuple.h>
# include <utils/io/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <parser/wasm/binfmt/binfmt_ver1/impl.h>
# include <parser/wasm/standard/wasm1/features/binfmt.h>
#endif

enum class vt1 : ::parser::wasm::standard::wasm1::type::wasm_u32
{

};

enum class vt2 : ::parser::wasm::standard::wasm1::type::wasm_u32
{

};

enum class ftp1 : ::parser::wasm::standard::wasm1::type::wasm_byte
{

};

enum class ftp2 : ::parser::wasm::standard::wasm1::type::wasm_byte
{

};

struct F1
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"F1"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    using value_type = ::parser::wasm::concepts::operation::type_replacer<::parser::wasm::concepts::operation::root_of_replacement, vt1>;
    using type_prefix = ::parser::wasm::concepts::operation::type_replacer<::parser::wasm::concepts::operation::root_of_replacement, ftp1>;
};

struct F2
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"F2"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    using type_prefix = ::parser::wasm::concepts::operation::type_replacer<ftp1, ftp2>;
    inline static constexpr bool allow_multi_result_vector{false};
};

struct F3
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"F2"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    using value_type = ::parser::wasm::concepts::operation::type_replacer<vt1, vt2>;
    inline static constexpr bool allow_multi_result_vector{true};
};

int main()
{
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_value_type_t<F1>, vt1>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_value_type_t<F1, F2>, vt1>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_value_type_t<F1, F3>, vt2>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_value_type_t<F1, F2, F3>, vt2>);

    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_type_prefix_t<F1>, ftp1>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_type_prefix_t<F1, F2>, ftp2>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_type_prefix_t<F1, F3>, ftp1>);
    static_assert(::std::same_as<::parser::wasm::standard::wasm1::features::final_type_prefix_t<F1, F2, F3>, ftp2>);

    static_assert(::parser::wasm::standard::wasm1::features::allow_multi_result_vector<F1>() == false);
    static_assert(::parser::wasm::standard::wasm1::features::allow_multi_result_vector<F1, F2>() == false);
    static_assert(::parser::wasm::standard::wasm1::features::allow_multi_result_vector<F1, F3>() == true);
    static_assert(::parser::wasm::standard::wasm1::features::allow_multi_result_vector<F1, F2, F3>() == true);
}

