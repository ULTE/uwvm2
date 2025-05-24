/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @brief       The wasm file that will be run
 * @details     "--run" or "-r"
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
import uwvm2.parser.wasm.concepts;
import uwvm2.parser.wasm.standard.wasm1.type;
import uwvm2.uwvm.wasm.base;
import uwvm2.uwvm.wasm.feature;
#else
// import
# include <fast_io.h>
# include <uwvm2/parser/wasm/concepts/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm2/uwvm/wasm/base/impl.h>
# include <uwvm2/uwvm/wasm/feature/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::uwvm::wasm::storage
{
    inline ::fast_io::native_file_loader execute_wasm_file{};  // [global] No global variable dependencies from other translation units
    inline ::uwvm2::uwvm::wasm::base::mode execute_wasm_mode{
        ::uwvm2::uwvm::wasm::base::mode::objdump};  // [global] No global variable dependencies from other translation units
    inline ::uwvm2::uwvm::wasm::base::abi execute_wasm_abi{
        ::uwvm2::uwvm::wasm::base::abi::detect};  // [global] No global variable dependencies from other translation units
    inline ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32
        execute_wasm_binfmt_ver{};  // [global] No global variable dependencies from other translation units

    // WASM Module Binfmt 1
    inline ::uwvm2::uwvm::wasm::feature::wasm_binfmt_ver1_feature_parameter_storage_t
        global_wasm_binfmt_ver1_paramaters{};  // [global] No global variable dependencies from other translation units

    inline ::uwvm2::uwvm::wasm::feature::wasm_binfmt_ver1_module_storage_t
        execute_wasm_binfmt_ver1_storage{};  // [global] No global variable dependencies from other translation units

}  // namespace uwvm2::uwvm::wasm::storage
