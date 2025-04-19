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
import parser.wasm.standard.wasm1.type;
#else
// std
# include <cstdint>
# include <cstddef>
# include <type_traits>
# include <memory>
// import
# include <fast_io.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::binfmt
{
    struct module_span_t
    {
        ::std::byte const* module_begin{};
        ::std::byte const* module_end{};
    };

    inline constexpr bool is_wasm_file_unchecked(::std::byte const* module_curr) noexcept
    {
        return ::fast_io::freestanding::my_memcmp(module_curr, u8"\0asm", 4u * sizeof(char8_t)) == 0;
    }

    inline constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 detect_wasm_binfmt_version_unchecked(::std::byte const* module_curr) noexcept
    {
        ::parser::wasm::standard::wasm1::type::wasm_u32 temp{};
        ::fast_io::freestanding::my_memcpy(::std::addressof(temp), module_curr, sizeof(::parser::wasm::standard::wasm1::type::wasm_u32));
        return ::fast_io::little_endian(temp);
    }

    /// @brief      detect wasm binfmt version
    /// @return     0 : error, other : binfmt version
    inline constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 detect_wasm_binfmt_version(::std::byte const* const module_begin,
                                                                                                ::std::byte const* const module_end) noexcept
    {
        ::std::byte const* module_curr{module_begin};

        if(static_cast<::std::size_t>(module_end - module_curr) < 8U * sizeof(char8_t) || !::parser::wasm::binfmt::is_wasm_file_unchecked(module_curr))
            [[unlikely]]
        {
            return 0;
        }

        module_curr += 4U * sizeof(char8_t);

        // 00 61 73 6D 01 00 00 00 ...
        //             ^^ module_curr

        auto binfmt_ver{detect_wasm_binfmt_version_unchecked(module_curr)};

        return binfmt_ver;
    }
}  // namespace parser::wasm::binfmt
