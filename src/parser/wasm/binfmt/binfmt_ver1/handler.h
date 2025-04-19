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

#if !(__cpp_structured_bindings >= 202411L)
# error "UWVM requires at least C++26 standard compiler."
#endif

#ifdef UWVM_MODULE
import fast_io;
import utils.io;
import utils.ansies;
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.standard.wasm1.section;
import parser.wasm.binfmt.base;
import :section;
import :def;
import :custom_section;
#else
// std
# include <cstddef>
# include <cstdint>
# include <concepts>
# include <type_traits>
# include <utility>
# include <vector>
# include <algorithm>
# include <memory>
// macro
# include <utils/macro/push_macros.h>
# include <utils/ansies/ansi_push_macro.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/string.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/vector.h>
# include <fast_io_dsal/array.h>
# include <fast_io_dsal/tuple.h>
# include <utils/io/impl.h>
# include <utils/ansies/impl.h>
# include <parser/wasm/base/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <parser/wasm/standard/wasm1/section/impl.h>
# include <parser/wasm/binfmt/base/impl.h>
# include "section.h"
# include "def.h"
# include "custom_section.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::binfmt::ver1
{
    template <typename Sec, typename... Fs>
    concept has_handle_binfmt_ver1_extensible_section_define =
        requires(::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec>> ref,
                 ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_begin,
                 ::std::byte const* section_end) {
            { handle_binfmt_ver1_extensible_section_define(ref, module_storage, section_begin, section_end) };
        };

    /// @see WebAssembly Release 1.0 (2019-07-20) § 5.5.2
    template <typename Ty>
    concept has_section_id_define =
        requires { requires std::same_as<std::remove_cvref_t<decltype(Ty::section_id)>, ::parser::wasm::standard::wasm1::type::wasm_u32>; };

    template <typename Ty, typename... Fs>
    concept has_section_id_and_handle_binfmt_ver1_extensible_section_define =
        has_handle_binfmt_ver1_extensible_section_define<Ty, Fs...> && has_section_id_define<Ty>;

    template <typename... Ty>
    inline consteval void check_extensible_section_is_series() noexcept
    {
        ::std::vector<::parser::wasm::standard::wasm1::type::wasm_u32> vec{};
        [&vec]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
        { ((vec.push_back(Ty...[I] ::section_id)), ...); }(::std::make_index_sequence<sizeof...(Ty)>{});
        ::std::ranges::sort(vec);
        ::parser::wasm::standard::wasm1::type::wasm_u32 counter{1};
        for(auto i: vec)
        {
            if(i != counter++) { ::fast_io::fast_terminate(); }
        }
    }

#if 1
    namespace details
    {
        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline constexpr void handle_all_binfmt_ver1_extensible_section_impl(bool&,
                                                                             ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>&,
                                                                             ::parser::wasm::standard::wasm1::type::wasm_u32,
                                                                             ::std::byte const*,
                                                                             ::std::byte const*) noexcept
        {
            // do nothing
        }

        /// @throw ::fast_io::error
        template <typename SecCurr, typename... Secs, ::parser::wasm::concepts::wasm_feature... Fs>
        inline void
            handle_all_binfmt_ver1_extensible_section_impl(bool& success,
                                                           ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                                                           ::parser::wasm::standard::wasm1::type::wasm_u32 section_id,
                                                           ::std::byte const* section_begin,
                                                           ::std::byte const* section_end) UWVM_THROWS
        {
            static_assert(has_section_id_and_handle_binfmt_ver1_extensible_section_define<SecCurr, Fs...>);

            /// @details    This can be optimized to jump tables, which is fine under llvm, not gcc or msvc.
            /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\handle_all_binfmt_ver1_extensible_section_test_jmp_table.cc

            if(section_id == SecCurr::section_id)
            {
                handle_binfmt_ver1_extensible_section_define(::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<SecCurr>>,
                                                             module_storage,
                                                             section_begin,
                                                             section_end);
                success = true;
            }
            else
            {
                if constexpr(sizeof...(Secs) != 0)
                {
                    handle_all_binfmt_ver1_extensible_section_impl<Secs...>(success, module_storage, section_id, section_begin, section_end);
                }
            }
        }

    }  // namespace details

    /// @brief      handle all binfmt ver1 extensible section
    /// @throws     ::fast_io::error
    /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\handle_all_binfmt_ver1_extensible_section.cc
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline void handle_all_binfmt_ver1_extensible_section(::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
                                                          [[maybe_unused]] ::std::byte const* module_begin,
                                                          ::parser::wasm::standard::wasm1::type::wasm_u32 section_id,
                                                          ::std::byte const* section_begin,
                                                          ::std::byte const* section_end) UWVM_THROWS
    {
        auto [... secs]{module_storage.sections};
        check_extensible_section_is_series<decltype(secs)...>();

        bool success{};

        // llvm can gen jump table here
        if(section_id == 0) 
        {
            ::parser::wasm::binfmt::ver1::handle_binfmt_ver1_custom_section(module_storage, section_begin, section_end);
            success = true;
        }
        else { details::handle_all_binfmt_ver1_extensible_section_impl<decltype(secs)...>(success, module_storage, section_id, section_begin, section_end); }
        
        if(!success) [[unlikely]]
        {
# ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_begin - module_begin),
                                u8") Unknown WebAssembly Section ID: \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                section_id,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
# endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }
    }

#else
    /// @brief          handle all binfmt ver1 extensible section
    /// @deprecated     Twice lambda, compiler inconvenient optimization
    /// @throws         ::fast_io::error
    /// @see            test\non-platform-specific\0001.parser\0002.binfmt1\handle_all_binfmt_ver1_extensible_section.cc
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline void handle_all_binfmt_ver1_extensible_section(::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
                                                          [[maybe_unused]] ::std::byte const* module_begin,
                                                          ::parser::wasm::standard::wasm1::type::wasm_u32 section_id,
                                                          ::std::byte const* section_begin,
                                                          ::std::byte const* section_end) UWVM_THROWS
    {
        auto [... secs]{module_storage.sections};
        check_extensible_section_is_series(module_storage.sections);
        constexpr auto Secs_sz{sizeof...(secs)};

        bool finish{};

        [&finish, &module_storage, section_id, section_begin, section_end]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
        {
            ((
                 [&finish, &module_storage, section_id, section_begin, section_end]<typename SecCurr>() constexpr noexcept
                 {
                     static_assert(has_section_id_and_handle_binfmt_ver1_extensible_section_define<SecCurr, Fs...>);
                     if(section_id == SecCurr::section_id)
                     {
                         if(finish) { return; }
                         handle_binfmt_ver1_extensible_section_define(::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<SecCurr>>,
                                                                      module_storage,
                                                                      section_begin,
                                                                      section_end);
                         finish = true;
                     }
                 }.template operator()<decltype(secs...[I])>()),
             ...);
        }(::std::make_index_sequence<Secs_sz>{});

        if(!finish) [[unlikely]]
        {
# ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(section_begin - module_begin),
                                u8") Unknown WebAssembly Section ID: \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                section_id,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
# endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }
    }
#endif

    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr wasm_binfmt_ver1_module_extensible_storage_t<Fs...> wasm_binfmt_ver1_handle_func(::fast_io::tuple<Fs...>,
                                                                                                      ::std::byte const* const module_begin,
                                                                                                      ::std::byte const* const module_end) UWVM_THROWS
    {
        using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

        wasm_binfmt_ver1_module_extensible_storage_t<Fs...> ret{};

        ret.module_span.module_begin = module_begin;
        ret.module_span.module_end = module_end;

        ::std::byte const* module_curr{module_begin};

        // 00 61 73 6D 01 00 00 00 01 7D ...
        // ^^ module_curr

        if(static_cast<::std::size_t>(module_end - module_curr) < 8U * sizeof(char8_t) || !::parser::wasm::binfmt::is_wasm_file_unchecked(module_curr))
            [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(module_curr - module_begin),
                                u8") Illegal WebAssembly file format.",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        // uncheck binfmt version, user-selected, or auto-detect

        module_curr += 8U * sizeof(char8_t);

        // 00 61 73 6D 01 00 00 00 01 7D ...
        //                         ^^ module_curr

        if(static_cast<::std::size_t>(module_end - module_curr) < 2U * sizeof(char8_t)) [[unlikely]]
        {
            // No need to check module_curr > module_end, always false
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"(offset=",
                                ::fast_io::mnp::addrvw(module_curr - module_begin),
                                u8") No WebAssembly sections found.",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
#endif
            ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        for(;;)
        {
            // get section type
            ::parser::wasm::standard::wasm1::type::wasm_byte sec_id{};
            ::fast_io::freestanding::my_memcpy(::std::addressof(sec_id), module_curr, sizeof(::parser::wasm::standard::wasm1::type::wasm_byte));

            // get section length
            ++module_curr;
            // 00 61 73 6D 01 00 00 00 01 7D ...
            //                            ^^ module_curr

            ::parser::wasm::standard::wasm1::type::wasm_u32 sec_len{};
            auto const [sec_len_next, sec_len_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(module_curr),
                                                                            reinterpret_cast<char8_t_const_may_alias_ptr>(module_end),
                                                                            ::fast_io::mnp::leb128_get(sec_len))};
            if(sec_len_err != ::fast_io::parse_code::ok) [[unlikely]]
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(module_curr - module_begin),
                                    u8") Invalid Section Length.",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                ::parser::wasm::base::throw_wasm_parse_code(sec_len_err);
            }

            // set curr to next
            module_curr = reinterpret_cast<::std::byte const*>(sec_len_next);

            // check length
            if(static_cast<::std::size_t>(module_end - module_curr) < sec_len) [[unlikely]]
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(module_curr - module_begin),
                                    u8") Invalid Section Length: \"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                    sec_len,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"\"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            auto const sec_end{module_curr + sec_len};

            handle_all_binfmt_ver1_extensible_section(ret, module_begin, sec_id, module_curr, sec_end);

            module_curr = sec_end;

            // check next section
            if(auto const dif{static_cast<::std::size_t>(module_end - module_curr)}; dif == 0U) 
            { 
                // there are no sections remaining
                break; 
            }
            else if(dif < 2U) [[unlikely]]
            {
                // No need to check module_curr > module_end, always false
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(module_curr - module_begin),
                                    u8") Unable to read leb128, not enough space left.",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                ::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }
        }

        return ret;
    }
}  // namespace parser::wasm::binfmt::ver1
