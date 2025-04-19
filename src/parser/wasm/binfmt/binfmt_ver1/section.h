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
 * @date        2025-04-12
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
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
#else
// std
# include <cstddef>
# include <cstdint>
# include <concepts>
# include <type_traits>
# include <utility>
// macro
# include <utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/tuple.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::binfmt::ver1
{
    /// @brief  The method that will get the extensible section type
    /// @see    test\non-platform-specific\0001.parser\0001.concept\splice_section_storage_structure.cc
    template <typename Feature, typename... Fs>
    concept has_binfmt_ver1_extensible_section_define = ::fast_io::is_tuple<typename Feature::template binfmt_ver1_section_type<Fs...>>;

    template <typename Feature, typename... Fs>
    concept has_binfmt_ver1_section_define = ::fast_io::is_tuple<typename Feature::binfmt_ver1_section_type>;

    template <::parser::wasm::concepts::wasm_feature... Features>
    inline consteval auto splice_section_storage_structure() noexcept
    {
        if constexpr(sizeof...(Features) == 0) { return ::parser::wasm::concepts::operation::tuple_megger<>{}; }
        else
        {
            return []<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                return ((
                            []<::parser::wasm::concepts::wasm_feature FeatureCurr>() constexpr noexcept
                            {
                                if constexpr(has_binfmt_ver1_extensible_section_define<FeatureCurr, Features...>)
                                {
                                    using extensible_section_t = typename FeatureCurr::template binfmt_ver1_section_type<Features...>;
                                    return ::parser::wasm::concepts::operation::get_tuple_megger_from_tuple(extensible_section_t{});
                                }
                                else if constexpr(has_binfmt_ver1_section_define<FeatureCurr>)
                                {
                                    using section_t = typename FeatureCurr::binfmt_ver1_section_type;
                                    return ::parser::wasm::concepts::operation::get_tuple_megger_from_tuple(section_t{});
                                }
                                else
                                {
                                    static_assert(!((
                                                        requires { typename FeatureCurr::template binfmt_ver1_section_type<Features...>; } ||
                                                        requires { typename FeatureCurr::binfmt_ver1_section_type; }) &&
                                                    !has_binfmt_ver1_extensible_section_define<FeatureCurr, Features...>),
                                                  "binfmt_ver1_section_type is not tuple");
                                    return ::parser::wasm::concepts::operation::tuple_megger<>{};
                                }
                            }.template operator()<Features...[I]>()),
                        ...);
            }(::std::make_index_sequence<sizeof...(Features)>{});
        }
    }

    template <::parser::wasm::concepts::wasm_feature... Features>
    using splice_section_storage_structure_t = decltype(splice_section_storage_structure<Features...>())::Type;

    template <::parser::wasm::concepts::wasm_feature... Features>
    inline consteval auto splice_section_storage_structure_from_tuple(::fast_io::tuple<Features...>) noexcept
    {
        return splice_section_storage_structure<Features...>();
    }

}  // namespace parser::wasm::binfmt::ver1
