/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-07
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
import parser.wasm.concepts;
import parser.wasm.standard.wasm1.type;
#else
# include <fast_io.h>
# include <fast_io_dsal/string_view.h>
# include <parser/wasm/concepts/impl.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
#endif
struct feature1
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"1"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
};

struct binfmt_ver1_module_storage_t
{
};

template <::parser::wasm::concepts::wasm_feature... Fs>
inline constexpr binfmt_ver1_module_storage_t handle_func(::fast_io::tuple<Fs...>, ::std::byte const*, ::std::byte const*) UWVM_THROWS
{
    return {};
}

template <::parser::wasm::concepts::wasm_feature... Fs>
inline constexpr auto define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type_t<feature1>, ::fast_io::tuple<Fs...>) noexcept
{
    return ::std::addressof(handle_func<Fs...>);
}

struct feature2
{
    inline static constexpr ::fast_io::u8string_view feature_name{u8"2"};
    inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
};

static_assert(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<feature1>);

int main() { ::parser::wasm::concepts::operation::check_has_duplicate_binfmt_handler<feature1, feature2>(); }
