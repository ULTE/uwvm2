/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       WebAssembly Release 1.0 (2019-07-20)
 * @details     antecedent dependency: null
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-09
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
import utils.io;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.standard.wasm1.section;
import parser.wasm.standard.wasm1.opcode;
import parser.wasm.binfmt.binfmt_ver1;
import :def;
import :type_section;
#else
// std
# include <cstddef>
# include <cstdint>
# include <concepts>
# include <type_traits>
# include <utility>
# include <memory>
// macro
# include <utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/tuple.h>
# include <utils/io/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <parser/wasm/standard/wasm1/section/impl.h>
# include <parser/wasm/standard/wasm1/opcode/impl.h>
# include <parser/wasm/binfmt/binfmt_ver1/impl.h>
# include "def.h"
# include "type_section.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::standard::wasm1::features
{
    struct wasm1
    {
        inline static constexpr ::fast_io::u8string_view feature_name{u8"WebAssembly Release 1.0 (2019-07-20)"};
        inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

        using value_type = ::parser::wasm::concepts::operation::type_replacer<::parser::wasm::concepts::operation::root_of_replacement,
                                                                              ::parser::wasm::standard::wasm1::type::value_type>;
        using type_prefix = ::parser::wasm::concepts::operation::type_replacer<::parser::wasm::concepts::operation::root_of_replacement,
                                                                              ::parser::wasm::standard::wasm1::type::function_type_prefix>;

        template <::parser::wasm::concepts::wasm_feature... Fs>
        using binfmt_ver1_section_type = ::fast_io::tuple<::parser::wasm::standard::wasm1::features::type_section_storage_t<Fs...>
                                                          /// @todo
                                                          >;
    };

    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr auto define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type_t<wasm1>, ::fast_io::tuple<Fs...>) noexcept
    {
        return ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_handle_func<Fs...>;
    }

    static_assert(::parser::wasm::concepts::wasm_feature<wasm1>);
    static_assert(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<wasm1>);
    static_assert(::parser::wasm::binfmt::ver1::has_binfmt_ver1_extensible_section_define<wasm1>);
    static_assert(::parser::wasm::standard::wasm1::features::has_value_type<wasm1>);
    static_assert(::parser::wasm::standard::wasm1::features::has_type_prefix<wasm1>);
}  // namespace parser::wasm::standard::wasm1::features
