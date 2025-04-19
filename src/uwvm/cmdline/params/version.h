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
import utils.cmdline;
#else
// std
# include <memory>
// macro
# include <utils/macro/push_macros.h>
# include <utils/ansies/ansi_push_macro.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/array.h>
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
        inline bool version_is_exist{};
        inline constexpr ::fast_io::array<::fast_io::u8string_view, 2> version_alias{u8"-v", u8"-ver"};
        extern "C++" ::utils::cmdline::parameter_return_type version_callback(::utils::cmdline::parameter_parsing_results*,
                                                                              ::utils::cmdline::parameter_parsing_results*,
                                                                              ::utils::cmdline::parameter_parsing_results*) noexcept;

    }  // namespace details

    inline constexpr ::utils::cmdline::parameter version{
        .name{u8"--version"},
        .describe{u8"Output version information."},
        .alias{::utils::cmdline::kns_u8_str_scatter_t{details::version_alias.data(), details::version_alias.size()}},
        .handle{::std::addressof(details::version_callback)},
        .is_exist{::std::addressof(details::version_is_exist)}};
}  // namespace uwvm::cmdline::paras
