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
import uwvm.cmdline;
#else
# include <fast_io.h>
# include <fast_io_dsal/array.h>
# include <utils/io/impl.h>
# include <utils/ansies/impl.h>
# include <utils/cmdline/impl.h>
# include <uwvm/cmdline/impl.h>
#endif

namespace uwvm::cmdline::paras::details
{
    UWVM_GNU_COLD extern ::utils::cmdline::parameter_return_type debug_output_callback([[maybe_unused]] ::utils::cmdline::parameter_parsing_results* para_begin,
                                                                                       ::utils::cmdline::parameter_parsing_results* para_curr,
                                                                                       ::utils::cmdline::parameter_parsing_results* para_end) noexcept
    {
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
                                u8"--debug-output",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Dop",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
#if !defined(__AVR__)
                                u8"[out|err|file <file>]"
#else
                                u8"[out|err]"
#endif
                                ,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

        // Setting the argument is already taken
        currp1->type = ::utils::cmdline::parameter_parsing_results_type::occupied_arg;

#if !defined(__AVR__)
        // win32 and posix
        if(auto currp1_str{currp1->str}; currp1_str == u8"out") { ::utils::debug_output = ::fast_io::u8native_file{::fast_io::io_dup, ::fast_io::u8out()}; }
        else if(currp1_str == u8"err") { ::utils::debug_output = ::fast_io::u8native_file{::fast_io::io_dup, ::fast_io::u8err()}; }
        else if(currp1_str == u8"file")
        {
            auto currp2{para_curr + 2};

            // Check for out-of-bounds and not-argument
            if(currp2 == para_end || currp2->type != ::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
            {
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"Usage: " u8"[",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                    u8"--debug-output",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"|",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                    u8"-Dop",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                    u8"file <file>",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n\n");
                return ::utils::cmdline::parameter_return_type::return_m1_imme;
            }

            // Setting the argument is already taken
            currp2->type = ::utils::cmdline::parameter_parsing_results_type::occupied_arg;

            auto currp2_str{currp2->str};

            try
            {
                ::utils::debug_output = ::fast_io::u8native_file{currp2_str, ::fast_io::open_mode::out};
            }
            catch(::fast_io::error e)
            {
                ::fast_io::io::perr(::utils::debug_output,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                    u8"uwvm: ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                    u8"[error] ",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"Unable to open debug output file \"",
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_CYAN),
                                    currp2_str,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                    u8"\": ",
                                    e,
                                    ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                    u8"\n"
#ifndef _WIN32
                                    u8"\n"
#endif
                                    );
                return ::utils::cmdline::parameter_return_type::return_m1_imme;
            }
        }
        else
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Usage: " u8"[",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"--debug-output",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Dop",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                u8"[out|err|file <file>]",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }

#else
        // on AVR only support cstdout and cstderr
        if(auto currp1_str{currp1->str}; currp1_str == u8"out") { ::utils::debug_output = ::fast_io::u8c_stdout(); }
        else if(currp1_str == u8"err") { ::utils::debug_output = ::fast_io::u8c_stderr(); }
        else
        {
            ::fast_io::io::perr(::utils::debug_output,
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE),
                                u8"uwvm: ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RED),
                                u8"[error] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"Usage: " u8"[",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"--debug-output",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"|",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_GREEN),
                                u8"-Dop",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_WHITE),
                                u8"] ",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_YELLOW),
                                u8"[out|err]",
                                ::fast_io::mnp::cond(::utils::ansies::put_color, UWVM_AES_U8_RST_ALL),
                                u8"\n\n");
            return ::utils::cmdline::parameter_return_type::return_m1_imme;
        }
#endif

        return ::utils::cmdline::parameter_return_type::def;
    }

}  // namespace uwvm::cmdline::paras::details
