/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-09
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
import parser.wasm.concepts;
import parser.wasm.standard;
#else
// import
# include <fast_io.h>
# include <fast_io_dsal/tuple.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif
UWVM_MODULE_EXPORT namespace uwvm::wasm::feature
{
    /// @brief All feature
    inline constexpr ::fast_io::tuple all_features{
        ::parser::wasm::standard::wasm1::features::wasm1{}
        // Add here
    };
    using all_feature_t = decltype(all_features);

    /// @brief wasm binfmt ver1 features
    using wasm_binfmt_ver1_features_t =
        decltype(::parser::wasm::concepts::operation::get_specified_binfmt_feature_tuple_from_all_freatures_tuple<1>(all_features));
    inline constexpr wasm_binfmt_ver1_features_t wasm_binfmt1_features{};
    using wasm_binfmt_ver1_module_storage_t = decltype(::parser::wasm::concepts::operation::get_module_storage_type_from_tuple(wasm_binfmt1_features));
    inline constexpr auto binfmt_ver1_handler{::parser::wasm::concepts::operation::get_binfmt_handler_func_p_from_tuple<1>(wasm_binfmt1_features)};

}  // namespace uwvm::wasm::feature
