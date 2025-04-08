/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-06
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

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <utility>
#include <algorithm>
#include <vector>

#if !(__cpp_pack_indexing >= 202311L)
# error "UWVM requires at least C++26 standard compiler."
#endif

export module parser.wasm.concepts:operation;

import fast_io;
import parser.wasm.standard.wasm1.type;
import :root;

export namespace parser::wasm::concepts
{
    namespace details
    {
        /// @brief Determine if parameters can be passed through registers under the current abi.
        template <typename T>
        concept abi_transferable_value = ::std::is_trivially_copyable_v<T> &&
#if (defined(_WIN32) && !defined(__WINE__)) || defined(__CYGWIN__)
                                         sizeof(T) <= 8u
#else
                                         sizeof(T) <= (sizeof(::std::size_t) * 2)
#endif
            ;
    }  // namespace details

    namespace operation
    {
        /// @brief      Get the version of binfmt
        /// @details    Need to satisfy the concept has_wasm_binfmt_version
        template <::parser::wasm::concepts::wasm_feature FeatureType>
            requires (::parser::wasm::concepts::has_wasm_binfmt_version<FeatureType>)
        inline consteval ::parser::wasm::standard::wasm1::type::wasm_u32 get_binfmt_version() noexcept
        {
            constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{::std::remove_cvref_t<FeatureType>::binfmt_version};
            // Can't be 0.
            if constexpr(binfmt_version == 0) { ::fast_io::fast_terminate(); }
            return binfmt_version;
        }

        /// @brief      Checking for duplicate binfmt version handler functions
        /// @details    Version numbers can be repeated
        ///             Each version number must have a corresponding handler function
        ///             Handling functions cannot be duplicated
        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval void check_has_duplicate_binfmt_handler() noexcept
        {
            // Define the binfmt needed for the feature. Duplicates not eliminated.
            ::std::vector<::parser::wasm::standard::wasm1::type::wasm_u32> binfmt_vers_uneliminated{};

            // Get all required binfmt versions from the variant templates
            [&]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            { ((binfmt_vers_uneliminated.push_back(get_binfmt_version<Fs...[I]>())), ...); }(::std::make_index_sequence<sizeof...(Fs)>{});

            // Sorting for easy follow-up
            ::std::ranges::sort(binfmt_vers_uneliminated);

            // Constructing a version that eliminates duplicates.
            ::std::vector<::parser::wasm::standard::wasm1::type::wasm_u32> binfmt_vers{};
            for(::parser::wasm::standard::wasm1::type::wasm_u32 tmp{0u}; auto curr: binfmt_vers_uneliminated)
            {
                if(curr == tmp) { continue; }
                tmp = curr;
                binfmt_vers.push_back(curr);
            }

            // Define the binfmt needed to process the feature.
            ::std::vector<::parser::wasm::standard::wasm1::type::wasm_u32> binfmt_handlers{};

            // Cannot define a parsing policy that differs from your wasm version.
            [&]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                ((
                     [&]<::parser::wasm::concepts::wasm_feature FeatureType>() constexpr noexcept
                     {
                         if constexpr(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<FeatureType>)
                         {
                             constexpr auto binfmt_ver{get_binfmt_version<FeatureType>()};
                             binfmt_handlers.push_back(binfmt_ver);
                         }
                     }.template operator()<Fs...[I]>()),
                 ...);
            }(::std::make_index_sequence<sizeof...(Fs)>{});

            // Determine if there is a corresponding parsing scheme by the existing binfmt version.
            ::std::ranges::sort(binfmt_handlers);

            // Check for duplicates
            for(::parser::wasm::standard::wasm1::type::wasm_u32 tmp{0u}; auto curr: binfmt_handlers)
            {
                if(curr == tmp) { ::fast_io::fast_terminate(); }
                tmp = curr;
            }

            // Ensure that the version corresponds to the processing
            if(binfmt_vers != binfmt_handlers) { ::fast_io::fast_terminate(); }
        }

        /// @brief      Checking for duplicate binfmt version handler functions from tuple
        /// @details    You can pass values directly when passing registers.
        template <::parser::wasm::concepts::wasm_feature... Fs>
            requires (::parser::wasm::concepts::details::abi_transferable_value<::fast_io::tuple<Fs...>>)
        inline consteval void check_has_duplicate_binfmt_handler_from_tuple(::fast_io::tuple<Fs...>) noexcept
        {
            check_has_duplicate_binfmt_handler<Fs...>();
        }

        /// @brief      Checking for duplicate binfmt version handler functions from tuple
        /// @details    You can't pass references on register passes.
        template <::parser::wasm::concepts::wasm_feature... Fs>
            requires (!::parser::wasm::concepts::details::abi_transferable_value<::fast_io::tuple<Fs...>>)
        inline consteval void check_has_duplicate_binfmt_handler_from_tuple(::fast_io::tuple<Fs...> const&) noexcept
        {
            check_has_duplicate_binfmt_handler<Fs...>();
        }

        namespace details
        {
            /// @brief Provide temporary structure for get_binfmt_handler_func_p
            template <::parser::wasm::concepts::wasm_feature... Fs>
            struct binfmt_and_funcp_pair
            {
                ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{};
                ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...> func_p{};
            };

            template <::parser::wasm::concepts::wasm_feature... Fs>
            inline constexpr auto operator== (binfmt_and_funcp_pair<Fs...> a, binfmt_and_funcp_pair<Fs...> b) noexcept
            {
                return a.binfmt_version == b.binfmt_version;
            }

            template <::parser::wasm::concepts::wasm_feature... Fs>
            inline constexpr auto operator<=> (binfmt_and_funcp_pair<Fs...> a, binfmt_and_funcp_pair<Fs...> b) noexcept
            {
                return a.binfmt_version <=> b.binfmt_version;
            }

            /// @brief      Provide template meta to filter out different binfmt versions
            /// @details                   
            ///                            wasm
            ///                     <B1F1, B1F2, B2F3, ...>
            ///                      ______________________
            ///                     /            |        |
            ///                  binfmt1       binfmt2   ...
            ///                <B1F1, B1F2>     <B2F3>   ...
            ///
            ///             ```cpp
            ///             struct B1F1
            ///             {
            ///                 inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1};
            ///             };
            ///
            ///             struct B1F2
            ///             {
            ///                 inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1};
            ///             };
            ///
            ///             struct B2F3
            ///             {
            ///                 inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{2};
            ///             };
            ///
            ///             using all_features = ::fast_io::tuple<B1F1, B1F2, B2F3>;
            ///            
            ///             using binfmt1_features = Fs_binfmt_controler_r<1, B1F1, B1F2, B2F3>; // same_as ::fast_io::tuple<B1F1, B1F2>
            ///
            ///             using binfmt2_features = Fs_binfmt_controler_r<2, B1F1, B1F2, B2F3>; // same_as ::fast_io::tuple<B2F3>
            /// 
            ///             ```
            template <typename F1, typename F2>
            struct tuple_type_merger;

            template <typename... F1, typename... F2>
            struct tuple_type_merger<::fast_io::tuple<F1...>, ::fast_io::tuple<F2...>>
            {
                using Result = ::fast_io::tuple<F1..., F2...>;
            };

            template <::parser::wasm::standard::wasm1::type::wasm_u32 BinfmtVer, typename... Fs>
            struct Fs_binfmt_controler;

            template <::parser::wasm::standard::wasm1::type::wasm_u32 BinfmtVer>
            struct Fs_binfmt_controler<BinfmtVer>
            {
                using Result = ::fast_io::tuple<>;
            };

            template <::parser::wasm::standard::wasm1::type::wasm_u32 BinfmtVer, typename F>
            struct Fs_binfmt_controler<BinfmtVer, F>
            {
                inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_ver{get_binfmt_version<F>()};
                using Result = ::std::conditional_t<(binfmt_ver == BinfmtVer), ::fast_io::tuple<F>, ::fast_io::tuple<>>;
            };

            template <::parser::wasm::standard::wasm1::type::wasm_u32 BinfmtVer, typename F, typename... Fs>
            struct Fs_binfmt_controler<BinfmtVer, F, Fs...>
            {
                inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_ver{get_binfmt_version<F>()};
                using CurrentResult = ::std::conditional_t<(binfmt_ver == BinfmtVer), ::fast_io::tuple<F>, ::fast_io::tuple<>>;
                using RestResult = Fs_binfmt_controler<BinfmtVer, Fs...>::Result;

                using Result = tuple_type_merger<CurrentResult, RestResult>::Result;
            };

            template <::std::uint_least32_t Ver, typename... Fs>
            using Fs_binfmt_controler_r = Fs_binfmt_controler<Ver, Fs...>::Result;

        }  // namespace details

        /// @brief      Get the handler function for the corresponding version of binfmt from a series of features
        /// @details
        ///             example:
        ///
        ///             ```cpp
        ///
        ///             struct feature1
        ///             {
        ///                 inline static constexpr ::fast_io::u8string_view feature_name{u8"feature1name"};
        ///                 inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
        ///             };
        ///
        ///             template <::parser::wasm::concepts::wasm_feature... Fs>
        ///             inline constexpr void binfmt_ver1_handle_func(::fast_io::tuple<Fs...>, ::std::byte const*, ::std::byte const*) UWVM_THROWS
        ///             {
        ///                 // This defines the function that handles binary format 1.
        ///                 // Supported by <::parser::wasm::concepts::wasm_feature... Fs> Continued Expansion
        ///             }
        ///
        ///             template <::parser::wasm::concepts::wasm_feature... Fs>
        ///             inline constexpr ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...>
        ///                 define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type_t<feature1>, ::fast_io::tuple<Fs...>) noexcept
        ///             {
        ///                 // Since feature1 defines binfmt as 1 and also defines the handler function, this function is the parsing function for binfmt1
        ///                 return ::std::addressof(binfmt_ver1_handle_func<Fs...>);
        ///             }
        ///
        ///             struct feature2
        ///             {
        ///                 inline static constexpr ::fast_io::u8string_view feature_name{u8"feature2name"};
        ///                 inline static constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version{1u};
        ///             };
        ///
        ///             int main()
        ///             {
        ///                 constexpr ::fast_io::tuple<feature1, feature2> features{};
        ///                 constexpr auto funcp{::parser::wasm::concepts::operation::get_binfmt_handler_func_p_from_tuple(1, features)};
        ///                 funcp(features, nullptr, nullptr);
        ///             }
        ///             ```
        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...>
            get_binfmt_handler_func_p(::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version) noexcept
        {
            // check
            check_has_duplicate_binfmt_handler<Fs...>();

            // create vector
            ::std::vector<details::binfmt_and_funcp_pair<Fs...>> fmt_and_funcs{};

            // emplace
            [&]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                ((
                     [&]<::parser::wasm::concepts::wasm_feature FeatureType>() constexpr noexcept
                     {
                         if constexpr(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<FeatureType>)
                         {
                             constexpr ::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_ver{get_binfmt_version<FeatureType>()};
                             constexpr ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...> handler{
                                 define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<FeatureType>>,
                                                                       ::fast_io::tuple<Fs...>{})};
                             fmt_and_funcs.emplace_back(binfmt_ver, handler);
                         }
                     }.template operator()<Fs...[I]>()),
                 ...);
            }(::std::make_index_sequence<sizeof...(Fs)>{});

            // try to find
            for(auto [bfv, fp]: fmt_and_funcs)
            {
                if(binfmt_version == bfv) { return fp; }
            }

            // not found
            ::fast_io::fast_terminate();
        }

        /// @brief      Checking for duplicate binfmt version handler functions from tuple
        /// @details    You can pass values directly when passing registers.
        template <::parser::wasm::concepts::wasm_feature... Fs>
            requires (::parser::wasm::concepts::details::abi_transferable_value<::fast_io::tuple<Fs...>>)
        inline consteval ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...>
            get_binfmt_handler_func_p_from_tuple(::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version, ::fast_io::tuple<Fs...>) noexcept
        {
            return get_binfmt_handler_func_p<Fs...>(binfmt_version);
        }

        /// @brief      Checking for duplicate binfmt version handler functions from tuple
        /// @details    You can't pass references on register passes.
        template <::parser::wasm::concepts::wasm_feature... Fs>
            requires (!::parser::wasm::concepts::details::abi_transferable_value<::fast_io::tuple<Fs...>>)
        inline consteval ::parser::wasm::concepts::binfmt_handle_version_func_p_type<Fs...>
            get_binfmt_handler_func_p_from_tuple(::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version, ::fast_io::tuple<Fs...> const&) noexcept
        {
            return get_binfmt_handler_func_p<Fs...>(binfmt_version);
        }
    }  // namespace operation
}  // namespace parser::wasm::concepts
