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
import utils.ansies;
# ifdef UWVM_TIMER
import utils.debug;
# endif
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.standard.wasm1.section;
import parser.wasm.standard.wasm1.opcode;
import parser.wasm.binfmt.binfmt_ver1;
import :def;
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
# include <utils/ansies/ansi_push_macro.h>
// import
# include <fast_io.h>
# include <utils/io/impl.h>
# include <utils/ansies/impl.h>
# ifdef UWVM_TIMER
#  include <utils/debug/impl.h>
# endif
# include <parser/wasm/base/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <parser/wasm/standard/wasm1/section/impl.h>
# include <parser/wasm/standard/wasm1/opcode/impl.h>
# include <parser/wasm/binfmt/binfmt_ver1/impl.h>
# include "def.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::standard::wasm1::features
{
    template <::parser::wasm::concepts::wasm_feature... Fs>
    struct type_section_storage_t
    {
        inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{1};

        ::parser::wasm::standard::wasm1::section::section_span_view sec_span{};

        ::fast_io::vector<::parser::wasm::standard::wasm1::features::final_function_type<Fs...>> types{};
    };

    /// @brief Define functions for checking value_type to provide extensibility
    template <typename... Fs>
    concept has_check_value_type = requires(::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                            ::parser::wasm::standard::wasm1::features::final_value_type_t<Fs...> value_type) {
        { define_check_value_type(sec_adl, value_type) } -> ::std::same_as<bool>;
    };

    /// @brief Define functions for value_type against wasm1 for checking value_type
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr bool define_check_value_type([[maybe_unused]] ::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                                  ::parser::wasm::standard::wasm1::type::value_type value_type) noexcept
    {
        switch(value_type)
        {
            case ::parser::wasm::standard::wasm1::type::value_type::i32: [[fallthrough]];
            case ::parser::wasm::standard::wasm1::type::value_type::i64: [[fallthrough]];
            case ::parser::wasm::standard::wasm1::type::value_type::f32: [[fallthrough]];
            case ::parser::wasm::standard::wasm1::type::value_type::f64: return true;
            default: return false;
        }
    }

    /// @brief Define functions for checking valuetype to type_prefix extensibility
    template <typename... Fs>
    concept has_type_prefix_handler = requires(::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                               ::parser::wasm::standard::wasm1::features::final_type_prefix_t<Fs...> preifx,
                                               ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                                               ::std::byte const* const section_curr,
                                               ::std::byte const* const section_end) {
        { define_type_prefix_handler(sec_adl, preifx, module_storage, section_curr, section_end) } -> ::std::same_as<::std::byte const*>;
    };

    /// @brief Define type_prefix for wasm1 Functions for checking type_prefix
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline ::std::byte const* define_type_prefix_handler(::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                                         ::parser::wasm::standard::wasm1::type::function_type_prefix prefix,
                                                         ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
                                                         ::std::byte const* section_curr,
                                                         ::std::byte const* const section_end) UWVM_THROWS
    {
        using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;
        using value_type_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::parser::wasm::standard::wasm1::features::final_value_type_t<Fs...> const*;

        // ... 60 ?? ?? ...
        //        ^^ section_curr
        switch(prefix)
        {
            case ::parser::wasm::standard::wasm1::type::function_type_prefix::functype:
            {
                ::parser::wasm::standard::wasm1::features::final_function_type<Fs...> ft{};

                // For safety, add parentheses to indicate the scope
                // parameter
                {
                    ::parser::wasm::standard::wasm1::type::wasm_u32 para_len{};
                    auto const [next_para_len, err_para_len]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                                      reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                                      ::fast_io::mnp::leb128_get(para_len))};
                    if(err_para_len != ::fast_io::parse_code::ok) [[unlikely]]
                    {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                        ::fast_io::io::perr(::utils::debug_output,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                            u8"uwvm: ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                            u8"[error] ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"(offset=",
                                            ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                            u8") Invalid Parameter Length.",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                            u8"\n\n");
#endif
                        ::parser::wasm::base::throw_wasm_parse_code(err_para_len);
                    }

                    section_curr = reinterpret_cast<::std::byte const*>(next_para_len);

                    // ... 60 length ... length ... ...
                    //               ^^ section_curr
                    // If it's a null return value, there's at least one more parameter, so add 1u
                    if(static_cast<::std::size_t>(section_end - section_curr) < para_len + 1u) [[unlikely]]
                    {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                        ::fast_io::io::perr(::utils::debug_output,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                            u8"uwvm: ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                            u8"[error] ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"(offset=",
                                            ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                            u8") Invalid Parameter Length: \"",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                            para_len,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"\"",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                            u8"\n\n");
#endif
                        ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                    }

                    // set parameters
                    ft.parameter.begin = reinterpret_cast<value_type_const_may_alias_ptr>(section_curr);
                    section_curr += para_len;
                    // ... 60 length ... length ... ...
                    //                   ^^ section_curr
                    ft.parameter.end = reinterpret_cast<value_type_const_may_alias_ptr>(section_curr);

                    // check handler
                    static_assert(has_check_value_type<Fs...>);
                    // check parameters
                    for(auto parameter_curr{ft.parameter.begin}; parameter_curr != ft.parameter.end; ++parameter_curr)
                    {
                        if(!define_check_value_type(sec_adl, *parameter_curr)) [[unlikely]]
                        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                            ::fast_io::io::perr(::utils::debug_output,
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                                u8"uwvm: ",
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                                u8"[error] ",
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                                u8"(offset=",
                                                ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                                u8") Invalid Value Type: \"",
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                                ::fast_io::mnp::hex0x<true>(
                                                    static_cast<::std::underlying_type_t<::parser::wasm::standard::wasm1::features::final_value_type_t<Fs...>>>(
                                                        *parameter_curr)),
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                                u8"\"",
                                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                                u8"\n\n");
#endif
                        }
                    }
                }

                // result
                {
                    ::parser::wasm::standard::wasm1::type::wasm_u32 result_len{};
                    auto const [next_result_len, err_result_len]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                                          reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                                          ::fast_io::mnp::leb128_get(result_len))};
                    if(err_result_len != ::fast_io::parse_code::ok) [[unlikely]]
                    {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                        ::fast_io::io::perr(::utils::debug_output,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                            u8"uwvm: ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                            u8"[error] ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"(offset=",
                                            ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                            u8") Invalid Result Length.",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                            u8"\n\n");
#endif
                        ::parser::wasm::base::throw_wasm_parse_code(err_result_len);
                    }

                    section_curr = reinterpret_cast<::std::byte const*>(next_result_len);
                    // ... 60 length ... length ... ...
                    //                          ^^ section_curr

                    /// @details    In the current version of WebAssembly, the length of the result type vector of a valid function type may be
                    ///             at most 1. This restriction may be removed in future versions.
                    /// @see        WebAssembly Release 1.0 (2019-07-20) § 2.3.3
                    constexpr bool allow_multi_value{::parser::wasm::standard::wasm1::features::allow_multi_result_vector<Fs...>()};
                    if constexpr(!allow_multi_value)
                    {
                        if(result_len > 1) [[unlikely]]
                        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                            ::fast_io::io::perr(
                                ::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                u8") In the WebAssembly Release 1.0 (2019-07-20), the length of the result type vector of a valid function type may be at most 1. This restriction may be removed in future versions.",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
                            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                        }
                    }

                    if(static_cast<::std::size_t>(section_end - section_curr) < result_len) [[unlikely]]
                    {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                        ::fast_io::io::perr(::utils::debug_output,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                            u8"uwvm: ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                            u8"[error] ",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"(offset=",
                                            ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                            u8") Invalid Result Length: \"",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                            result_len,
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                            u8"\"",
                                            ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                            u8"\n\n");
#endif
                        ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                    }

                    // set parameters
                    ft.result.begin = reinterpret_cast<value_type_const_may_alias_ptr>(section_curr);
                    section_curr += result_len;
                    // ... 60 length ... length ... ...
                    //                              ^^ section_curr
                    ft.result.end = reinterpret_cast<value_type_const_may_alias_ptr>(section_curr);

                    // check results
                    for(auto result_curr{ft.result.begin}; result_curr != ft.result.end; ++result_curr)
                    {
                        if(!define_check_value_type(sec_adl, *result_curr)) [[unlikely]]
                        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                            ::fast_io::io::perr(
                                ::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                u8") Invalid Value Type: \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                ::fast_io::mnp::hex0x<true>(
                                    static_cast<::std::underlying_type_t<::parser::wasm::standard::wasm1::features::final_value_type_t<Fs...>>>(*result_curr)),
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
                        }
                    }
                }

                // push back
                auto& typesec{::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};
                typesec.types.push_back_unchecked(::std::move(ft));

                break;
            }
            default: [[unlikely]] {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                    ::fast_io::io::perr(
                        ::utils::debug_output,
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                        u8"uwvm: ",
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                        u8"[error] ",
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                        u8"(offset=",
                        ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                        u8") Invalid Type Prefix: \"",
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                        ::fast_io::mnp::hex0x<true>(static_cast<::std::underlying_type_t<::parser::wasm::standard::wasm1::type::function_type_prefix>>(prefix)),
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                        u8"\"",
                        ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                        u8"\n\n");
#endif
                    ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }
        }
        return section_curr;
    }

    /// @brief Define the handler function for type_section
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline void handle_binfmt_ver1_extensible_section_define(::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                                             ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
                                                             ::std::byte const* const section_begin,
                                                             ::std::byte const* const section_end) UWVM_THROWS
    {
#ifdef UWVM_TIMER
        ::utils::debug::timer parsing_timer{u8"parse type section (id: 1)"};
#endif

        // get type_section_storage_t from storages
        auto& typesec{::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};

        // check duplicate
        if(typesec.sec_span.sec_begin) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_begin - module_storage.module_span.module_begin),
                                u8") Duplicate WebAssembly Section: \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                u8"Type",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        using wasm_byte_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::parser::wasm::standard::wasm1::type::wasm_byte const*;

        typesec.sec_span.sec_begin = reinterpret_cast<wasm_byte_const_may_alias_ptr>(section_begin);
        typesec.sec_span.sec_end = reinterpret_cast<wasm_byte_const_may_alias_ptr>(section_end);

        auto section_curr{section_begin};

        ::parser::wasm::standard::wasm1::type::wasm_u32 type_count{};

        using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

        auto const [type_count_next, type_count_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                              reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                              ::fast_io::mnp::leb128_get(type_count))};

        if(type_count_err != ::fast_io::parse_code::ok) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                u8") Invalid Type Count.",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
            ::parser::wasm::base::throw_wasm_parse_code(type_count_err);
        }

        typesec.types.reserve(type_count);

        section_curr = reinterpret_cast<::std::byte const*>(type_count_next);  // never out of bounds

        ::parser::wasm::standard::wasm1::type::wasm_u32 type_counter{};

        for(; section_curr != section_end;)
        {
            // ... 60 ?? ?? ...
            //     ^^ section_curr
            ::parser::wasm::standard::wasm1::features::final_type_prefix_t<Fs...> prefix{};
            // no necessary to check, because section_curr != section_end
            ::fast_io::freestanding::my_memcpy(::std::addressof(prefix), section_curr, sizeof(prefix));
            // set section_curr to next
            ++section_curr;
            // ... 60 ?? ?? ...
            //        ^^ section_curr
            // check has func
            static_assert(has_type_prefix_handler<Fs...>);
            // check type count
            if(++type_counter > type_count) [[unlikely]]
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                    u8") The number of types resolved does not match the actual number: \"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                    type_counter,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"\"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }
            // handle it
            section_curr = define_type_prefix_handler(sec_adl, prefix, module_storage, section_curr, section_end);
        }

        // check type counter match
        if(type_counter != type_count) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_curr - module_storage.module_span.module_begin),
                                u8") The number of types resolved \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                type_counter,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\" does not match the actual number \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_LT_GREEN),
                                type_count,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\".",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }
    }
}  // namespace parser::wasm::standard::wasm1::features
