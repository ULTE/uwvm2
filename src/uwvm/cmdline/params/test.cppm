﻿/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-07
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

export module uwvm.cmdline.params:test;

#ifdef _DEBUG

import fast_io;
import utils.cmdline;

export namespace uwvm::cmdline::paras
{
    namespace details
    {
        inline bool test_is_exist{};
        extern "C++" ::utils::cmdline::parameter_return_type test_callback(::utils::cmdline::parameter_parsing_results*,
                                                                           ::utils::cmdline::parameter_parsing_results*,
                                                                           ::utils::cmdline::parameter_parsing_results*) noexcept;

    }  // namespace details

    inline constexpr ::utils::cmdline::parameter test{.name{u8"--test"},
                                                      .describe{u8"Debug Test."},
                                                      .handle{::std::addressof(details::test_callback)},
                                                      .is_exist{::std::addressof(details::test_is_exist)}};
}  // namespace uwvm::cmdline::paras

#endif
