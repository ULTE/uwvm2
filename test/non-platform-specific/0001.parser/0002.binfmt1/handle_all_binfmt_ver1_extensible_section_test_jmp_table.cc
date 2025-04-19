/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @details     This example is used to test whether a jump table can be generated instead of a continuous if judgment
 * @version     2.0.0
 * @date        2025-04-13
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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <memory>

#include <utils/macro/push_macros.h>

#ifdef UWVM_MODULE
import fast_io;
import parser.wasm.base;
import uwvm.wasm.storage;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.binfmt.binfmt_ver1;
#else
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/tuple.h>
# include <utils/io/impl.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include <parser/wasm/binfmt/binfmt_ver1/impl.h>
#endif

#pragma push_macro("GNU_NOINLINE")
#undef GNU_NOINLINE
#if __has_cpp_attribute(__gnu__::__noinline__)
# define GNU_NOINLINE [[__gnu__::__noinline__]]
#endif

template <::parser::wasm::concepts::wasm_feature... Fs>
struct Sec1
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{1};

    // Expand on Sec1 here
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec1<Fs...>>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test1\n");
    return true;
}

struct Feature1
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature1"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    template <::parser::wasm::concepts::wasm_feature... Fs>
    using binfmt_ver1_section_type = ::fast_io::tuple<Sec1<Fs...>>;
};

template <::parser::wasm::concepts::wasm_feature... Fs>
struct Sec2
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{2};

    // Expand on Sec2 here
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec2<Fs...>>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test2\n");

    return true;
}

struct Sec3
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{3};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec3>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test3\n");

    return true;
}

struct Sec4
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{4};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec4>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test4\n");

    return true;
}

struct Sec5
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{5};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec5>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test5\n");

    return true;
}

struct Sec6
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{6};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec6>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test6\n");

    return true;
}

struct Sec7
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{7};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec7>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test7\n");

    return true;
}

struct Sec8
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{8};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec8>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test8\n");

    return true;
}

struct Sec9
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{9};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec9>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test9\n");

    return true;
}

struct Sec10
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{10};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec10>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test10\n");

    return true;
}

struct Sec11
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{11};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec11>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test11\n");

    return true;
}

struct Sec12
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{12};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec12>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test12\n");

    return true;
}

struct Sec13
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{13};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec13>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test13\n");

    return true;
}

struct Sec14
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{14};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec14>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test14\n");

    return true;
}

struct Sec15
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{15};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec15>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test15\n");

    return true;
}

struct Sec16
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{16};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec16>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test16\n");

    return true;
}

struct Sec17
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{17};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec17>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test17\n");

    return true;
}

struct Sec18
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{18};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec18>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test18\n");

    return true;
}

struct Sec19
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{19};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec19>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test19\n");

    return true;
}

struct Sec20
{
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 section_id{20};

    // Unexpandable section
};

template <::parser::wasm::concepts::wasm_feature... Fs>
GNU_NOINLINE inline constexpr bool handle_binfmt_ver1_extensible_section_define(
    ::parser::wasm::concepts::feature_reserve_type_t<::std::remove_cvref_t<Sec20>>,
    [[maybe_unused]] ::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_module_extensible_storage_t<Fs...>& module_storage,
    [[maybe_unused]] ::std::byte const* section_begin,
    [[maybe_unused]] ::std::byte const* section_end)
{
    ::fast_io::io::perrln(::utils::debug_output, u8"test20\n");

    return true;
}

struct Feature2
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature2"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    template <::parser::wasm::concepts::wasm_feature... Fs>
    using binfmt_ver1_section_type =
        ::fast_io::tuple<Sec2<Fs...>, Sec3, Sec4, Sec5, Sec6, Sec7, Sec8, Sec9, Sec10, Sec11, Sec12, Sec13, Sec14, Sec15, Sec16, Sec17, Sec18, Sec19, Sec20>;
};

struct Feature3
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature3"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
};

template <::parser::wasm::concepts::wasm_feature... Fs>
inline constexpr auto define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type_t<Feature1>, ::fast_io::tuple<Fs...>) noexcept
{
    return ::std::addressof(::parser::wasm::binfmt::ver1::wasm_binfmt_ver1_handle_func<Fs...>);
}

/*
root:                    wasm
                          |
                         /
                        /
binfmt:           binfmt_ver1(binfmt1)
                 /             |        \.
featurs:       Feature1     Feature2   Feature3
                 |          /      \
sections:      Sec1(ext) Sec2(ext) Sec3
*/

int main(int argc, char**)
{
    /// @brief All feature
    constexpr ::fast_io::tuple<Feature1, Feature2, Feature3> all_features{};
    // [[maybe_unused]] using all_feature_t = decltype(all_features);

    /// @brief wasm binfmt ver1 features
    using wasm_binfmt_ver1_features_t =
        decltype(::parser::wasm::concepts::operation::get_specified_binfmt_feature_tuple_from_all_freatures_tuple<1>(all_features));
    constexpr wasm_binfmt_ver1_features_t wasm_binfmt1_features{};
    using wasm_binfmt_ver1_module_storage_t = decltype(::parser::wasm::concepts::operation::get_module_storage_type_from_tuple(wasm_binfmt1_features));
    [[maybe_unused]] constexpr auto binfmt_ver1_handler{::parser::wasm::concepts::operation::get_binfmt_handler_func_p_from_tuple<1>(wasm_binfmt1_features)};

    wasm_binfmt_ver1_module_storage_t wasm_module1{};

    ::fast_io::io::perr(::utils::debug_output, u8"sec", argc, u8":\n");
    ::parser::wasm::binfmt::ver1::handle_all_binfmt_ver1_extensible_section(wasm_module1, nullptr, argc, nullptr, nullptr);
}

/*

(stderr)


*/
