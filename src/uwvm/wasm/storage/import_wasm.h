/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       Imported wasm modules
 * @details     "--wasm-load-wasm" or "-Wlw"
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-28
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
// import
# include <fast_io.h>
# include <fast_io_dsal/vector.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif
UWVM_MODULE_EXPORT namespace uwvm::wasm::storage
{
    inline ::fast_io::vector<::fast_io::native_file_loader> import_wasm_file{};  // No global variable dependencies from other translation units

    // TODO: import_wasm_module // The result of parsing the wasm is used to add the import module directly.
}  // namespace uwvm::wasm::storage
