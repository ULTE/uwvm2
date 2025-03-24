/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-21
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

export module utils.ansies:cursor;

import fast_io;

/// @brief not support on win9x and msdos
#if !((defined(_WIN32) && defined(_WIN32_WINDOWS)) || defined(__MSDOS__) || defined(__DJGPP__))

export namespace utils::ansies
{
    struct crs
    {
        ::std::uint_least32_t feat{};
        enum class cursor_variables : char8_t
        {
            up = u8'A',
            down = u8'B',
            right = u8'C',
            left = u8'D',
            csc = u8'J',
            cln = u8'K',
        } cursor_var{};
    };

    template <::std::integral char_type>
        requires (sizeof(char_type) == sizeof(char8_t))
    inline constexpr ::std::size_t print_reserve_size(::fast_io::io_reserve_type_t<char_type, crs>) noexcept
    {
        constexpr ::std::size_t ul32_real_size{::fast_io::pr_rsv_size<char_type, ::std::uint_least32_t>};
        constexpr ::std::size_t max_size{3 + ul32_real_size};
        return max_size;
    }

    namespace details
    {
        template <::std::integral char_type>
            requires (sizeof(char_type) == sizeof(char8_t))
        inline constexpr char_type* crs_print_reserve_impl(char_type* iter, crs::cursor_variables cv, ::std::uint_least32_t f) noexcept
        {
            ::fast_io::freestanding::my_memcpy(iter, u8"\033[", 2u);
            char_type* curr_pos{iter + 2u};
            curr_pos = ::fast_io::pr_rsv_to_iterator_unchecked(curr_pos, f);
            *curr_pos = static_cast<char_type>(cv);
            return ++curr_pos;
        }
    }  // namespace details

    template <::std::integral char_type>
        requires (sizeof(char_type) == sizeof(char8_t))
    inline constexpr char_type* print_reserve_define(::fast_io::io_reserve_type_t<char_type, crs>, char_type* iter, crs c) noexcept
    {
        return details::crs_print_reserve_impl(iter, c.cursor_var, c.feat);
    }

}  // namespace utils::ansies
#endif
