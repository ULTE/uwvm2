/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @brief       WebAssembly Release 1.0 (2019-07-20)
 * @details     antecedent dependency: null
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-26
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
import uwvm2.parser.wasm.base;
import uwvm2.parser.wasm.concepts;
import uwvm2.parser.wasm.standard.wasm1.type;
import uwvm2.parser.wasm.standard.wasm1.section;
import uwvm2.parser.wasm.standard.wasm1.opcode;
import uwvm2.parser.wasm.binfmt.binfmt_ver1;
import :def;
#else
// std
# include <cstddef>
# include <cstdint>
# include <concepts>
# include <type_traits>
# include <utility>
# include <memory>
// macro
# include <uwvm2/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/tuple.h>
# include <fast_io_dsal/vector.h>
# include <uwvm2/parser/wasm/base/impl.h>
# include <uwvm2/parser/wasm/concepts/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/section/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/opcode/impl.h>
# include <uwvm2/parser/wasm/binfmt/binfmt_ver1/impl.h>
# include "def.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::parser::wasm::standard::wasm1::features
{
    ///
    /// @brief Defining structures or concepts related to wasm1 versions
    ///

    ///////////////////////////
    /// @brief type section ///
    ///////////////////////////

    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    struct type_section_storage_t;

    /// @brief Define functions for checking value_type to provide extensibility
    template <typename... Fs>
    concept has_check_value_type = requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                            ::uwvm2::parser::wasm::standard::wasm1::features::final_value_type_t<Fs...> value_type) {
        { define_check_value_type(sec_adl, value_type) } -> ::std::same_as<bool>;
    };

    /// @brief Define functions to handle type prefix
    template <typename... Fs>
    concept has_type_prefix_handler = requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<type_section_storage_t<Fs...>> sec_adl,
                                               ::uwvm2::parser::wasm::standard::wasm1::features::final_type_prefix_t<Fs...> preifx,
                                               ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                                               ::std::byte const* section_curr,
                                               ::std::byte const* const section_end,
                                               ::uwvm2::parser::wasm::base::error_impl& err,
                                               ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
                                               ::std::byte const* const prefix_module_ptr) {
        {
            define_type_prefix_handler(sec_adl, preifx, module_storage, section_curr, section_end, err, fs_para, prefix_module_ptr)
        } -> ::std::same_as<::std::byte const*>;
    };

    /////////////////////////////
    /// @brief import section ///
    /////////////////////////////

    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    struct import_section_storage_t;

    /// @brief Define functions for handle extern_prefix
    template <typename... Fs>
    concept has_extern_prefix_imports_handler =
        requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<import_section_storage_t<Fs...>> sec_adl,
                 ::uwvm2::parser::wasm::standard::wasm1::features::final_import_type<Fs...>& fit,
                 ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_curr,
                 ::std::byte const* const section_end,
                 ::uwvm2::parser::wasm::base::error_impl& err,
                 ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para) {
            {
                define_extern_prefix_imports_handler(sec_adl, fit.imports, module_storage, section_curr, section_end, err, fs_para)
            } -> ::std::same_as<::std::byte const*>;
        };

    /// @brief Defining structures or concepts related to wasm versions
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    struct wasm1_final_extern_type
    {
        union storage_t
        {
            ::uwvm2::parser::wasm::standard::wasm1::features::final_function_type<Fs...> const* function;
            ::uwvm2::parser::wasm::standard::wasm1::features::final_table_type<Fs...> table;
            ::uwvm2::parser::wasm::standard::wasm1::features::final_memory_type<Fs...> memory;
            ::uwvm2::parser::wasm::standard::wasm1::features::final_global_type<Fs...> global;
        } storage;

        ::uwvm2::parser::wasm::standard::wasm1::type::external_types type{};
    };

    /// @brief Define functions for handle imports table
    template <typename... Fs>
    concept has_extern_imports_table_handler =
        requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<import_section_storage_t<Fs...>> sec_adl,
                 ::uwvm2::parser::wasm::standard::wasm1::features::wasm1_final_extern_type<Fs...>& fit_imports,
                 ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_curr,
                 ::std::byte const* const section_end,
                 ::uwvm2::parser::wasm::base::error_impl& err,
                 ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para) {
            {
                extern_imports_table_handler(sec_adl, fit_imports.storage.table, module_storage, section_curr, section_end, err, fs_para)
            } -> ::std::same_as<::std::byte const*>;
        };

    /// @brief Define functions for handle imports memory
    template <typename... Fs>
    concept has_extern_imports_memory_handler =
        requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<import_section_storage_t<Fs...>> sec_adl,
                 ::uwvm2::parser::wasm::standard::wasm1::features::wasm1_final_extern_type<Fs...>& fit_imports,
                 ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_curr,
                 ::std::byte const* const section_end,
                 ::uwvm2::parser::wasm::base::error_impl& err,
                 ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para) {
            {
                extern_imports_memory_handler(sec_adl, fit_imports.storage.memory, module_storage, section_curr, section_end, err, fs_para)
            } -> ::std::same_as<::std::byte const*>;
        };

    /// @brief Define functions for handle imports global
    template <typename... Fs>
    concept has_extern_imports_global_handler =
        requires(::uwvm2::parser::wasm::concepts::feature_reserve_type_t<import_section_storage_t<Fs...>> sec_adl,
                 ::uwvm2::parser::wasm::standard::wasm1::features::wasm1_final_extern_type<Fs...>& fit_imports,
                 ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
                 ::std::byte const* section_curr,
                 ::std::byte const* const section_end,
                 ::uwvm2::parser::wasm::base::error_impl& err,
                 ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para) {
            {
                extern_imports_global_handler(sec_adl, fit_imports.storage.global, module_storage, section_curr, section_end, err, fs_para)
            } -> ::std::same_as<::std::byte const*>;
        };

    // function_section
    static_assert(
        ::fast_io::freestanding::is_trivially_copyable_or_relocatable_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>> &&
            ::fast_io::freestanding::is_zero_default_constructible_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>> &&
            ::fast_io::freestanding::is_trivially_copyable_or_relocatable_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>> &&
            ::fast_io::freestanding::is_zero_default_constructible_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>> &&
            ::fast_io::freestanding::is_trivially_copyable_or_relocatable_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>> &&
            ::fast_io::freestanding::is_zero_default_constructible_v<::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>>,
        "::fast_io::vector is not trivially_copyable_or_relocatable or zero_default_constructible");

    enum class vectypeidx_minimize_storage_mode : unsigned
    {
        null,
        u8_view,
        u8_vector,
        u16_vector,
        u32_vector
    };

    struct typeidx_u8_view_t
    {
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8 const* begin{};
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8 const* end{};
    };

    template <typename... Ty>
    inline consteval ::std::size_t get_union_size() noexcept
    {
        ::std::size_t max_size{};
        [&max_size]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
        { ((max_size = ::std::max(max_size, sizeof(Ty...[I]))), ...); }(::std::make_index_sequence<sizeof...(Ty)>{});
        return max_size;
    }

    struct vectypeidx_minimize_storage_t UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
    {
        inline static constexpr ::std::size_t sizeof_vectypeidx_minimize_storage_u{
            get_union_size<typeidx_u8_view_t,
                           ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>,
                           ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>,
                           ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>>()};

        union vectypeidx_minimize_storage_u UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
        {
            typeidx_u8_view_t typeidx_u8_view;
            ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8> typeidx_u8_vector;
            ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16> typeidx_u16_vector;
            ::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32> typeidx_u32_vector;

            // Full occupancy is used to initialize the union, set the union to all zero.
            [[maybe_unused]] ::std::byte vectypeidx_minimize_storage_u_reserve[sizeof_vectypeidx_minimize_storage_u]{};

            // destructor of 'vectypeidx_minimize_storage_u' is implicitly deleted because variant field 'typeidx_u8_vector' has a non-trivial destructor
            inline constexpr ~vectypeidx_minimize_storage_u() {}
        };

        static_assert(sizeof(vectypeidx_minimize_storage_u) == sizeof_vectypeidx_minimize_storage_u,
                      "sizeof_vectypeidx_minimize_storage_u not equal to sizeof_vectypeidx_minimize_storage_u");

        vectypeidx_minimize_storage_u storage{};
        vectypeidx_minimize_storage_mode mode{};

        inline constexpr vectypeidx_minimize_storage_t() noexcept = default;  // all-zero

        inline constexpr vectypeidx_minimize_storage_t(vectypeidx_minimize_storage_t const& other) noexcept : mode{other.mode}
        {
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    // trivial
                    this->storage.typeidx_u8_view = other.storage.typeidx_u8_view;
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    // copy constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u8_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>{
                        other.storage.typeidx_u8_vector};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    // copy constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u16_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>{
                        other.storage.typeidx_u16_vector};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    // copy constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u32_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>{
                        other.storage.typeidx_u32_vector};
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline constexpr vectypeidx_minimize_storage_t(vectypeidx_minimize_storage_t&& other) noexcept : mode{other.mode}
        {
            // Since fast_io::vector satisfies both is_trivially_copyable_or_relocatable and is_zero_default_constructible, it is possible to do this
            other.mode = {};  // set to u8_view

            // move data
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    // trivial
                    this->storage.typeidx_u8_view = ::std::move(other.storage.typeidx_u8_view);
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    // move constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u8_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>{
                        ::std::move(other.storage.typeidx_u8_vector)};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    // move constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u16_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>{
                        ::std::move(other.storage.typeidx_u16_vector)};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    // move constructor, placement new
                    ::new(::std::addressof(this->storage.typeidx_u32_vector))::fast_io::vector<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>{
                        ::std::move(other.storage.typeidx_u32_vector)};
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline constexpr vectypeidx_minimize_storage_t& operator= (vectypeidx_minimize_storage_t const& other) noexcept
        {
            if(::std::addressof(other) == this) [[unlikely]] { return *this; }

            clear_destroy();

            this->mode = other.mode;

            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    this->storage.typeidx_u8_view = other.storage.typeidx_u8_view;
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    this->storage.typeidx_u8_vector = other.storage.typeidx_u8_vector;
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    this->storage.typeidx_u16_vector = other.storage.typeidx_u16_vector;
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    this->storage.typeidx_u32_vector = other.storage.typeidx_u32_vector;
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }

            return *this;
        }

        inline constexpr vectypeidx_minimize_storage_t& operator= (vectypeidx_minimize_storage_t&& other) noexcept
        {
            if(::std::addressof(other) == this) [[unlikely]] { return *this; }

            clear_destroy();

            // Since fast_io::vector satisfies both is_trivially_copyable_or_relocatable and is_zero_default_constructible, it is possible to do this

            this->mode = other.mode;

            other.mode = {};  // set to u8_view

            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    this->storage.typeidx_u8_view = ::std::move(other.storage.typeidx_u8_view);
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    this->storage.typeidx_u8_vector = ::std::move(other.storage.typeidx_u8_vector);
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    this->storage.typeidx_u16_vector = ::std::move(other.storage.typeidx_u16_vector);
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    this->storage.typeidx_u32_vector = ::std::move(other.storage.typeidx_u32_vector);
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }

            return *this;
        }

        inline constexpr ~vectypeidx_minimize_storage_t() { clear_destroy(); }

        inline constexpr void clear_destroy() noexcept
        {
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    this->storage.typeidx_u8_view = {};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    this->storage.typeidx_u8_vector.clear_destroy();
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    this->storage.typeidx_u16_vector.clear_destroy();
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    this->storage.typeidx_u32_vector.clear_destroy();
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }

            this->mode = {};
        }

        inline constexpr void clear() noexcept
        {
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    this->storage.typeidx_u8_view = {};
                    break;
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    this->storage.typeidx_u8_vector.clear();
                    break;
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    this->storage.typeidx_u16_vector.clear();
                    break;
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    this->storage.typeidx_u32_vector.clear();
                    break;
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline constexpr ::std::size_t size() noexcept
        {
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    return 0;
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    return static_cast<::std::size_t>(this->storage.typeidx_u8_view.end - this->storage.typeidx_u8_view.begin);
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    return this->storage.typeidx_u8_vector.size();
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    return this->storage.typeidx_u16_vector.size();
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    return this->storage.typeidx_u32_vector.size();
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 index_unchecked(::std::size_t sz) noexcept
        {
            switch(this->mode)
            {
                [[unlikely]] case vectypeidx_minimize_storage_mode::null:
                {
                    return static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(-1);
                }
                case vectypeidx_minimize_storage_mode::u8_view:
                {
                    return static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(this->storage.typeidx_u8_view.begin[sz]);
                }
                case vectypeidx_minimize_storage_mode::u8_vector:
                {
                    return static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(this->storage.typeidx_u8_vector.index_unchecked(sz));
                }
                case vectypeidx_minimize_storage_mode::u16_vector:
                {
                    return static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(this->storage.typeidx_u16_vector.index_unchecked(sz));
                }
                case vectypeidx_minimize_storage_mode::u32_vector:
                {
                    return this->storage.typeidx_u32_vector.index_unchecked(sz);
                }
                [[unlikely]] default:
                {
                    ::fast_io::fast_terminate();
                }
            }
        }

        inline constexpr void change_mode(vectypeidx_minimize_storage_mode mode) noexcept
        {
            // chang mode need destroy first
            clear_destroy();
            this->mode = mode;
            // Because the fast_io vector is constructed with all zeros, there is no need to do any constructor operations
        }
    };

}  // namespace uwvm2::parser::wasm::standard::wasm1::features

UWVM_MODULE_EXPORT namespace fast_io::freestanding
{
    template <>
    struct is_trivially_copyable_or_relocatable<::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_t>
    {
        inline static constexpr bool value = true;
    };

    template <>
    struct is_zero_default_constructible<::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_t>
    {
        inline static constexpr bool value = true;
    };
}

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif
