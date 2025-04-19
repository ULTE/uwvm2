/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       The wasm file that will be run
 * @details     "--run" or "-r"
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
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import uwvm.wasm.feature;
#else
// import
# include <fast_io.h>
# include <parser/wasm/base/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm/wasm/feature/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm::wasm::storage
{
    inline ::fast_io::native_file_loader execute_wasm_file{};                                  // No global variable dependencies from other translation units
    inline ::parser::wasm::base::mode execute_wasm_mode{::parser::wasm::base::mode::objdump};  // No global variable dependencies from other translation units
    inline ::parser::wasm::base::abi execute_wasm_abi{::parser::wasm::base::abi::detect};      // No global variable dependencies from other translation units
    inline ::parser::wasm::standard::wasm1::type::wasm_u32 execute_wasm_binfmt_ver{};          // No global variable dependencies from other translation units

    // WASM Module Binfmt 1
    inline ::uwvm::wasm::feature::wasm_binfmt_ver1_module_storage_t
        execute_wasm_binfmt_ver1_storage{};  // No global variable dependencies from other translation units

}  // namespace uwvm::wasm::storage
