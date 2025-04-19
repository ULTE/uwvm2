/********************************************************
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

#pragma once

#ifdef UWVM_MODULE
import fast_io;
import utils.io;
import utils.ansies;
# ifdef UWVM_TIMER
import utils.debug;
# endif
import utils.madvise;
import uwvm.cmdline;
import uwvm.wasm.storage;
import uwvm.wasm.feature;
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard;
import parser.wasm.binfmt.base;
#else
// std
# include <cstddef>
# include <cstdint>
# include <type_traits>
// macro
# include <utils/ansies/ansi_push_macro.h>
// import
# include <fast_io.h>
# include <utils/io/impl.h>
# include <utils/ansies/impl.h>
# ifdef UWVM_TIMER
#  include <utils/debug/impl.h>
# endif
# include <utils/madvise/impl.h>
# include <uwvm/cmdline/impl.h>
# include <uwvm/wasm/storage/impl.h>
# include <uwvm/wasm/feature/impl.h>
# include <parser/wasm/base/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/impl.h>
# include <parser/wasm/binfmt/base/impl.h>

#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif
UWVM_MODULE_EXPORT namespace uwvm::run
{
    inline int run() noexcept
    {
        if(!::uwvm::cmdline::wasm_file_ppos) [[unlikely]]
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"No input file.\n\n",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL));
            return -2;  // The specified file is not available or cannot be opened
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
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Unable to open WASM file \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                module_name,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\": ",
                                e,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n"
# ifndef _WIN32  // Win32 automatically adds a newline (winnt and win9x)
                                u8"\n"
# endif
            );
            return -2;  // The specified file is not available or cannot be opened
        }
#endif

        // Instructs to read the file all the way into memory
        ::utils::madvise::my_madvise(::uwvm::wasm::storage::execute_wasm_file.cbegin(),
                                     ::uwvm::wasm::storage::execute_wasm_file.size(),
                                     ::utils::madvise::madvise_flag::willneed);

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
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(nullptr),
                                    u8") Illegal WebAssembly file format.",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                return -3;  // wasm parsing error
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
                    ::utils::debug::timer parsing_timer{u8"parse binfmt ver1"};
#endif
                    ::uwvm::wasm::storage::execute_wasm_binfmt_ver1_storage =
                        ::uwvm::wasm::feature::binfmt_ver1_handler(::uwvm::wasm::feature::wasm_binfmt1_features,
                                                                   reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cbegin()),
                                                                   reinterpret_cast<::std::byte const*>(::uwvm::wasm::storage::execute_wasm_file.cend()));
                }
#if defined(__cpp_exceptions) && !defined(UWVM_TERMINATE_IMME_WHEN_PARSE)
                catch(::fast_io::error e)
                {
                    return -3;  // wasm parsing error
                }
#endif
                break;
            }
            default:
            {
#ifndef UWVM_DISABLE_OUTPUT_WHEN_PARSE
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"(offset=",
                                    ::fast_io::mnp::addrvw(4U * sizeof(char8_t)),
                                    u8") Unknown Binary Format Version of WebAssembly: \"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                    ::uwvm::wasm::storage::execute_wasm_binfmt_ver,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"\"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
#endif
                return -3;  // wasm parsing error
            }
        }

        // run vm
        switch(::uwvm::wasm::storage::execute_wasm_mode)
        {
            case ::parser::wasm::base::mode::objdump:
            {
                /// @todo objdump
                break;
            }
            default: ::fast_io::unreachable();
        }

        return 0;
    }
}  // namespace uwvm::run
