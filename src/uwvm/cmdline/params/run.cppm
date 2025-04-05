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

module;

#include <memory>

#include <utils/macro/push_macros.h>
#include <utils/ansies/ansi_push_macro.h>

export module uwvm.cmdline.params:run;

import fast_io;
import utils.io;
import utils.cmdline;

export namespace uwvm::cmdline::paras
{
    namespace details
    {
        inline constexpr ::fast_io::u8string_view run_alias{u8"-r"};
    }  // namespace details

    inline constexpr ::utils::cmdline::parameter run{.name{u8"--run"},
                                                     .describe{u8"Run WebAssembly."},
                                                     .usage{u8"<file> <argv[1]> <arg[2]> ..."},
                                                     .alias{::utils::cmdline::kns_u8_str_scatter_t{::std::addressof(details::run_alias), 1}}};
}  // namespace uwvm::cmdline::paras
