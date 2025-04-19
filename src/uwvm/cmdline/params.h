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
import utils.cmdline;
import uwvm.cmdline.params;
#else
// std
# include <memory>
// import
# include <utils/cmdline/impl.h>
# include "params/impl.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm::cmdline
{
    namespace details
    {
        inline constexpr ::utils::cmdline::parameter const* parameter_unsort[]{
            ::std::addressof(::uwvm::cmdline::paras::version),
            ::std::addressof(::uwvm::cmdline::paras::run),
            ::std::addressof(::uwvm::cmdline::paras::help),
            ::std::addressof(::uwvm::cmdline::paras::mode),
            ::std::addressof(::uwvm::cmdline::paras::wasm_abi),
            ::std::addressof(::uwvm::cmdline::paras::wasm_binfmt),
            ::std::addressof(::uwvm::cmdline::paras::debug_output),

#ifdef _DEBUG
            ::std::addressof(::uwvm::cmdline::paras::test),
#endif
        };
    }  // namespace details

    inline constexpr auto parameters{::utils::cmdline::parameter_sort(details::parameter_unsort)};

    inline constexpr ::std::size_t parameter_lookup_table_size{::utils::cmdline::calculate_alias_parameters_size(parameters)};
    inline constexpr auto parameter_lookup_table{::utils::cmdline::expand_alias_parameters_and_check<parameter_lookup_table_size>(parameters)};

    inline constexpr ::std::size_t parameter_max_principal_name_size{::utils::cmdline::calculate_max_principal_name_size(parameters)};
    inline constexpr ::std::size_t parameter_max_name_size{::utils::cmdline::calculate_max_para_size(parameter_lookup_table)};

    inline constexpr auto hash_table_size{::utils::cmdline::calculate_hash_table_size(parameter_lookup_table)};
    inline constexpr auto hash_table{
        ::utils::cmdline::generate_hash_table<hash_table_size.hash_table_size, hash_table_size.extra_size, hash_table_size.real_max_conflict_size>(
            parameter_lookup_table)};

    inline constexpr ::std::size_t hash_table_byte_sz{sizeof(hash_table)};
    // inline constexpr auto sizeof_hash_table{sizeof(hash_table)};
}  // namespace uwvm::cmdline
