/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-24
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
// std
# include <cstdint>
# include <cstddef>
# include <concepts>
# include <new>
// macro
# include <uwvm2/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/array.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::utils::cmdline
{
    /// @brief      Shortest Path Algorithm for Strings
    /// @details    Compute the shortest path between two strings with a time complexity of O(n²) and a space complexity of O(n).
    ///             In the template, if Stack_Len is 0, heap allocation is used; if Stack_Len is greater than 0, a stack of length Stack_Len is used.
    ///             This optimization benefits command-line parsing when command lengths can be determined at compile time.
    /// @param      x_str       fist string ptr
    /// @param      x_length    fist string length
    /// @param      y_str       second string ptr
    /// @param      y_length    second string length

    template <::std::size_t Stack_Len = 0, ::std::integral char_type>
    UWVM_GNU_CONST inline constexpr ::std::size_t shortest_path(char_type const* x_str,
                                                                ::std::size_t x_length,
                                                                char_type const* y_str,
                                                                ::std::size_t y_length) noexcept
    {
        using Alloc = ::fast_io::native_typed_thread_local_allocator<::std::size_t>;

        ::std::size_t* d{};
        [[maybe_unused]] ::fast_io::array<::std::size_t, Stack_Len> storage;

        if constexpr(Stack_Len) { d = storage.data(); }
        else
        {
            if UWVM_IF_CONSTEVAL { d = ::new ::std::size_t[y_length + 1uz]; }
            else
            {
                d = Alloc::allocate(y_length + 1uz);
            }
        }

        for(::std::size_t j{}; j <= y_length; j++) { d[j] = j; }

        for(::std::size_t i{1}; i <= x_length; i++)
        {
            ::std::size_t old{i - 1uz};
            d[0uz] = i;
            for(::std::size_t j{1uz}; j <= y_length; j++)
            {
                ::std::size_t const temp{d[j]};
                if(x_str[i - 1] == y_str[j - 1uz]) { d[j] = old; }
                else
                {
                    ::std::size_t min{d[j] + 1uz};
                    if(d[j - 1uz] + 1uz < min) { min = d[j - 1uz] + 1uz; }
                    if(old + 1uz < min) { min = old + 1uz; }
                    d[j] = min;
                }
                old = temp;
            }
        }

        ::std::size_t const ret{d[y_length]};

        if constexpr(!Stack_Len)
        {
            if UWVM_IF_CONSTEVAL { ::delete[] d; }
            else
            {
                Alloc::deallocate_n(d, y_length + 1uz);
            }
        }

        return ret;
    }

}  // namespace uwvm2::utils::cmdline

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif
