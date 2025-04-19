/********************************************************
 * Ultimate WebAssembly Virtual Machine (debug_output 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
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
import utils.cmdline;
#else
// std
# include <memory>
// macro
# include <utils/macro/push_macros.h>
# include <utils/ansies/ansi_push_macro.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <utils/cmdline/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm::cmdline::paras
{
    namespace details
    {
        inline bool debug_output_is_exist{};
        inline constexpr ::fast_io::u8string_view debug_output_alias{u8"-Dop"};
        extern "C++" ::utils::cmdline::parameter_return_type debug_output_callback(::utils::cmdline::parameter_parsing_results*,
                                                                                   ::utils::cmdline::parameter_parsing_results*,
                                                                                   ::utils::cmdline::parameter_parsing_results*) noexcept;

    }  // namespace details

    inline constexpr ::utils::cmdline::parameter debug_output{.name{u8"--debug-output"},
                                                              .describe{u8"Setting the output of the uwvm, (DEFAULT: err)."},
                                                              .usage{
#if !defined(__AVR__)
                                                                  u8"[out|err|file <file>]"
#else
                                                                  u8"[out|err]"
#endif
                                                              },
                                                              .alias{::utils::cmdline::kns_u8_str_scatter_t{::std::addressof(details::debug_output_alias), 1}},
                                                              .handle{::std::addressof(details::debug_output_callback)},
                                                              .is_exist{::std::addressof(details::debug_output_is_exist)},
                                                              .cate{::utils::cmdline::categorization::debug}};
}  // namespace uwvm::cmdline::paras
