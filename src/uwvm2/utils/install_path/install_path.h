/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-29
 * @copyright   ASHP-1.0 License
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
// no import
#else
// macro
# include <uwvm2/utils/macro/push_macros.h>
// include
# ifdef UWVM_SUPPORT_INSTALL_PATH
#  include <fast_io.h>
#  include <fast_io_driver/install_path.h>
# endif
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

#ifdef UWVM_SUPPORT_INSTALL_PATH
UWVM_MODULE_EXPORT namespace uwvm2::utils::install_path
{
    inline ::fast_io::install_path get_module_install_path_noexcept() noexcept
    {
        ::fast_io::install_path ret{};
# ifdef __cpp_exceptions
        try
# endif
        {
            ret = ::fast_io::get_module_install_path();
        }
# ifdef __cpp_exceptions
        catch(::fast_io::error)
        {
            // If you can't get the install path, do nothing!
        }
# endif
        return ret;
    }

}  // namespace uwvm2::utils::install_path
#endif

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif
