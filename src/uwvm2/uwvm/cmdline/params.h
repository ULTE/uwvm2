/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-27
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
import uwvm2.utils.cmdline;
import uwvm2.uwvm.cmdline.params;
#else
// std
# include <memory>
// import
# include <uwvm2/utils/cmdline/impl.h>
# include "params/impl.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::uwvm::cmdline
{
    namespace details
    {
        inline constexpr ::uwvm2::utils::cmdline::parameter const* parameter_unsort[]{
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::version),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::run),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::help),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::mode),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::wasm_abi),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::wasm_binfmt),
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::u8log_output),

#ifdef _DEBUG
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::test),
#endif

#if defined(_WIN32) && (_WIN32_WINNT < 0x0A00 || defined(_WIN32_WINDOWS))
            ::std::addressof(::uwvm2::uwvm::cmdline::paras::log_win32_use_ansi),
#endif
        };
    }  // namespace details

    inline constexpr auto parameters{::uwvm2::utils::cmdline::parameter_sort(details::parameter_unsort)};

    inline constexpr ::std::size_t parameter_lookup_table_size{::uwvm2::utils::cmdline::calculate_alias_parameters_size(parameters)};
    inline constexpr auto parameter_lookup_table{::uwvm2::utils::cmdline::expand_alias_parameters_and_check<parameter_lookup_table_size>(parameters)};

    inline constexpr ::std::size_t parameter_max_principal_name_size{::uwvm2::utils::cmdline::calculate_max_principal_name_size(parameters)};
    inline constexpr ::std::size_t parameter_max_name_size{::uwvm2::utils::cmdline::calculate_max_para_size(parameter_lookup_table)};

    inline constexpr auto hash_table_size{::uwvm2::utils::cmdline::calculate_hash_table_size(parameter_lookup_table)};
    inline constexpr auto hash_table{
        ::uwvm2::utils::cmdline::generate_hash_table<hash_table_size.hash_table_size, hash_table_size.extra_size, hash_table_size.real_max_conflict_size>(
            parameter_lookup_table)};

    inline constexpr ::std::size_t hash_table_byte_sz{sizeof(hash_table)};
    // inline constexpr auto sizeof_hash_table{sizeof(hash_table)};
}  // namespace uwvm2::uwvm::cmdline
