/********************************************************
 * Ultimate WebAssembly Virtual Machine (help 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-30
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

#include <memory>

#include <utils/macro/push_macros.h>
#include <utils/ansies/ansi_push_macro.h>

import fast_io;
import utils.io;
import utils.cmdline;
import uwvm.cmdline;
import parser.wasm.base;
import uwvm.wasm.storage;

namespace uwvm::cmdline::paras::details
{
    UWVM_GNU_COLD extern ::utils::cmdline::parameter_return_type mode_callback(::utils::cmdline::parameter_parsing_results* para_begin,
                                                                               ::utils::cmdline::parameter_parsing_results* para_curr,
                                                                               ::utils::cmdline::parameter_parsing_results* para_end) noexcept
    {
        // "--mode" xxxxxxxxx
        //           currp1^
        auto currp1{para_curr + 1};

        // Check for out-of-bounds and not-argument
        if(currp1 == para_end || currp1->type != ::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
        {
            ::fast_io::io::perr(
                ::utils::u8err,
                UWVM_AES_U8_RST_ALL
                    UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"Usage: " u8"[" UWVM_AES_U8_GREEN u8"--mode" UWVM_AES_U8_WHITE u8"|" UWVM_AES_U8_GREEN u8"-m" UWVM_AES_U8_WHITE u8"] " UWVM_AES_U8_YELLOW u8"[objdump]" UWVM_AES_U8_RST_ALL u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        // Setting the argument is already taken
        currp1->type = ::utils::cmdline::parameter_parsing_results_type::occupied_arg;

        if(auto currp1_str{currp1->str}; currp1_str == u8"objdump") { ::uwvm::wasm::storage::execute_wasm_mode = ::parser::wasm::base::mode::objdump; }
        else [[unlikely]]
        {
            ::fast_io::io::perr(
                ::utils::u8err,
                UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"Invalid mode \"" UWVM_AES_U8_CYAN,
                currp1_str,
                UWVM_AES_U8_WHITE u8"\". Usage: "  u8"[" UWVM_AES_U8_GREEN u8"--mode" UWVM_AES_U8_WHITE u8"|" UWVM_AES_U8_GREEN u8"-m" UWVM_AES_U8_WHITE u8"] " UWVM_AES_U8_YELLOW u8"[objdump]" UWVM_AES_U8_RST_ALL u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }
        return ::utils::cmdline::parameter_return_type::def;
    }

}  // namespace uwvm::cmdline::paras::details
