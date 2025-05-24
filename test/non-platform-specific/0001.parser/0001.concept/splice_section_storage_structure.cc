/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-12
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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <memory>

#include <uwvm2/utils/macro/push_macros.h>

#ifdef UWVM_MODULE
import fast_io;
import parser.wasm.base;
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
import parser.wasm.binfmt.binfmt_ver1;
import uwvm.io;
import uwvm.wasm.storage;
#else
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <fast_io_dsal/tuple.h>
# include <uwvm2/parser/wasm/concepts/impl.h>
# include <uwvm2/parser/wasm/standard/wasm1/type/impl.h>
# include <uwvm2/parser/wasm/binfmt/binfmt_ver1/impl.h>
# include <uwvm2/uwvm/io/impl.h>
# include <uwvm2/uwvm/wasm/storage/impl.h>
#endif

template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
struct Sec1
{
    inline static constexpr ::fast_io::u8string_view section_name{u8"Sec1 ext"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte section_id{1};

    // Expand on Sec1 here
};

struct Feature1
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature1"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    using binfmt_ver1_section_type = ::fast_io::tuple<Sec1<Fs...>>;
};

template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
struct Sec2
{
    inline static constexpr ::fast_io::u8string_view section_name{u8"Sec2 ext"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte section_id{2};

    // Expand on Sec2 here
};

struct Sec3
{
    inline static constexpr ::fast_io::u8string_view section_name{u8"Sec3"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_byte section_id{3};

    // Unexpandable section
};

struct Feature2
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature2"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};

    template <::uwvm2::parser::wasm::concepts::wasm_feature... Fs>
    using binfmt_ver1_section_type = ::fast_io::tuple<Sec2<Fs...>, Sec3>;
};

struct Feature3
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"Feature3"};
    inline static constexpr ::uwvm2::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
};

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

int main()
{
    using T = ::uwvm2::parser::wasm::binfmt::ver1::splice_section_storage_structure_t<Feature1, Feature2, Feature3>;
    static_assert(::std::same_as<T, ::fast_io::tuple<Sec1<Feature1, Feature2, Feature3>, Sec2<Feature1, Feature2, Feature3>, Sec3>>);
}

// macro
#include <uwvm2/utils/macro/pop_macros.h>
