/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
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
#else
// macro
# include <utils/macro/push_macros.h>
// import
# include <fast_io.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::base
{
    [[noreturn]] inline void throw_wasm_parse_code([[maybe_unused]] ::fast_io::parse_code code) UWVM_THROWS
    {
#ifdef UWVM_TERMINATE_IMME_WHEN_PARSE
        ::fast_io::fast_terminate();
#else
# ifdef __cpp_exceptions
#  if defined(_MSC_VER) && (!defined(_HAS_EXCEPTIONS) || _HAS_EXCEPTIONS == 0)
        ::fast_io::fast_terminate();
#  else
        throw ::fast_io::error{::fast_io::parse_domain_value, static_cast<::std::size_t>(static_cast<char8_t>(code))};
#  endif
# else
        ::fast_io::fast_terminate();
# endif
#endif
    }
}  // namespace parser::wasm::base
