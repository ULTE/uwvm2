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
 * @date        2025-05-07
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
# ifdef UWVM_TIMER
import uwvm2.utils.debug;
# endif
import uwvm2.utils.intrinsics;
import uwvm2.parser.wasm.base;
import uwvm2.parser.wasm.concepts;
import uwvm2.parser.wasm.standard.wasm1.type;
import uwvm2.parser.wasm.standard.wasm1.section;
import uwvm2.parser.wasm.standard.wasm1.opcode;
import uwvm2.parser.wasm.binfmt.binfmt_ver1;
import :def;
import :types;
import :feature_def;
import :type_section;
#else
// std
# include <cstddef>
# include <cstdint>
# include <concepts>
# include <type_traits>
# include <utility>
# include <memory>
# include <bit>
# if (defined(_MSC_VER) && !defined(__clang__)) && !defined(_KERNEL_MODE) && defined(_M_AMD64)
#  include <emmintrin.h>  // MSVC x86_64-SSE2
# endif
# if (defined(_MSC_VER) && !defined(__clang__)) && !defined(_KERNEL_MODE) && defined(_M_ARM64)
#  include <arm_neon.h>  // MSVC aarch64-NEON
# endif
// macro
# include <uwvm2/utils/macro/push_macros.h>
// import
# include <fast_io.h>
# include <fast_io_dsal/array.h>
# include <fast_io_dsal/vector.h>
# include <fast_io_dsal/string_view.h>
# ifdef UWVM_TIMER
#  include <uwvm2/utils/debug/impl.h>
# endif
# include <uwvm2/utils/intrinsics/impl.h>
# include <uwvm2/parser/wasm/base/impl.h>
# include <uwvm2/parser/wasm/concepts/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/section/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/opcode/impl.h>
# include <uwvm2/parser/wasm/binfmt/binfmt_ver1/impl.h>
# include "def.h"
# include "types.h"
# include "feature_def.h"
# include "type_section.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm2::parser::wasm::standard::wasm1::features
{
    struct function_section_storage_t UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
    {
        inline static constexpr ::fast_io::u8string_view section_name{u8"Function"};
        inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte section_id{
            static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(::uwvm2::parser::wasm::standard::wasm1::section::section_id::function_sec)};

        ::uwvm2::parser::wasm::standard::wasm1::section::section_span_view sec_span{};

        ::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_t funcs{};
    };

    /// @brief      Convert view to vec
    /// @param      func_counter The correct u8 size has been processed
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr ::std::byte const* change_u8_1b_view_to_vec(
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_reserve_type_t<function_section_storage_t> sec_adl,
        ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
        ::std::byte const* section_curr,
        ::std::byte const* const section_end,
        ::uwvm2::parser::wasm::base::error_impl& err,
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32& func_counter,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 const func_count) UWVM_THROWS
    {
        auto const& typesec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};
        auto const type_section_count{static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(typesec.types.size())};

#if __has_cpp_attribute(assume)
        [[assume(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 7u)]];
#endif

        auto& functionsec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<function_section_storage_t>(module_storage.sections)};

        // Storing a typeidx takes 1 bytes, change u8view to u8_vector
        functionsec.funcs.change_mode(::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_mode::u8_vector);

        // The size comparison between u32 and size_t has already been checked
        functionsec.funcs.storage.typeidx_u8_vector.reserve(static_cast<::std::size_t>(func_count));

        static_assert(sizeof(::std::byte) == sizeof(::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8));

        // Copy the situation that has been processed correctly
        ::fast_io::freestanding::my_memcpy(functionsec.funcs.storage.typeidx_u8_vector.imp.curr_ptr, section_curr - func_counter, func_counter);
        functionsec.funcs.storage.typeidx_u8_vector.imp.curr_ptr += func_counter;

        // [typeidxbef ...] typeidx1 ... typeidx2 ...
        // [     safe     ] unsafe (could be the section_end)
        //                  ^^ section_curr

        while(section_curr != section_end) [[likely]]
        {
            // Ensuring the existence of valid information

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check function counter
            // Ensure content is available before counting (section_curr != section_end)
            if(++func_counter > func_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = func_count;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 typeidx;  // No initialization necessary

            using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

            auto const [typeidx_next, typeidx_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                            reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                            ::fast_io::mnp::leb128_get(typeidx))};

            if(typeidx_err != ::fast_io::parse_code::ok) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::invalid_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(typeidx_err);
            }

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check: type_index should less than type_section_count
            if(typeidx >= type_section_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = typeidx;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::illegal_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            functionsec.funcs.storage.typeidx_u8_vector.emplace_back_unchecked(static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8>(typeidx));

            section_curr = reinterpret_cast<::std::byte const*>(typeidx_next);

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //                     ^^ section_curr
        }

        // [before_section ... | func_count ... typeidx1 ... ...] (end)
        // [                       safe                         ] unsafe (could be the section_end)
        //                                                        ^^ section_curr

        return section_curr;
    }

    /// @brief      Maximum typeidx in [0, 2^7)
    /// @details    Storing a typeidx takes up 1 bytes, typeidx corresponding uleb128 varies from 1 bytes, linear read/write, no simd optimization
    ///             Sequential scanning, correctly handling all cases of uleb128 u32, allowing up to 5 bytes.
    ///
    ///             According to the characteristics of wasm, wasm-ld will try to avoid redundancy 0 allowed by uleb128, so basically all cases are one byte,
    ///             this time we only need to check whether they are all 1 byte, and no more than typeidx, the total length matches, to meet these points can be
    ///             used directly to view to avoid copying, and you can simd parallel computation and writing. In rare cases, such as the user to modify the
    ///             wasm file, or wasm-ld does not use the least byte representation, encounter redundancy 0, uleb128<u32> will appear to be greater than 1 byte
    ///             in length, but meets the standard, this time it will be allocated space and the previous contents of the memcpy to the space, and then
    ///             continue to read to ensure that the subsequent access to ensure that access can be accessed through the index directly to the This will
    ///             increase the scanning time.
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr ::std::byte const* scan_function_section_impl_u8_1b(
        ::uwvm2::parser::wasm::concepts::feature_reserve_type_t<function_section_storage_t> sec_adl,
        ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
        ::std::byte const* section_curr,
        ::std::byte const* const section_end,
        ::uwvm2::parser::wasm::base::error_impl& err,
        ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32& func_counter,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 const func_count) UWVM_THROWS
    {
        auto const& typesec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};
        auto const type_section_count{static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(typesec.types.size())};

#if __has_cpp_attribute(assume)
        [[assume(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 7u)]];
#endif

        auto& functionsec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<function_section_storage_t>(module_storage.sections)};

        // used directly to u8 view to avoid copying
        functionsec.funcs.mode = ::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_mode::u8_view;

        // set view begin
        using wasm_u8_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u8 const*;
        functionsec.funcs.storage.typeidx_u8_view.begin = reinterpret_cast<wasm_u8_const_may_alias_ptr>(section_curr);

#if (defined(_MSC_VER) && !defined(__clang__)) && !defined(_KERNEL_MODE) && (defined(_M_AMD64) || defined(_M_ARM64))
        /// (Little Endian), MSVC, ::fast_io::intrinsics::simd_vector
        /// x86_64-sse2, aarch64-neon
        /// @todo need check

        static_assert(::std::same_as<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte, ::std::uint8_t>);

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const simd_vector_check{
            static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(type_section_count)};

        // use fast_io simd on msvc
        using simd128_t = ::fast_io::intrinsics::simd_vector<::std::uint8_t, 16uz>;

        simd128_t const simd_vector_check_u8x16{simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check,
                                                simd_vector_check};

        while(static_cast<::std::size_t>(section_end - section_curr) >= 16uz) [[likely]]
        {
            // [before_section ... | func_count ... typeidx1 ... (15) ...] ...
            // [                        safe                             ] unsafe (could be the section_end)
            //                                      ^^ section_curr
            //                                      [   simd_vector_str  ]

            simd128_t simd_vector_str;  // No initialization necessary

            simd_vector_str.load(section_curr);

            // It's already a little-endian.

            auto const check_upper{simd_vector_str >= simd_vector_check_u8x16};

            if(!is_all_zeros(check_upper)) [[unlikely]]
            {
                // There are special cases greater than typeidx, which may be legal redundancy 0 or illegal data, all converted to vec to determine.
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }
            else
            {
                // all are single bytes, so there are 16
                // There is no need to staging func_counter_this_round_end, as the special case no longer exists.
                func_counter += 16u;

                // check counter
                if(func_counter > func_count) [[unlikely]]
                {
                    err.err_curr = section_curr;
                    err.err_selectable.u32 = func_count;
                    err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                    ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }

                section_curr += 16uz;

                // [before_section ... | func_count ... typeidx1 ... (15) ...] typeidx16
                // [                        safe                             ] unsafe (could be the section_end)
                //                                                             ^^ section_curr
            }
        }

#elif defined(__LITTLE_ENDIAN__) && (defined(__ARM_FEATURE_SVE) || defined(__ARM_FEATURE_SME))
        /// (Little Endian) Variable Length
        /// mask: aarch64-sve
        /// @todo need check

        // Support for certain cpu's that don't have SVE but have SME like apple m4
        [&]
# if defined(__ARM_FEATURE_SME) && !defined(__ARM_FEATURE_SVE)
            __arm_locally_streaming
# endif
            () constexpr noexcept -> void
        {
            static_assert(::std::same_as<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte, ::std::uint8_t>);

            ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const simd_vector_check{
                static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(type_section_count)};

            auto const all_one_predicate_reg{::uwvm2::utils::intrinsics::arm_sve::svptrue_b8()};
            auto const svc_sz{::uwvm2::utils::intrinsics::arm_sve::svcntb()};

            while(static_cast<::std::size_t>(section_end - section_curr) >= svc_sz) [[likely]]
            {
                // [before_section ... | func_count ... typeidx1 ... (svc_sz - 1) ...] ...
                // [                        safe                                     ] unsafe (could be the section_end)
                //                                      ^^ section_curr
                //                                      [       simd_vector_str      ]

                using uint8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::std::uint8_t const*;

                // The entire sve can be loaded
                auto const simd_vector_str{
                    ::uwvm2::utils::intrinsics::arm_sve::svld1_u8(all_one_predicate_reg, reinterpret_cast<uint8_t_const_may_alias_ptr>(section_curr))};

                auto const check_upper{::uwvm2::utils::intrinsics::arm_sve::svcmpge_n_u8(all_one_predicate_reg, simd_vector_str, simd_vector_check)};

                if(::uwvm2::utils::intrinsics::arm_sve::svptest_any(all_one_predicate_reg, check_upper)) [[unlikely]]
                {
                    return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
                }
                else
                {
                    // all are single bytes, so there are 64
                    // There is no need to staging func_counter_this_round_end, as the special case no longer exists.
                    func_counter += svc_sz;

                    // check counter
                    if(func_counter > func_count) [[unlikely]]
                    {
                        err.err_curr = section_curr;
                        err.err_selectable.u32 = func_count;
                        err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                        ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                    }

                    section_curr += svc_sz;

                    // [before_section ... | func_count ... typeidx1 ... (svc_sz - 1) ...] typeidx64
                    // [                        safe                                     ] unsafe (could be the section_end)
                    //                                                                     ^^ section_curr
                }
            }

            // [before_section ... | func_count ... typeidx1 ... (svc_sz - 1) ...] typeidx64 ... (?) ... ] (end)
            // [                        safe                                                             ] unsafe (could be the section_end)
            //                                                                     ^^ section_curr
            //
            // Or maybe:
            //
            // [before_section ... | func_count ... typeidx1 ... (svc_sz - 1) ...] (end)
            // [                        safe                                     ] unsafe (could be the section_end)
            //                                                                     ^^ section_curr

            // Generate quantifiers for final tail processing
            svbool_t load_predicate;  // No initialization necessary

            if constexpr(sizeof(::std::byte const*) == sizeof(::std::uint64_t))
            {
                load_predicate = ::uwvm2::utils::intrinsics::arm_sve::svwhilelt_b8_u64(::std::bit_cast<::std::uint64_t>(section_curr),
                                                                                       ::std::bit_cast<::std::uint64_t>(section_end));
            }
            else
            {
                load_predicate = ::uwvm2::utils::intrinsics::arm_sve::svwhilelt_b8_u32(::std::bit_cast<::std::uint32_t>(section_curr),
                                                                                       ::std::bit_cast<::std::uint32_t>(section_end));
            }

            // sve safely loads memory via predicates
            auto const simd_vector_str{
                ::uwvm2::utils::intrinsics::arm_sve::svld1_u8(load_predicate, reinterpret_cast<uint8_t_const_may_alias_ptr>(section_curr))};

            auto const check_upper{::uwvm2::utils::intrinsics::arm_sve::svcmpge_n_u8(load_predicate, simd_vector_str, simd_vector_check)};

            if(::uwvm2::utils::intrinsics::arm_sve::svptest_any(load_predicate, check_upper)) [[unlikely]]
            {
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }
            else
            {
                using uint8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::std::uint8_t const*;

                auto const last_load_predicate_size{static_cast<::std::size_t>(reinterpret_cast<uint8_t_const_may_alias_ptr>(section_end) -
                                                                               reinterpret_cast<uint8_t_const_may_alias_ptr>(section_curr))};

                // all are single bytes, so there are 64
                // There is no need to staging func_counter_this_round_end, as the special case no longer exists.
                func_counter += last_load_predicate_size;

                // check counter
                if(func_counter > func_count) [[unlikely]]
                {
                    err.err_curr = section_curr;
                    err.err_selectable.u32 = func_count;
                    err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                    ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }

                section_curr += last_load_predicate_size;

                // [before_section ... | func_count ... typeidx1 ... (last_load_predicate_size - 1) ...] (end)
                // [                        safe                                                       ] unsafe (could be the section_end)
                //                                                                                       ^^ section_curr
            }
        }
        ();

#elif __has_cpp_attribute(__gnu__::__vector_size__) && defined(__LITTLE_ENDIAN__) && UWVM_HAS_BUILTIN(__builtin_shufflevector) &&                              \
    (defined(__AVX512BW__) && (UWVM_HAS_BUILTIN(__builtin_ia32_ptestmb512) || UWVM_HAS_BUILTIN(__builtin_ia32_cmpb512_mask)))
        /// (Little Endian)
        /// mask: x86_64-avx512vbmi
        /// @todo need check

        using i64x8simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = ::std::int64_t;
        using u64x8simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = ::std::uint64_t;
        using u32x16simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = ::std::uint32_t;
        using c8x64simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = char;
        using u8x64simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = ::std::uint8_t;
        using i8x64simd [[__gnu__::__vector_size__(64)]] [[maybe_unused]] = ::std::int8_t;

        static_assert(::std::same_as<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte, ::std::uint8_t>);

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const simd_vector_check{
            static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(type_section_count)};

        while(static_cast<::std::size_t>(section_end - section_curr) >= 64uz) [[likely]]
        {
            // [before_section ... | func_count ... typeidx1 ... (63) ...] ...
            // [                        safe                             ] unsafe (could be the section_end)
            //                                      ^^ section_curr
            //                                      [   simd_vector_str  ]

            u8x64simd simd_vector_str;  // No initialization necessary

            ::fast_io::freestanding::my_memcpy(::std::addressof(simd_vector_str), section_curr, sizeof(u8x64simd));

            // It's already a little-endian.

            auto const check_upper{simd_vector_str >= simd_vector_check};

            if(
# if defined(__AVX512BW__) && UWVM_HAS_BUILTIN(__builtin_ia32_ptestmb512)  // Only supported by GCC
                // gcc:
                // vptestmb        k0, zmm0, zmm0
                // kortestq        k0, k0
                // sete    al
                __builtin_ia32_ptestmb512(::std::bit_cast<c8x64simd>(check_upper), ::std::bit_cast<c8x64simd>(check_upper), UINT64_MAX)
# elif defined(__AVX512BW__) && UWVM_HAS_BUILTIN(__builtin_ia32_cmpb512_mask)
                // clang:
                // vptestmd        k0, zmm0, zmm0
                // kortestw        k0, k0
                // setne   al
                // vzeroupper
                //
                // gcc:
                // vpxor   xmm1, xmm1, xmm1
                // vpcmpb  k0, zmm0, zmm1, 4
                // kortestq        k0, k0
                // setne   al
                __builtin_ia32_cmpb512_mask(::std::bit_cast<c8x64simd>(check_upper), c8x64simd{}, 0x04, UINT64_MAX)
# endif
                    ) [[unlikely]]
            {
                // There are special cases greater than typeidx, which may be legal redundancy 0 or illegal data, all converted to vec to determine.
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }
            else
            {
                // all are single bytes, so there are 64
                // There is no need to staging func_counter_this_round_end, as the special case no longer exists.
                func_counter += 64u;

                // check counter
                if(func_counter > func_count) [[unlikely]]
                {
                    err.err_curr = section_curr;
                    err.err_selectable.u32 = func_count;
                    err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                    ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }

                section_curr += 64uz;

                // [before_section ... | func_count ... typeidx1 ... (63) ...] typeidx64
                // [                        safe                             ] unsafe (could be the section_end)
                //                                                             ^^ section_curr
            }
        }

#elif __has_cpp_attribute(__gnu__::__vector_size__) && defined(__LITTLE_ENDIAN__) && UWVM_HAS_BUILTIN(__builtin_shufflevector) &&                              \
    ((defined(__AVX__) && UWVM_HAS_BUILTIN(__builtin_ia32_ptestz256)) || (defined(__loongarch_asx) && UWVM_HAS_BUILTIN(__builtin_lasx_xbnz_v)))
        /// (Little Endian), [[gnu::vector_size]]
        /// mask: x86_64-avx, loongarch-ASX

        using i64x4simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = ::std::int64_t;
        using u64x4simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = ::std::uint64_t;
        using u32x8simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = ::std::uint32_t;
        using c8x32simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = char;
        using u8x32simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = ::std::uint8_t;
        using i8x32simd [[__gnu__::__vector_size__(32)]] [[maybe_unused]] = ::std::int8_t;

        static_assert(::std::same_as<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte, ::std::uint8_t>);

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const simd_vector_check{
            static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(type_section_count)};

        while(static_cast<::std::size_t>(section_end - section_curr) >= 32uz) [[likely]]
        {
            // [before_section ... | func_count ... typeidx1 ... (31) ...] ...
            // [                        safe                             ] unsafe (could be the section_end)
            //                                      ^^ section_curr
            //                                      [   simd_vector_str  ]

            u8x32simd simd_vector_str;  // No initialization necessary

            ::fast_io::freestanding::my_memcpy(::std::addressof(simd_vector_str), section_curr, sizeof(u8x32simd));

            // It's already a little-endian.

            auto const check_upper{simd_vector_str >= simd_vector_check};

            if(
# if defined(__AVX__) && UWVM_HAS_BUILTIN(__builtin_ia32_ptestz256)
                !__builtin_ia32_ptestz256(::std::bit_cast<i64x4simd>(check_upper), ::std::bit_cast<i64x4simd>(check_upper))
# elif defined(__loongarch_asx) && UWVM_HAS_BUILTIN(__builtin_lasx_xbnz_v)
                __builtin_lasx_xbnz_v(::std::bit_cast<u8x32simd>(check_upper))  /// @todo need check
# endif
                    ) [[unlikely]]
            {
                // There are special cases greater than typeidx, which may be legal redundancy 0 or illegal data, all converted to vec to determine.
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }
            else
            {
                // all are single bytes, so there are 32
                func_counter += 32u;

                // check counter
                if(func_counter > func_count) [[unlikely]]
                {
                    err.err_curr = section_curr;
                    err.err_selectable.u32 = func_count;
                    err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                    ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }

                section_curr += 32uz;

                // [before_section ... | func_count ... typeidx1 ... (31) ...] typeidx32
                // [                        safe                             ] unsafe (could be the section_end)
                //                                                             ^^ section_curr
            }
        }

#elif __has_cpp_attribute(__gnu__::__vector_size__) && defined(__LITTLE_ENDIAN__) &&                                                                           \
    ((defined(__SSE2__) && UWVM_HAS_BUILTIN(__builtin_ia32_pmovmskb128)) || (defined(__ARM_NEON) && UWVM_HAS_BUILTIN(__builtin_neon_vmaxvq_u32)) ||            \
     (defined(__ARM_NEON) && UWVM_HAS_BUILTIN(__builtin_aarch64_reduc_umax_scal_v4si_uu)) ||                                                                   \
     (defined(__loongarch_sx) && UWVM_HAS_BUILTIN(__builtin_lsx_bnz_v)) || (defined(__wasm_simd128__) && UWVM_HAS_BUILTIN(__builtin_wasm_bitmask_i8x16)))
        /// (Little Endian), [[gnu::vector_size]]
        /// x86_64-sse2, aarch64-neon, loongarch-SX, wasm-wasmsimd128

        using i64x2simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = ::std::int64_t;
        using u64x2simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = ::std::uint64_t;
        using u32x4simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = ::std::uint32_t;
        using c8x16simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = char;
        using u8x16simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = ::std::uint8_t;
        using i8x16simd [[__gnu__::__vector_size__(16)]] [[maybe_unused]] = ::std::int8_t;

        static_assert(::std::same_as<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte, ::std::uint8_t>);

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const simd_vector_check{
            static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte>(type_section_count)};

        while(static_cast<::std::size_t>(section_end - section_curr) >= 16uz) [[likely]]
        {
            // [before_section ... | func_count ... typeidx1 ... (15) ...] ...
            // [                        safe                             ] unsafe (could be the section_end)
            //                                      ^^ section_curr
            //                                      [   simd_vector_str  ]

            u8x16simd simd_vector_str;  // No initialization necessary

            ::fast_io::freestanding::my_memcpy(::std::addressof(simd_vector_str), section_curr, sizeof(u8x16simd));

            // It's already a little-endian.

            auto const check_upper{simd_vector_str >= simd_vector_check};

            if(
# if defined(__SSE4_1__) && UWVM_HAS_BUILTIN(__builtin_ia32_ptestz128)
                !__builtin_ia32_ptestz128(::std::bit_cast<i64x2simd>(check_upper), ::std::bit_cast<i64x2simd>(check_upper))
# elif defined(__SSE2__) && UWVM_HAS_BUILTIN(__builtin_ia32_pmovmskb128)
                __builtin_ia32_pmovmskb128(::std::bit_cast<c8x16simd>(check_upper))
# elif defined(__wasm_simd128__) && UWVM_HAS_BUILTIN(__builtin_wasm_all_true_i8x16)
                !__builtin_wasm_all_true_i8x16(::std::bit_cast<i8x16simd>(~check_upper))
# elif defined(__wasm_simd128__) && UWVM_HAS_BUILTIN(__builtin_wasm_bitmask_i8x16)
                __builtin_wasm_bitmask_i8x16(::std::bit_cast<i8x16simd>(check_upper))
# elif defined(__ARM_NEON) && UWVM_HAS_BUILTIN(__builtin_neon_vmaxvq_u32)                  // Only supported by clang
                __builtin_neon_vmaxvq_u32(::std::bit_cast<u32x4simd>(check_upper))
# elif defined(__ARM_NEON) && UWVM_HAS_BUILTIN(__builtin_aarch64_reduc_umax_scal_v4si_uu)  // Only supported by GCC
                __builtin_aarch64_reduc_umax_scal_v4si_uu(::std::bit_cast<u32x4simd>(check_upper))
# elif defined(__loongarch_sx) && UWVM_HAS_BUILTIN(__builtin_lsx_bnz_v)
                __builtin_lsx_bnz_v(::std::bit_cast<u8x16simd>(check_upper))  /// @todo need check
# endif
                    ) [[unlikely]]
            {
                // There are special cases greater than typeidx, which may be legal redundancy 0 or illegal data, all converted to vec to determine.
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }
            else
            {
                // all are single bytes, so there are 16
                func_counter += 16u;

                // check counter
                if(func_counter > func_count) [[unlikely]]
                {
                    err.err_curr = section_curr;
                    err.err_selectable.u32 = func_count;
                    err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                    ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
                }

                section_curr += 16uz;

                // [before_section ... | func_count ... typeidx1 ... (15) ...] typeidx16
                // [                        safe                             ] unsafe (could be the section_end)
                //                                                             ^^ section_curr
            }
        }
#endif

#if ((defined(_MSC_VER) && !defined(__clang__)) && !defined(_KERNEL_MODE) && (defined(_M_AMD64) || defined(_M_ARM64))) ||                                      \
    !(defined(__LITTLE_ENDIAN__) && (defined(__ARM_FEATURE_SVE) || defined(__ARM_FEATURE_SME)))
        // non-simd or simd (non-sve) tail-treatment
        // msvc, non-sve, default
        // arm-sve no tail treatment required

        while(section_curr != section_end) [[likely]]
        {
            // Ensuring the existence of valid information

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            // This needs to be judged first before setting the value, to ensure that the special case call view_to_vec can get the correct function_counter
            // Need to stash func_counter_this_round_end because special cases are not yet handled
            auto const func_counter_this_round_end{func_counter + 1u};

            // check function counter
            // Ensure content is available before counting (section_curr != section_end)
            if(func_counter_this_round_end > func_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = func_count;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 typeidx;  // No initialization necessary

            using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

            auto const [typeidx_next, typeidx_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                            reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                            ::fast_io::mnp::leb128_get(typeidx))};

            if(typeidx_err != ::fast_io::parse_code::ok) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::invalid_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(typeidx_err);
            }

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check: type_index should less than type_section_count
            if(typeidx >= type_section_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = typeidx;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::illegal_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            // Check for the presence of redundant 0, (check single byte)
            if(static_cast<::std::size_t>(reinterpret_cast<::std::byte const*>(typeidx_next) - section_curr) > 1uz) [[unlikely]]
            {
                return change_u8_1b_view_to_vec(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
            }

            section_curr = reinterpret_cast<::std::byte const*>(typeidx_next);

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //                     ^^ section_curr

            // Processed and returned to stock. Special cases processed.
            func_counter = func_counter_this_round_end;
        }
#endif

        // set view end
        functionsec.funcs.storage.typeidx_u8_view.end = reinterpret_cast<wasm_u8_const_may_alias_ptr>(section_curr);

        return section_curr;
    }

    /// @brief      Maximum typeidx in [2^14, 2^16)
    /// @details    Storing a typeidx takes up 2 bytes, typeidx corresponding uleb128 varies from 1-3 bytes, linear read/write, no simd optimization
    ///             Sequential scanning, correctly handling all cases of uleb128 u32, allowing up to 5 bytes.
    ///             simd has basically no advantage in this area of processing
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr ::std::byte const* scan_function_section_impl_u16_3b(
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_reserve_type_t<function_section_storage_t> sec_adl,
        ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
        ::std::byte const* section_curr,
        ::std::byte const* const section_end,
        ::uwvm2::parser::wasm::base::error_impl& err,
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32& func_counter,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 const func_count) UWVM_THROWS
    {
        auto const& typesec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};
        auto const type_section_count{static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(typesec.types.size())};

#if __has_cpp_attribute(assume)
        [[assume(type_section_count >= static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 14u &&
                 type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 16u)]];
#endif

        auto& functionsec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<function_section_storage_t>(module_storage.sections)};

        // Storing a typeidx takes up 2 bytes, use u16_vector
        functionsec.funcs.mode = ::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_mode::u16_vector;

        // The size comparison between u32 and size_t has already been checked
        functionsec.funcs.storage.typeidx_u16_vector.reserve(static_cast<::std::size_t>(func_count));

        // [before_section ... | func_count ...] typeidx1 ... typeidx2 ...
        // [              safe                 ] unsafe (could be the section_end)
        //                                       ^^ section_curr

        while(section_curr != section_end) [[likely]]
        {
            // Ensuring the existence of valid information

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check function counter
            // Ensure content is available before counting (section_curr != section_end)
            if(++func_counter > func_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = func_count;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 typeidx;  // No initialization necessary

            using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

            auto const [typeidx_next, typeidx_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                            reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                            ::fast_io::mnp::leb128_get(typeidx))};

            if(typeidx_err != ::fast_io::parse_code::ok) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::invalid_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(typeidx_err);
            }

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check: type_index should less than type_section_count
            if(typeidx >= type_section_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = typeidx;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::illegal_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            functionsec.funcs.storage.typeidx_u16_vector.emplace_back_unchecked(static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u16>(typeidx));

            section_curr = reinterpret_cast<::std::byte const*>(typeidx_next);

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //                     ^^ section_curr
        }

        // [before_section ... | func_count ... typeidx1 ... ...] (end)
        // [                       safe                         ] unsafe (could be the section_end)
        //                                                        ^^ section_curr

        return section_curr;
    }

    /// @brief      Maximum typeidx in [2^16, 2^32)
    /// @details    Storing a typeidx takes up 4 bytes, typeidx corresponding uleb128 varies from 1-5 bytes, linear read/write, no simd optimization
    ///             Sequential scanning, correctly handling all cases of uleb128 u32, allowing up to 5 bytes.
    ///             simd has basically no advantage in this area of processing
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr ::std::byte const* scan_function_section_impl_u32_5b(
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_reserve_type_t<function_section_storage_t> sec_adl,
        ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
        ::std::byte const* section_curr,
        ::std::byte const* const section_end,
        ::uwvm2::parser::wasm::base::error_impl& err,
        [[maybe_unused]] ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32& func_counter,
        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 const func_count) UWVM_THROWS
    {
        auto const& typesec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};
        auto const type_section_count{static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(typesec.types.size())};

#if __has_cpp_attribute(assume)
        [[assume(type_section_count >= static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 16u)]];
#endif

        auto& functionsec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<function_section_storage_t>(module_storage.sections)};

        // Storing a typeidx takes up 4 bytes, use u32_vector
        functionsec.funcs.mode = ::uwvm2::parser::wasm::standard::wasm1::features::vectypeidx_minimize_storage_mode::u32_vector;

        // The size comparison between u32 and size_t has already been checked
        functionsec.funcs.storage.typeidx_u32_vector.reserve(static_cast<::std::size_t>(func_count));

        // [before_section ... | func_count ...] typeidx1 ... typeidx2 ...
        // [              safe                 ] unsafe (could be the section_end)
        //                                       ^^ section_curr

        while(section_curr != section_end) [[likely]]
        {
            // Ensuring the existence of valid information

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check function counter
            // Ensure content is available before counting (section_curr != section_end)
            if(++func_counter > func_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = func_count;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_exceeded_the_actual_number;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            // [ ... typeidx1] ... typeidx2 ...
            // [     safe    ] unsafe (could be the section_end)
            //       ^^ section_curr

            ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 typeidx;  // No initialization necessary

            using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

            auto const [typeidx_next, typeidx_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                            reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                            ::fast_io::mnp::leb128_get(typeidx))};

            if(typeidx_err != ::fast_io::parse_code::ok) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::invalid_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(typeidx_err);
            }

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //       ^^ section_curr

            // check: type_index should less than type_section_count
            if(typeidx >= type_section_count) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u32 = typeidx;
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::illegal_type_index;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }

            functionsec.funcs.storage.typeidx_u32_vector.emplace_back_unchecked(typeidx);

            section_curr = reinterpret_cast<::std::byte const*>(typeidx_next);

            // [ ... typeidx1 ...] typeidx2 ...
            // [      safe       ] unsafe (could be the section_end)
            //                     ^^ section_curr
        }

        // [before_section ... | func_count ... typeidx1 ... ...] (end)
        // [                       safe                         ] unsafe (could be the section_end)
        //                                                        ^^ section_curr

        return section_curr;
    }

    /// @brief Define the handler function for type_section
    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    inline constexpr void handle_binfmt_ver1_extensible_section_define(
        ::uwvm2::parser::wasm::concepts::feature_reserve_type_t<function_section_storage_t> sec_adl,
        ::uwvm2::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...> & module_storage,
        ::std::byte const* const section_begin,
        ::std::byte const* const section_end,
        ::uwvm2::parser::wasm::base::error_impl& err,
        ::uwvm2::parser::wasm::concepts::feature_parameter_t<Fs...> const& fs_para,
        ::std::byte const* const sec_id_module_ptr) UWVM_THROWS
    {
#ifdef UWVM_TIMER
        ::uwvm2::utils::debug::timer parsing_timer{u8"parse function section (id: 3)"};
#endif
        // Note that section_begin may be equal to section_end
        // No explicit checking required because ::fast_io::parse_by_scan self-checking (::fast_io::parse_code::end_of_file)

        // get function_section_storage_t from storages
        auto& functionsec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<function_section_storage_t>(module_storage.sections)};

        // check duplicate
        if(functionsec.sec_span.sec_begin) [[unlikely]]
        {
            err.err_curr = sec_id_module_ptr;
            err.err_selectable.u8 = functionsec.section_id;
            err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::duplicate_section;
            ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        // check has typesec
        auto const& typesec{::uwvm2::parser::wasm::concepts::operation::get_first_type_in_tuple<type_section_storage_t<Fs...>>(module_storage.sections)};

        if(!typesec.sec_span.sec_begin) [[unlikely]]
        {
            err.err_curr = sec_id_module_ptr;
            err.err_selectable.u8arr[0] = typesec.section_id;
            err.err_selectable.u8arr[1] = functionsec.section_id;
            err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::forward_dependency_missing;
            ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }

        using wasm_byte_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte const*;

        functionsec.sec_span.sec_begin = reinterpret_cast<wasm_byte_const_may_alias_ptr>(section_begin);
        functionsec.sec_span.sec_end = reinterpret_cast<wasm_byte_const_may_alias_ptr>(section_end);

        auto section_curr{section_begin};

        // [before_section ... ] | func_count typeidx1 ...
        // [        safe       ] | unsafe (could be the section_end)
        //                         ^^ section_curr

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 func_count;  // No initialization necessary

        using char8_t_const_may_alias_ptr UWVM_GNU_MAY_ALIAS = char8_t const*;

        // No explicit checking required because ::fast_io::parse_by_scan self-checking (::fast_io::parse_code::end_of_file)
        auto const [func_count_next, func_count_err]{::fast_io::parse_by_scan(reinterpret_cast<char8_t_const_may_alias_ptr>(section_curr),
                                                                              reinterpret_cast<char8_t_const_may_alias_ptr>(section_end),
                                                                              ::fast_io::mnp::leb128_get(func_count))};

        if(func_count_err != ::fast_io::parse_code::ok) [[unlikely]]
        {
            err.err_curr = section_curr;
            err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::invalid_func_count;
            ::uwvm2::parser::wasm::base::throw_wasm_parse_code(func_count_err);
        }

        // [before_section ... | func_count ...] typeidx1 ...
        // [             safe                  ] unsafe (could be the section_end)
        //                       ^^ section_curr

        // The size_t of some platforms is smaller than u32, in these platforms you need to do a size check before conversion
        constexpr auto size_t_max{::std::numeric_limits<::std::size_t>::max()};
        constexpr auto wasm_u32_max{::std::numeric_limits<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>::max()};
        if constexpr(size_t_max < wasm_u32_max)
        {
            // The size_t of current platforms is smaller than u32, in these platforms you need to do a size check before conversion
            if(func_count > size_t_max) [[unlikely]]
            {
                err.err_curr = section_curr;
                err.err_selectable.u64 = static_cast<::std::uint_least64_t>(func_count);
                err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::size_exceeds_the_maximum_value_of_size_t;
                ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
            }
        }

        ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 func_counter{};  // use for check

        section_curr = reinterpret_cast<::std::byte const*>(func_count_next);  // never out of bounds

        // No explicit checking required because ::fast_io::parse_by_scan self-checking (::fast_io::parse_code::end_of_file)

        // [before_section ... | func_count ...] typeidx1 ...
        // [              safe                 ] unsafe (could be the section_end)
        //                                       ^^ section_curr

        // handle it
        auto const type_section_count{static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(typesec.types.size())};

        if(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 7u)
        {
            // storage: 1 byte
            // vectypeidx: almost always 1 byte, may be redundant zeros (up to 5 byte)
            section_curr = scan_function_section_impl_u8_1b(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
        }
        else if(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 8u)
        {
            // storage: 1 byte
            // vectypeidx: most 1 byte - 2 byte, may be redundant zeros (up to 5 byte)
            ::fast_io::fast_terminate();  /// @todo
#if 0
            section_curr = scan_function_section_impl_u8_2b(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
#endif
        }
        else if(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 14u)
        {
            // storage: 2 byte
            // vectypeidx: most 1 byte - 2 byte, may be redundant zeros (up to 5 byte)
            ::fast_io::fast_terminate();  /// @todo
#if 0
            section_curr = scan_function_section_impl_u16_2b(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
#endif
        }
        else if(type_section_count < static_cast<::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32>(1u) << 16u)
        {
            // storage: 2 byte
            // vectypeidx uleb128: most: 1 byte - 3 byte, may be redundant zeros (up to 5 byte)
            section_curr = scan_function_section_impl_u16_3b(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
        }
        else
        {
            // storage: 4 byte
            // vectypeidx uleb128: most: 1 byte - 5 byte
            section_curr = scan_function_section_impl_u32_5b(sec_adl, module_storage, section_curr, section_end, err, fs_para, func_counter, func_count);
        }

        // [before_section ... | func_count ... typeidx1 ... ...] (end)
        // [                       safe                         ] unsafe (could be the section_end)
        //                                                        ^^ section_curr

        // check function counter match
        if(func_counter != func_count) [[unlikely]]
        {
            err.err_curr = section_curr;
            err.err_selectable.u32arr[0] = func_counter;
            err.err_selectable.u32arr[1] = func_count;
            err.err_code = ::uwvm2::parser::wasm::base::wasm_parse_error_code::func_section_resolved_not_match_the_actual_number;
            ::uwvm2::parser::wasm::base::throw_wasm_parse_code(::fast_io::parse_code::invalid);
        }
    }
}  // namespace uwvm2::parser::wasm::standard::wasm1::features

/// @brief Define container optimization operations for use with fast_io
UWVM_MODULE_EXPORT namespace fast_io::freestanding
{
    template <>
    struct is_trivially_copyable_or_relocatable<::uwvm2::parser::wasm::standard::wasm1::features::function_section_storage_t>
    {
        inline static constexpr bool value = true;
    };

    template <>
    struct is_zero_default_constructible<::uwvm2::parser::wasm::standard::wasm1::features::function_section_storage_t>
    {
        inline static constexpr bool value = true;
    };
}

#ifndef UWVM_MODULE
// macro
# include <uwvm2/utils/macro/pop_macros.h>
#endif
