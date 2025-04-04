﻿/********************************************************
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

module;

#include <cstdint>
#include <cstddef>
#include <memory>
#include <bit>

#include <utils/macro/push_macros.h>
#include <utils/ansies/ansi_push_macro.h>

export module uwvm.cmdline:parser;

import fast_io;
import utils.io;
import utils.cmdline;
import uwvm.cmdline.params;
#ifdef UWVM_TIMER
import utils.debug;
#endif
import :params;

export namespace uwvm::cmdline
{
    enum class parsing_return_val : unsigned
    {
        def,      // Continue with the main program
        return0,  // Instructs the main function to return 0
        returnm1  // Instructs the main function to return -1
    };

    // globals
    inline ::fast_io::vector<::utils::cmdline::parameter_parsing_results> parsing_result{};
    inline char8_t const* argv0_dir{};
    inline ::utils::cmdline::parameter_parsing_results* wasm_file_ppos{};

    /// @brief parsing cmdline
    inline constexpr parsing_return_val parsing(::std::size_t argc, char8_t const* const* argv) noexcept
    {
#ifdef UWVM_TIMER
        ::utils::debug::timer parsing_timer{u8"parsing parameters"};
#endif

        auto& pr{parsing_result};
        auto const& ht{::uwvm::cmdline::hash_table};

        // It is assumed that they are all initialized by default and no checks will be made
#if 0 
        pr.clear();
#endif
        pr.reserve(argc);

        // If argc is 0, prohibit running
        if(argc == 0) [[unlikely]]
        {
            ::fast_io::io::perr(
                ::utils::u8err,
                UWVM_AES_U8_RST_ALL
                    UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"No Parameters." UWVM_AES_U8_RST_ALL u8"\n\n");
            return parsing_return_val::returnm1;
        }

        auto curr_argv{argv};

        // Use argv0 as the program runtime path
        if(*curr_argv != nullptr) [[likely]]
        {
            pr.emplace_back_unchecked(::fast_io::u8cstring_view{::fast_io::mnp::os_c_str(*curr_argv)},
                                      nullptr,
                                      ::utils::cmdline::parameter_parsing_results_type::dir);
            // storage argv0
            argv0_dir = *curr_argv;
        }

        // preprocessing
        auto const argv_end{argv + argc};
        for(++curr_argv; curr_argv != argv_end; ++curr_argv)
        {
            if(*curr_argv == nullptr) [[unlikely]]
            {
                // This doesn't happen, but just in case
                continue;
            }

            if(::fast_io::u8cstring_view const argv_str{::fast_io::mnp::os_c_str(*curr_argv)}; argv_str.empty()) [[unlikely]]
            {
                // No characters, may appear on windows, the first value of this parameter is u8'\0'
                continue;
            }
            else if(argv_str.front_unchecked() == u8'-')
            {
                // this is a parameter
                // Special treatment for run
                constexpr auto run_para{::std::addressof(::uwvm::cmdline::paras::run)};

                // find hash table
                auto const para{::utils::cmdline::find_from_hash_table(ht, argv_str)};

                if(para == nullptr) [[unlikely]]
                {
                    // invalid parameter
                    pr.emplace_back_unchecked(argv_str, nullptr, ::utils::cmdline::parameter_parsing_results_type::invalid_parameter);
                }
                else if(para == run_para)
                {
                    // All subsequent parameters are runtime parameters and need not be parsed further, jumping directly out of the
                    pr.emplace_back_unchecked(argv_str, run_para, ::utils::cmdline::parameter_parsing_results_type::parameter);  // -- run

                    // grammatical error
                    if(++curr_argv == argv_end) [[unlikely]]
                    {
                        ::fast_io::io::perr(
                            ::utils::u8err,
                            UWVM_AES_U8_RST_ALL
                                UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"Usage: " u8"[" UWVM_AES_U8_GREEN u8"--run" UWVM_AES_U8_WHITE u8"|" UWVM_AES_U8_GREEN u8"-r" UWVM_AES_U8_WHITE u8"] " UWVM_AES_U8_YELLOW u8"<file> <argv1> <argv2> ..." UWVM_AES_U8_RST_ALL u8"\n\n");

                        return parsing_return_val::returnm1;
                    }

                    wasm_file_ppos = ::std::addressof(pr.emplace_back_unchecked(fast_io::u8cstring_view{::fast_io::mnp::os_c_str(*curr_argv)},
                                                                                nullptr,
                                                                                ::utils::cmdline::parameter_parsing_results_type::occupied_arg));  // wasm file

                    for(++curr_argv; curr_argv != argv_end; ++curr_argv)
                    {
                        pr.emplace_back_unchecked(::fast_io::u8cstring_view{::fast_io::mnp::os_c_str(*curr_argv)},
                                                  nullptr,
                                                  ::utils::cmdline::parameter_parsing_results_type::occupied_arg);  // wasm parameters
                    }

                    break;  // End preprocessing
                }
                else [[likely]]
                {
                    if(para->is_exist)  // Check for null pointer
                    {
                        // not nullptr
                        if(auto& para_is_exist{*para->is_exist}; para_is_exist)
                        {
                            pr.emplace_back_unchecked(argv_str, para, ::utils::cmdline::parameter_parsing_results_type::duplicate_parameter);
                        }
                        else
                        {
                            para_is_exist = true;  // Marker already exists
                            pr.emplace_back_unchecked(argv_str, para, ::utils::cmdline::parameter_parsing_results_type::parameter);
                        }
                    }
                    else { pr.emplace_back_unchecked(argv_str, para, ::utils::cmdline::parameter_parsing_results_type::parameter); }

                    // The preprocessor that calls this function
                    // Preprocessing is used to jump directly to the backmarked section.

                    // If a signed integer is required for a subsequent argument,
                    // marking one bit back as occupied_arg prevents the negative sign from being misidentified as an argument prefix.
                    if(para->pretreatment) { para->pretreatment(curr_argv, argv_end, pr); }
                }
            }
            else { pr.emplace_back_unchecked(argv_str, nullptr, ::utils::cmdline::parameter_parsing_results_type::arg); }
        }

        //   "--run" (end)         "wasm file name"
        // wasm_file_ppos - 1       wasm_file_ppos
        auto const end_pos{wasm_file_ppos ? wasm_file_ppos - 1 : pr.end()};

        // Checking for wrong parameters vs. duplicates
        {
            bool shouldreturn{};

            for(auto curr_pr{pr.begin() + 1}; curr_pr != end_pos; ++curr_pr)
            {
                if(curr_pr->type == ::utils::cmdline::parameter_parsing_results_type::invalid_parameter) [[unlikely]]
                {
                    shouldreturn = true;
                    ::fast_io::io::perr(
                        ::utils::u8err,
                        UWVM_AES_U8_RST_ALL
                            UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"invalid parameter: " UWVM_AES_U8_CYAN,
                        curr_pr->str);

                    // Finding the most similar parameters
                    ::fast_io::u8string_view f_test_str{};

                    ::std::size_t const str_size{curr_pr->str.size()};

                    // Assumed size facilitates multiplicative optimization
#if __has_cpp_attribute(assume)
                    constexpr ::std::size_t smax{::std::numeric_limits<::std::size_t>::max() / 4u};
                    [[assume(str_size < smax)]];
#endif
                    // First time variance requirement within 40%
                    ::std::size_t const test_size{str_size * 4u / 10u};
                    ::std::size_t f_test_size{test_size};

                    for(auto const& j: ::uwvm::cmdline::parameter_lookup_table)
                    {
                        if(j.str.size() < str_size - f_test_size || j.str.size() > str_size + f_test_size)
                        {
                            // When the string size difference is already greater than the editable distance difference, just skip the
                            continue;
                        }

                        // Maximum stack size that will hit
                        constexpr ::std::size_t shortest_path_stack_size{parameter_max_name_size + parameter_max_name_size * 4u / 10u + 1u};

                        // Calculate the shortest path distance
                        if(auto const dp_res{
                               ::utils::cmdline::shortest_path<shortest_path_stack_size>(curr_pr->str.data(), curr_pr->str.size(), j.str.data(), j.str.size())};
                           dp_res <= test_size)
                        {
                            f_test_str = j.str;
                            f_test_size = dp_res;
                        }
                    }

                    if(f_test_str.empty())
                    {
                        // The most similar parameters were not found
                        ::fast_io::io::perr(::utils::u8err, UWVM_AES_U8_RST_ALL u8"\n");
                    }
                    else
                    {
                        // Output the most similar parameter
                        ::fast_io::io::perr(::utils::u8err,
                                            UWVM_AES_U8_WHITE u8" (did you mean: " UWVM_AES_U8_GREEN,
                                            f_test_str,
                                            UWVM_AES_U8_WHITE u8")" UWVM_AES_U8_RST_ALL u8"\n");
                    }
                }
                else if(curr_pr->type == ::utils::cmdline::parameter_parsing_results_type::duplicate_parameter) [[unlikely]]
                {
                    shouldreturn = true;
                    ::fast_io::io::perr(
                        ::utils::u8err,
                        UWVM_AES_U8_RST_ALL
                            UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"duplicate parameter: " UWVM_AES_U8_CYAN,
                        curr_pr->str,
                        UWVM_AES_U8_RST_ALL u8"\n");
                }
            }

            if(shouldreturn) [[unlikely]]
            {
                ::fast_io::io::perrln(::utils::u8err);
                return parsing_return_val::returnm1;
            }
        }

        // Call the function corresponding to each parameter
        {
            bool needexit{};
            bool needterminal{};

            for(auto curr_pr{pr.begin() + 1}; curr_pr != end_pos; ++curr_pr)
            {
                if(curr_pr->para == nullptr)
                {
                    // nonparametric
                    continue;
                }

                if(auto const cb{curr_pr->para->handle}; cb != nullptr)
                {
                    ::utils::cmdline::parameter_return_type const res{cb(pr.begin(), curr_pr, pr.end())};
                    switch(res)
                    {
                        case ::utils::cmdline::parameter_return_type::def: break;
                        case ::utils::cmdline::parameter_return_type::return_m1_imme: return parsing_return_val::returnm1;
                        case ::utils::cmdline::parameter_return_type::return_imme: return parsing_return_val::return0;
                        case ::utils::cmdline::parameter_return_type::return_soon: needexit = true; break;
                        case ::utils::cmdline::parameter_return_type::err_imme: ::fast_io::fast_terminate();
                        case ::utils::cmdline::parameter_return_type::err_soon: needterminal = true; break;
                        default:
                            ::fast_io::unreachable();  // A correct implementation will not show any other results, and if it does, the behavior is undefined.
                    }
                }
            }

            if(needterminal) [[unlikely]] { ::fast_io::fast_terminate(); }

            if(needexit) [[unlikely]] { return parsing_return_val::returnm1; }

            // Check for unmarked arg

            bool shouldreturn{};

            for(auto curr_pr{pr.begin() + 1}; curr_pr != end_pos; ++curr_pr)
            {
                if(curr_pr->type == ::utils::cmdline::parameter_parsing_results_type::arg) [[unlikely]]
                {
                    shouldreturn = true;

                    ::fast_io::io::perr(
                        ::utils::u8err,
                        UWVM_AES_U8_RST_ALL UWVM_AES_U8_WHITE u8"uwvm: " UWVM_AES_U8_RED u8"[error] " UWVM_AES_U8_WHITE u8"invalid option: " UWVM_AES_U8_CYAN,
                        curr_pr->str,
                        UWVM_AES_U8_RST_ALL u8"\n");
                }
            }

            if(shouldreturn) [[unlikely]]
            {
                ::fast_io::io::perrln(::utils::u8err);
                return parsing_return_val::returnm1;
            }
        }
        return parsing_return_val::def;
    }
}  // namespace uwvm::cmdline
