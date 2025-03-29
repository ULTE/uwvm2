/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-25
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
#include <algorithm>

#include <utils/macro/push_macros.h>

export module utils.cmdline:handle;

import fast_io;

export namespace utils::cmdline
{
    /// @brief Used to indicate parameter type
    enum class parameter_parsing_results_type : unsigned
    {
        arg,                  // normal args
        occupied_arg,         // The occupied args are used for preprocessing or running wasm
        parameter,            // Correct parameters
        invalid_parameter,    // Invalid parameter
        duplicate_parameter,  // Duplicate parameter
        dir                   // The type of the first parameter, indicating the current program running path
    };

    struct parameter;

    /// @brief Parsing results of each crtmain parameter
    struct parameter_parsing_results
    {
        ::fast_io::u8cstring_view str{};        // Parameter content
        parameter const* para{};                // Corresponding parameter. If it is not a parameter, it is nullptr
        parameter_parsing_results_type type{};  // Parameter type
    };

    // Not recommended
#if 0
    /// @brief Structure to storage parameter_parsing_results
    struct parameter_parsing_results_storage UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
    {
        using Alloc = ::fast_io::native_typed_global_allocator<parameter_parsing_results>;

        parameter_parsing_results* begin{};
        parameter_parsing_results* end{};

        inline constexpr parameter_parsing_results_storage() noexcept = default;

        inline constexpr parameter_parsing_results_storage(::std::size_t argc) noexcept
        {
            if UWVM_IF_CONSTEVAL { this->begin = ::new parameter_parsing_results[argc]; }
            else { this->begin = Alloc::allocate(argc); }
            this->end = this->begin + argc;
        }

        inline constexpr parameter_parsing_results_storage(parameter_parsing_results_storage const&) = delete;
        inline constexpr parameter_parsing_results_storage& operator= (parameter_parsing_results_storage const&) = delete;

        inline constexpr parameter_parsing_results_storage(parameter_parsing_results_storage&& other) noexcept : begin{other.begin}, end{other.end}
        {
            other.begin = nullptr;
            other.end = nullptr;
        }

        inline constexpr parameter_parsing_results_storage& operator= (parameter_parsing_results_storage&& other) noexcept
        {
            if(::std::addressof(other) == this) [[unlikely]] { return *this; }

            this->begin = other.begin;
            other.begin = nullptr;
            this->end = other.end;
            other.end = nullptr;
            return *this;
        }

        inline constexpr ~parameter_parsing_results_storage() { clear(); }

        inline constexpr void alloc(::std::size_t argc) noexcept
        {
            if(!this->begin) [[likely]]
            {
                if UWVM_IF_CONSTEVAL { this->begin = ::new parameter_parsing_results[argc]; }
                else { this->begin = Alloc::allocate(argc); }
                this->end = this->begin + argc;
            }
        }

        inline constexpr void clear() noexcept
        {
            if(this->begin) [[likely]]
            {
                if UWVM_IF_CONSTEVAL { ::delete[] this->begin; }
                else
                {
                    auto const dealloc_size{static_cast<::std::size_t>(this->end - this->begin)};
                    Alloc::deallocate_n(this->begin, dealloc_size);
                }
            }
        }
    };
#endif

    /// @brief Used to indicate the return type of the parameter parser
    enum class parameter_return_type : unsigned
    {
        def,             // Continue with the program
        return_m1_imme,  // return -1 immediately
        return_imme,     // return 0 immediately
        return_soon,     // return 0 after parsing
        err_imme,        // trap immediately
        err_soon         // trap after parsing
    };

    /// @brief type for consecutive alias
    using kns_u8_str_scatter_t = ::fast_io::basic_io_scatter_t<::fast_io::u8string_view>;

    /// @brief type for handle function
    using handle_func_type = parameter_return_type (*)(parameter_parsing_results* para_begin,
                                                       parameter_parsing_results* para_curr,
                                                       parameter_parsing_results* para_end) noexcept;

    /// @brief type for pretreatment function
    using parameter_func_type = void (*)(char8_t const* const*& argv_curr,
                                         char8_t const* const* argv_end,
                                         ::fast_io::vector<parameter_parsing_results>& pr) noexcept;

    /// @brief User-defined parameters and handlers
    /// @brief Command line arguments will be encoded in ascii and will not be specialized for encodings such as ebcdic.
    struct parameter
    {
        ::fast_io::u8string_view const name{};      // parameter name
        ::fast_io::u8string_view const describe{};  // describtion shown in help
        kns_u8_str_scatter_t alias{};               // alias names
        handle_func_type handle{};                  // formal processing results
        parameter_func_type pretreatment{};         // pretreatment
        bool* is_exist{};                           // When it is not nullptr, repeated errors will be reported
    };

    /// @brief      sort the parameter const* const [N]
    /// @details    Sort user-defined parameters.
    ///             This function only allows consteval to implement.
    template <::std::size_t N>
    inline consteval auto parameter_sort(parameter const* const (&punsort)[N]) noexcept
    {
        ::fast_io::array<parameter const*, N> res{};
        for(::std::size_t i{}; i < N; ++i) { res.index_unchecked(i) = punsort[i]; }
        ::std::ranges::sort(res, [](parameter const* const a, parameter const* const b) noexcept -> bool { return a->name < b->name; });
        return res;
    }

    /// @brief This structure is used to store the parameters of all aliases
    struct alias_parameter
    {
        ::fast_io::u8string_view str{};  // raw name or alias name
        parameter const* para{};         // Equivalent parameter
    };

    /// @brief      Calculate all parameters sizes
    /// @details    Calculate the total number of aliases in the sorting parameter results obtained by parameter_sort
    ///             This function only allows consteval to implement.
    template <::std::size_t N>
    inline consteval ::std::size_t calculate_alias_parameters_size(::fast_io::array<parameter const*, N> const& punsort) noexcept
    {
        ::std::size_t res{};
        for(::std::size_t i{}; i < N; ++i)
        {
            ++res;                                         // raw name size == 1
            res += punsort.index_unchecked(i)->alias.len;  // alias name size == alias.len
        }
        return res;
    }

    /// @brief judge whether parameter has invalid char
    inline constexpr bool is_invalid_paramater_char(char8_t c) noexcept
    {
        if(c >= 0x21 && c <= 0x7E)
        {
            switch(c)
            {
                case u8'/': [[fallthrough]];
                case u8'\\': [[fallthrough]];
                case u8':': [[fallthrough]];
                case u8'*': [[fallthrough]];
                case u8'?': [[fallthrough]];
                case u8'\"': [[fallthrough]];
                case u8'<': [[fallthrough]];
                case u8'>': [[fallthrough]];
                case u8'|': return true;
                default: return false;
            }
        }
        else { return true; }
    }

    /// @brief this function expand all parameter raw name and it alias name and check whether they are valid
    /// @details AllParaSize is the value calculate_alias_parameters_size return
    template <::std::size_t AllParaSize, ::std::size_t N>
    inline consteval auto expand_alias_parameters_and_check(::fast_io::array<parameter const*, N> const& punsort) noexcept
    {
        ::fast_io::array<alias_parameter, AllParaSize> res{};
        ::std::size_t res_pos{};

        // expand all alias patameters
        for(::std::size_t i{}; i < N; ++i)
        {
            res.index_unchecked(res_pos) = {punsort.index_unchecked(i)->name, punsort.index_unchecked(i)};
            ++res_pos;
            for(::std::size_t j{}; j < punsort.index_unchecked(i)->alias.len; ++j)
            {
                res.index_unchecked(res_pos) = {punsort.index_unchecked(i)->alias.base[j], punsort.index_unchecked(i)};
                ++res_pos;
            }
        }

        // sort
        ::std::ranges::sort(res, [](alias_parameter const& a, alias_parameter const& b) noexcept -> bool { return a.str < b.str; });

        // check is invalid
        ::fast_io::u8string_view check{};  // Empty strings will be sorted and placed first.
        for(auto const& i: res)
        {
            if(i.str == check || i.str.front_unchecked() != u8'-')
            {
                // Duplicate parameters are not allowed
                // The first character of the parameter must be '-'
                ::fast_io::fast_terminate();
            }
            else
            {
                if(i.str.size() == 1)
                {
                    // "-" is invalid
                    ::fast_io::fast_terminate();
                }
                else
                {
                    for(auto c: i.str)
                    {
                        if(is_invalid_paramater_char(c))
                        {
                            // invalid parameter character
                            ::fast_io::fast_terminate();
                        }
                    }
                }
                check = i.str;  // check duplicate
            }
        }
        return res;
    }

    /// @brief      Calculate max parameter size
    /// @details    Maximum long distance used to provide to the shortest path
    template <::std::size_t N>
    inline consteval ::std::size_t calculate_max_para_size(::fast_io::array<alias_parameter, N> const& punsort) noexcept
    {
        ::std::size_t max_size{};
        for(::std::size_t i{}; i < N; ++i) { max_size = ::std::max(max_size, punsort.index_unchecked(i).str.size()); }
        return max_size;
    }

    /// @brief      Minimum hash table size to start generating
    /// @details    2 ^ hash_size_base
    inline constexpr ::std::size_t hash_size_base{4u};

    /// @brief      Maximum conflict size above which the hashtable will be expanded.
    inline constexpr ::std::size_t max_conflict_size{8u};

    struct calculate_hash_table_size_res
    {
        ::std::size_t hash_table_size{};
        ::std::size_t extra_size{};
    };

    /// @brief      Calculate the size of the hash_table with the maximum conflict size
    template <::std::size_t N>
    inline consteval calculate_hash_table_size_res calculate_hash_table_size(::fast_io::array<alias_parameter, N> const& ord) noexcept
    {
        constexpr auto sizet_d10{static_cast<::std::size_t>(::std::numeric_limits<::std::size_t>::digits10)};

        ::fast_io::crc32c_context crc32c{};
        for(auto i{hash_size_base}; i < sizet_d10; ++i)
        {
            ::std::size_t const hash_size{static_cast<::std::size_t>(1u) << i};
            bool c{};
            ::std::size_t extra_size{};
            ::std::size_t* const hash_size_array{::new ::std::size_t[hash_size]{}};
            for(auto const& j: ord)
            {
                ::std::size_t const j_str_size{j.str.size()};
                ::std::byte* const ptr{::new ::std::byte[j_str_size]{}};
                for(::std::size_t k{}; k < j_str_size; ++k) { ptr[k] = static_cast<::std::byte>(j.str.index_unchecked(k)); }
                crc32c.reset();
                crc32c.update(ptr, ptr + j_str_size);
                ::delete[] ptr;
                auto const val{crc32c.digest_value() % hash_size};
                ++hash_size_array[val];
                if(hash_size_array[val] == 2) { ++extra_size; }
                if(hash_size_array[val] > max_conflict_size) { c = true; }
            }

            ::delete[] hash_size_array;
            if(!c) { return {hash_size, extra_size}; }
        }
        // The conflict size has not been able to stay within the maximum conflict size, try changing the initial seed.
        ::fast_io::fast_terminate();
    }

    struct ht_para_cpos
    {
        ::fast_io::u8string_view str{};
        parameter const* para{};
    };

    using ct_para_str = alias_parameter;

    struct conflict_table
    {
        // Add one, store the last nullptr, to reduce the number of judgments when looking up
        ::fast_io::array<ct_para_str, max_conflict_size + 1> ctmem{};
    };

    template <::std::size_t hash_table_size, ::std::size_t conflict_size>
    struct parameters_hash_table
    {
        static_assert(hash_table_size > 1);
        // Hash Table
        ::fast_io::array<ht_para_cpos, hash_table_size> ht{};
        // Conflict Table
        ::std::conditional_t<static_cast<bool>(conflict_size), ::fast_io::array<conflict_table, conflict_size>, ::std::in_place_t> ct{};
    };

    /// @brief generate hash table
    template <::std::size_t hash_table_size, ::std::size_t conflict_size, ::std::size_t N>
    inline consteval auto generate_hash_table(::fast_io::array<alias_parameter, N> const& ord) noexcept
    {
        parameters_hash_table<hash_table_size, conflict_size> res{};

        ::fast_io::crc32c_context crc32c{};
        ::std::size_t conflictplace{1u};

        for(auto const& j: ord)
        {
            ::std::size_t const j_str_size{j.str.size()};
            ::std::byte* const ptr{::new ::std::byte[j_str_size]{}};
            for(::std::size_t k{}; k < j_str_size; ++k) { ptr[k] = static_cast<::std::byte>(j.str.index_unchecked(k)); }
            crc32c.reset();
            crc32c.update(ptr, ptr + j_str_size);
            ::delete[] ptr;
            auto const val{crc32c.digest_value() % hash_table_size};
            if constexpr(conflict_size)
            {
                if(res.ht.index_unchecked(val).para == nullptr)
                {
                    if(!res.ht.index_unchecked(val).str.empty())
                    {
                        // Write a conflict table backward.
                        for(auto& i: res.ct.index_unchecked(res.ht.index_unchecked(val).str.size() - 1).ctmem)
                        {
                            // Find an opening.
                            if(i.para == nullptr)
                            {
                                i.para = j.para;
                                i.str = j.str;
                                break;
                            }
                        }
                    }
                    else
                    {
                        // Without any conflict, this is the first
                        res.ht.index_unchecked(val).para = j.para;
                        res.ht.index_unchecked(val).str = j.str;
                    }
                }
                else
                {
                    // Move the data to the conflict table
                    res.ct.index_unchecked(conflictplace - 1).ctmem.front_unchecked().para = res.ht.index_unchecked(val).para;
                    res.ct.index_unchecked(conflictplace - 1).ctmem.front_unchecked().str = res.ht.index_unchecked(val).str;
                    res.ht.index_unchecked(val).para = nullptr;         // Mark this as no available
                    res.ht.index_unchecked(val).str.ptr = nullptr;      // Mark this as no available
                    res.ht.index_unchecked(val).str.n = conflictplace;  // Conflict Table Location
                    res.ct.index_unchecked(conflictplace - 1).ctmem.index_unchecked(1).para = j.para;
                    res.ct.index_unchecked(conflictplace - 1).ctmem.index_unchecked(1).str = j.str;
                    ++conflictplace;
                }
            }
            else
            {
                // No conflicts of any kind
                res.ht.index_unchecked(val).para = j.para;
                res.ht.index_unchecked(val).str = j.str;
            }
        }
        return res;
    }

    template <::std::size_t hash_table_size, ::std::size_t conflict_size>
    inline constexpr parameter const* find_from_hash_table(parameters_hash_table<hash_table_size, conflict_size> const& ght,
                                                           ::fast_io::u8string_view str) noexcept
    {
        ::fast_io::crc32c_context crc32c{};

        // calculate crc32c
        if UWVM_IF_CONSTEVAL
        {
            auto const str_size{str.size()};
            ::std::byte* const ptr{::new ::std::byte[str_size]{}};
            for(::std::size_t k{}; k < str_size; ++k) { ptr[k] = static_cast<::std::byte>(str.index_unchecked(k)); }
            crc32c.update(ptr, ptr + str_size);
            ::delete[] ptr;
        }
        else
        {
            auto const i{reinterpret_cast<::std::byte const*>(str.data())};
            crc32c.update(i, i + str.size());
        }

        // get hash table
        auto const val{crc32c.digest_value() % hash_table_size};
        auto const htval{ght.ht.index_unchecked(val)};

        if constexpr(conflict_size)
        {
            if(htval.para == nullptr)
            {
                if(!htval.str.empty()) [[likely]]
                {
                    // Get Conflict Table
                    auto const& ct{ght.ct.index_unchecked(htval.str.size() - 1).ctmem};
                    // Conflict table is always the last one is nullptr, here no longer judge cend, improve speed
                    for(auto curr_conflict{ct.cbegin()};; ++curr_conflict)
                    {
                        if(curr_conflict->str == str) { return curr_conflict->para; }
                        else if(curr_conflict->para == nullptr) [[unlikely]] { return nullptr; }
                    }
                    // If the above scenario is defined, there will never be a hit here.
                    ::fast_io::unreachable();
                }
                else [[unlikely]] { return nullptr; }
            }
            else
            {
                if(str == htval.str) [[likely]] { return htval.para; }
                else [[unlikely]] { return nullptr; }
            }
        }
        else
        {
            if(str == htval.str) [[likely]] { return htval.para; }
            else [[unlikely]] { return nullptr; }
        }
    }

}  // namespace utils::cmdline
