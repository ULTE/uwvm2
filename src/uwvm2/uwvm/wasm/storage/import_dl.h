/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @brief       Imported local dynamic libraries
 * @details     "--wasm-load-dl" or "-Wld"
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-28
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
import fast_io;
#else
// macro
# include <uwvm2/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/vector.h>
#endif

#ifdef UWVM_CAN_LOAD_DL
# ifndef UWVM_MODULE_EXPORT
#  define UWVM_MODULE_EXPORT
# endif
UWVM_MODULE_EXPORT namespace uwvm2::uwvm::wasm::storage
{
    inline ::fast_io::vector<::fast_io::native_dll_file> import_dl_file{};  // [global] No global variable dependencies from other translation units

    // TODO: import_dl_func // The result of parsing the dl is used to add the import module directly.
}  // namespace uwvm2::uwvm::wasm::storage
#endif

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif

