﻿/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-27
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
#include <type_traits>

#include <utils/ansies/ansi_push_macro.h>

export module uwvm.run:run;

import fast_io;
import utils.io;
import uwvm.cmdline;
import uwvm.wasm.storage;
import uwvm.wasm.feature;
import parser.wasm.concepts;
import parser.wasm.standard;
import parser.wasm.binfmt.base;

#ifdef UWVM_TIMER
import utils.debug;
#endif

export namespace uwvm::run
{
    inline int run() noexcept
    {
        if(!::uwvm::cmdline::wasm_file_ppos) [[unlikely]]
        {
            ::fast_io::io::perr(
                ::utils::u8err,
                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"No input file.\n\n" UWVM_AES_U8_RST_ALL);
            return -1;
        }

        auto module_name{::uwvm::cmdline::wasm_file_ppos->str};

#ifdef __cpp_exceptions
        try
#endif
        {
#ifdef UWVM_TIMER
            ::utils::debug::timer parsing_timer{u8"file loader"};
#endif
            ::uwvm::wasm::storage::execute_wasm_file = ::fast_io::native_file_loader{module_name};
        }
#ifdef __cpp_exceptions
        catch(::fast_io::error e)
        {
            ::fast_io::io::perr(::utils::u8err,
                                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"Unable to open WASM file \"" UWVM_AES_U8_CYAN,
                                module_name,
                                UWVM_AES_U8_WHITE u8"\": ",
                                e,
                                UWVM_AES_U8_RST_ALL u8"\n"
# ifndef _WIN32  // Win32 automatically adds a newline (winnt and win9x)
                                u8"\n"
# endif
                            );
            return -1;
        }
#endif

        // If not specified by the user, detect it
        if(::uwvm::wasm::storage::execute_wasm_binfmt_ver == 0)
        {
            ::uwvm::wasm::storage::execute_wasm_binfmt_ver =
                ::parser::wasm::binfmt::detect_wasm_binfmt_version(reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cbegin()),
                                                                   reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cend()));
        }

        switch(::uwvm::wasm::storage::execute_wasm_binfmt_ver)
        {
            case 0:
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::u8err,
                                    UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                    ::fast_io::mnp::addrvw(nullptr),
                                    u8") Illegal WebAssembly file format." UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
                return -1;
            }
            case 1:
            {
                // set module name
                ::uwvm::wasm::storage::execute_wasm_binfmt_ver1_storage.module_name = ::fast_io::u8string_view{module_name};

                // parse wasm 1
#if defined(__cpp_exceptions) && !defined(UWVM_TERMINATE_IMME_WHEN_PARSE)
                try
#endif
                {
#ifdef UWVM_TIMER
                    ::utils::debug::timer parsing_timer{u8"parse binfmt1"};
#endif
                    ::uwvm::wasm::storage::execute_wasm_binfmt_ver1_storage =
                        ::uwvm::wasm::feature::binfmt_ver1_handler(::uwvm::wasm::feature::wasm_binfmt1_features,
                                                                   reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cbegin()),
                                                                   reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cend()));
                }
#if defined(__cpp_exceptions) && !defined(UWVM_TERMINATE_IMME_WHEN_PARSE)
                catch(::fast_io::error e)
                {
                    return -1;
                }
#endif

                /// @todo run vm

                break;
            }
            default:
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::u8err,
                                    UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"(offset=",
                                    ::fast_io::mnp::addrvw(4U * sizeof(char8_t)),
                                    u8") Unknown Binary Format Version of WebAssembly: \"" UWVM_AES_U8_CYAN,
                                    ::uwvm::wasm::storage::execute_wasm_binfmt_ver,
                                    UWVM_AES_U8_WHITE u8"\"" UWVM_AES_U8_RST_ALL u8"\n\n");
#endif
                return -1;
            }
        }

        return 0;
    }
}  // namespace uwvm::run
