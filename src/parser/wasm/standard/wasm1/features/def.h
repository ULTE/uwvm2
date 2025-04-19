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
 * @date        2025-04-16
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
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::standard::wasm1::features
{
    /// @brief      has value type
    /// @details
    ///             ```cpp
    ///             struct F
    ///             {
    ///                 using value_type = type_replacer<root_of_replacement, value_type>;
    ///             };
    ///             ```
    /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\section\type_section.cc
    template <typename FeatureType>
    concept has_value_type = requires {
        typename FeatureType::value_type;
        ::parser::wasm::concepts::operation::details::check_is_type_replacer<::parser::wasm::concepts::operation::type_replacer,
                                                                             typename FeatureType::value_type>;
    };

    template <typename FeatureType>
    inline consteval auto get_value_type() noexcept
    {
        if constexpr(has_value_type<FeatureType>) { return typename FeatureType::value_type{}; }
        else { return ::parser::wasm::concepts::operation::irreplaceable_t{}; }
    }

    template <::parser::wasm::concepts::wasm_feature... Fs>
    using final_value_type_t = ::parser::wasm::concepts::operation::replacement_structure_t<decltype(get_value_type<Fs>())...>;

    template <::parser::wasm::concepts::wasm_feature... Fs>
    struct vec_value_type
    {
        static_assert(::std::is_enum_v<final_value_type_t<Fs...>>);
        static_assert(::std::same_as<::std::underlying_type_t<final_value_type_t<Fs...>>, ::parser::wasm::standard::wasm1::type::wasm_byte>);

        final_value_type_t<Fs...> const* begin{};
        final_value_type_t<Fs...> const* end{};
    };

    template <::parser::wasm::concepts::wasm_feature... Fs>
    using final_result_type = vec_value_type<Fs...>;

    template <::parser::wasm::concepts::wasm_feature... Fs>
    struct final_function_type
    {
        final_result_type<Fs...> parameter{};
        final_result_type<Fs...> result{};
    };

    /// @brief      has type prefie
    /// @details
    ///             ```cpp
    ///             struct F
    ///             {
    ///                 using type_prefix = type_replacer<root_of_replacement, type_prefix>;
    ///             };
    ///             ```
    /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\section\type_section.cc
    template <typename FeatureType>
    concept has_type_prefix = requires {
        typename FeatureType::type_prefix;
        ::parser::wasm::concepts::operation::details::check_is_type_replacer<::parser::wasm::concepts::operation::type_replacer,
                                                                             typename FeatureType::type_prefix>;
    };

    template <typename FeatureType>
    inline consteval auto get_type_prefix() noexcept
    {
        if constexpr(has_type_prefix<FeatureType>) { return typename FeatureType::type_prefix{}; }
        else { return ::parser::wasm::concepts::operation::irreplaceable_t{}; }
    }

    template <::parser::wasm::concepts::wasm_feature... Fs>
    using final_type_prefix_t = ::parser::wasm::concepts::operation::replacement_structure_t<decltype(get_type_prefix<Fs>())...>;

    /// @brief      allow multi value
    /// @details    In the current version of WebAssembly, the length of the result type vector of a valid function type may be
    ///             at most 1. This restriction may be removed in future versions.
    ///             
    ///             Define this to eliminate checking the length of the result.
    ///
    ///             ```cpp
    ///             struct F
    ///             {
    ///                 inline static constexpr bool allow_multi_result_vector{true};
    ///             };
    ///             ```
    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.3.3
    /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\section\type_section.cc
    template <typename FsCurr>
    concept has_allow_multi_result_vector = requires { requires ::std::same_as<::std::remove_cvref_t<decltype(FsCurr::allow_multi_result_vector)>, bool>; };

    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline consteval bool allow_multi_result_vector() noexcept
    {
        return []<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
        {
            return ((
                        []<typename FsCurr>() constexpr noexcept -> bool
                                                                    {
                                                                        // check irreplaceable
                                                                        if constexpr(has_allow_multi_result_vector<FsCurr>)
                                                                        {
                                                                            constexpr bool tallow{FsCurr::allow_multi_result_vector};
                                                                            return tallow;
                                                                        }
                                                                        else { return false; }
                                                                    }.template operator()<Fs...[I]>()) ||
                    ...);
        }(::std::make_index_sequence<sizeof...(Fs)>{});
    }
}  // namespace parser::wasm::standard::wasm1::features

UWVM_MODULE_EXPORT namespace fast_io::freestanding
{
    template <::parser::wasm::concepts::wasm_feature... Fs>
    struct is_zero_default_constructible<::parser::wasm::standard::wasm1::features::final_function_type<Fs...>>
    {
        inline static constexpr bool value = true;
    };
}
