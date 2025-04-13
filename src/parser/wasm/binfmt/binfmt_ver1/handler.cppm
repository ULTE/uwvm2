﻿/********************************************************
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

module;

#include <cstddef>
#include <cstdint>
#include <concepts>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory>

#include <utils/macro/push_macros.h>
#include <utils/ansies/ansi_push_macro.h>

export module parser.wasm.binfmt.binfmt_ver1:handler;

import fast_io;
import utils.io;
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.standard.wasm1.section;
import parser.wasm.binfmt.base;
import :section;
import :def;

export namespace parser::wasm::binfmt::ver1
{
    [[noreturn]] inline void throw_wasm_parse_code([[maybe_unused]] ::fast_io::parse_code code)
    {
#ifdef UWVM_TERMINATE_IMME_WHEN_PARSE
        ::fast_io::fast_terminate();
#else
# ifdef __cpp_exceptions
#  if defined(_MSC_VER) && (!defined(_HAS_EXCEPTIONS) || _HAS_EXCEPTIONS == 0)
        ::fast_io::fast_terminate();
#  else
        throw ::fast_io::error{::fast_io::parse_domain_value, static_cast<::std::size_t>(static_cast<char8_t>(code))};
#  endif
# else
        ::fast_io::fast_terminate();
# endif
#endif
    }

    template <typename Sec, typename... Fs>
    concept has_handle_binfmt_ver1_extensible_section_define =
        requires(::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec>> ref,
                 ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_begin,
                 ::std::byte const* section_end) {
            { handle_binfmt_ver1_extensible_section_define(ref, module_storage, section_begin, section_end) } -> ::std::same_as<bool>;
        };

    /// @see WebAssembly Release 1.0 (2019-07-20) § 5.5.2
    template <typename Ty>
    concept has_section_id_define =
        requires { ::std::same_as<decltype(::std::remove_cvref_t<Ty>::section_id), ::parser::wasm::standard::wasm1::type::wasm_u32>; };

    template <typename Ty, typename... Fs>
    concept has_section_id_and_handle_binfmt_ver1_extensible_section_define =
        has_handle_binfmt_ver1_extensible_section_define<Ty, Fs...> && has_section_id_define<Ty>;

    template <typename... Ty>
    inline consteval void check_extensible_section_is_series(::fast_io::tuple<Ty...>) noexcept
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

    /// @brief      handle all binfmt ver1 extensible section
    /// @throws     ::fast_io::error
    /// @see        test\non-platform-specific\0001.parser\0002.binfmt1\handle_all_binfmt_ver1_extensible_section.cc
    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr void
        handle_all_binfmt_ver1_extensible_section(::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
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
                         finish = handle_binfmt_ver1_extensible_section_define(::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<SecCurr>>,
                                                                               module_storage,
                                                                               section_begin,
                                                                               section_end);
                     }
                 }.template operator()<decltype(secs...[I])>()),
             ...);
        }(::std::make_index_sequence<Secs_sz>{});

        if(!finish) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::u8err,
                                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                ::fast_io::mnp::addrvw(section_begin - module_begin),
                                u8") Unknown WebAssembly Section ID: \"",
                                UWVM_AES_U8_CYAN,
                                section_id,
                                UWVM_AES_U8_WHITE u8"\"" UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
            throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }
    }

    inline constexpr bool is_wasm_file_unchecked(::std::byte const* module_curr) noexcept
    {
        return ::fast_io::freestanding::my_memcmp(module_curr, u8"\0asm", 4u * sizeof(char8_t)) == 0;
    }

    inline constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 detect_wasm_version_unchecked(::std::byte const* module_curr) noexcept
    {
        ::parser::wasm::standard::wasm1::type::wasm_u32 temp{};
        ::fast_io::freestanding::my_memcpy(::std::addressof(temp), module_curr, sizeof(::parser::wasm::standard::wasm1::type::wasm_u32));
        return ::fast_io::little_endian(temp);
    }

    template <::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr wasm_binfmt_ver1_module_extensible_storage_t<Fs...>
        wasm_binfmt_ver1_handle_func(::fast_io::tuple<Fs...>, ::std::byte const* const module_begin, ::std::byte const* const module_end) UWVM_THROWS
    {
        using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

        wasm_binfmt_ver1_module_extensible_storage_t<Fs...> ret{};

        ret.module_span.module_begin = module_begin;
        ret.module_span.module_end = module_end;

        // 00 61 73 6D 01 00 00 00 ...
        // ^^ module_curr

        ::std::byte const* module_curr{module_begin};

        if(static_cast<::std::size_t>(module_end - module_curr) < 8U * sizeof(char8_t) || !is_wasm_file_unchecked(module_curr)) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::u8err,
                                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                ::fast_io::mnp::addrvw(module_curr - module_begin),
                                u8") Illegal WebAssembly file format." UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
            throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        module_curr += 4U * sizeof(char8_t);

        // 00 61 73 6D 01 00 00 00 ...
        //             ^^ module_curr

        auto binfmt_ver{detect_wasm_version_unchecked(module_curr)};

        if(binfmt_ver != 1U) [[unlikely]]
        {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::u8err,
                                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                ::fast_io::mnp::addrvw(module_curr - module_begin),
                                u8") The binary format version of WebAssembly is not 1." UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
            throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        module_curr += 4U * sizeof(char8_t);

        // 00 61 73 6D 01 00 00 00 01 7D ...
        //                         ^^ module_curr

        if(static_cast<::std::size_t>(module_end - module_curr) < 2U * sizeof(char8_t)) [[unlikely]]
        {
            // No need to check module_curr > module_end, always false
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
            ::fast_io::io::perr(::utils::u8err,
                                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                ::fast_io::mnp::addrvw(module_curr - module_begin),
                                u8") No WebAssembly sections found." UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
            throw_wasm_parse_code(::fast_io::parse_code::invalid);
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
            if(sec_len_err != ::fast_io::parse_code::ok) [[unlikely]] { throw_wasm_parse_code(sec_len_err); }

            // set curr to next
            module_curr = reinterpret_cast<::std::byte const*>(sec_len_next);

            // check length
            if(static_cast<::std::size_t>(module_end - module_curr) < sec_len) [[unlikely]]
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::u8err,
                                    UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                    ::fast_io::mnp::addrvw(module_curr - module_begin),
                                    u8") Invalid Section Length: \"",
                                    UWVM_AES_U8_CYAN,
                                    sec_len,
                                    UWVM_AES_U8_WHITE u8"\"" UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
                throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            auto const sec_end{module_curr + sec_len};

            handle_all_binfmt_ver1_extensible_section(ret, module_begin, sec_id, module_curr, sec_end);

            module_curr = sec_end;

            // check next section
            if(auto const dif{static_cast<::std::size_t>(module_end - module_curr)}; dif == 0U) { break; }
            else if(dif < 2U) [[unlikely]]
            {
                // No need to check module_curr > module_end, always false
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::u8err,
                                    UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                    ::fast_io::mnp::addrvw(module_curr - module_begin),
                                    u8") Unable to read leb128, not enough space left." UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
                throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }
        }

        return ret;
    }
}  // namespace parser::wasm::binfmt::ver1
