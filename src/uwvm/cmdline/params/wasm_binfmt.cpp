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

#ifdef UWVM_MODULE
import fast_io;
import utils.io;
import utils.ansies;
import utils.cmdline;
import parser.wasm.base;
import parser.wasm.standard.wasm1.type;
import uwvm.cmdline;
import uwvm.wasm.storage;
#else
# include <fast_io.h>
# include <utils/io/impl.h>
# include <utils/ansies/impl.h>
# include <utils/cmdline/impl.h>
# include <parser/wasm/base/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm/cmdline/impl.h>
# include <uwvm/wasm/storage/impl.h>
#endif

namespace uwvm::cmdline::paras::details
{
    UWVM_GNU_COLD extern ::utils::cmdline::parameter_return_type wasm_binfmt_callback([[maybe_unused]] ::utils::cmdline::parameter_parsing_results* para_begin,
                                                                                      ::utils::cmdline::parameter_parsing_results* para_curr,
                                                                                      ::utils::cmdline::parameter_parsing_results* para_end) noexcept
    {
        // "--abi" xxxxxxxxx
        //          currp1^
        auto currp1{para_curr + 1};

        // Check for out-of-bounds and not-argument
        if(currp1 == para_end || currp1->type != ::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Usage: " u8"[",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"--wasm-binfmt",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Wbf",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                u8"[detect|1]",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        // Setting the argument is already taken
        currp1->type = ::utils::cmdline::parameter_parsing_results_type::occupied_arg;

        auto currp1_str{currp1->str};

        if(currp1_str == u8"detect")
        {
            ::uwvm::wasm::storage::execute_wasm_binfmt_ver = 0;
            return ::utils::cmdline::parameter_return_type::def;
        }

        parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{};
        auto const [next, err]{::fast_io::parse_by_scan(currp1_str.cbegin(), currp1_str.cend(), binfmt_version)};

        // parse u32 error
        if(err != ::fast_io::parse_code::ok || next != currp1_str.cend()) [[unlikely]]
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Invalid Binary Format Version \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                currp1_str,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\". Usage: " u8"[",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"--wasm-binfmt",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Wbf",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                u8"[detect|1]",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");

            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        if(binfmt_version == static_cast<parser::wasm::standard::wasm1::type::wasm_u32>(1u))
        {
            ::uwvm::wasm::storage::execute_wasm_binfmt_ver = static_cast<parser::wasm::standard::wasm1::type::wasm_u32>(1u);
        }
        else [[unlikely]]
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Invalid Binary Format Version \"",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                binfmt_version,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"\". Usage: " u8"[",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"--wasm-binfmt",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Wbf",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                u8"[detect|1]",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");

            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        return ::utils::cmdline::parameter_return_type::def;
    }

}  // namespace uwvm::cmdline::paras::details
