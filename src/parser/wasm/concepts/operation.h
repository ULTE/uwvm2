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

#pragma once

#if !(__cpp_pack_indexing >= 202311L)
# error "UWVM requires at least C++26 standard compiler."
#endif

#ifdef UWVM_MODULE
import fast_io;
import parser.wasm.standard.wasm1.type;
import :root;
#else
// std
# include <cstddef>
# include <cstdint>
# include <type_traits>
# include <concepts>
# include <utility>
# include <algorithm>
# include <vector>
// import
# include <fast_io.h>
# include <fast_io_dsal/tuple.h>
# include <fast_io_dsal/array.h>
# include <parser/wasm/standard/wasm1/type/impl.h>
# include "root.h"
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace parser::wasm::concepts
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
        /// @see        test\non-platform-specific\0001.parser\0001.concept\binfmt_strategy.cc
        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval void check_has_duplicate_binfmt_handler() noexcept
        {
            // Check for duplicate Fs, wasm feature cannot be duplicated
            []<::std::size_t... I1>(::std::index_sequence<I1...>) constexpr noexcept
            {
                ((
                     []<::parser::wasm::concepts::wasm_feature F1>() constexpr noexcept
                     {
                         bool has{};
                         [&has]<::std::size_t... I2>(::std::index_sequence<I2...>) constexpr noexcept
                         {
                             ((
                                  [&has]<::parser::wasm::concepts::wasm_feature F2>() constexpr noexcept
                                  {
                                      if constexpr(::std::same_as<F1, F2>)
                                      {
                                          if(has) { ::fast_io::fast_terminate(); }
                                          else { has = true; }
                                      }
                                  }.template operator()<Fs...[I2]>()),
                              ...);
                         }(::std::make_index_sequence<sizeof...(Fs)>{});
                     }.template operator()<Fs...[I1]>()),
                 ...);
            }(::std::make_index_sequence<sizeof...(Fs)>{});

            // Define the binfmt needed for the feature. Duplicates not eliminated.
            ::std::vector<::parser::wasm::standard::wasm1::type::wasm_u32> binfmt_vers_uneliminated{};

            // Get all required binfmt versions from the variant templates
            [&binfmt_vers_uneliminated]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
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
            [&binfmt_handlers]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                ((
                     [&binfmt_handlers]<::parser::wasm::concepts::wasm_feature FeatureType>() constexpr noexcept
                     {
                         if constexpr(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<FeatureType>)
                         {
                             // pushback binfmtver
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
        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval void check_has_duplicate_binfmt_handler_from_tuple(::fast_io::tuple<Fs...>) noexcept
        {
            check_has_duplicate_binfmt_handler<Fs...>();
        }

        namespace details
        {
            /// @brief Get the function type from the tuple
            template <typename module_stroate_t, ::parser::wasm::concepts::wasm_feature... Fs>
            inline consteval binfmt_handle_version_func_p_type<module_stroate_t, Fs...>
                get_binfmt_handle_version_func_p_type_from_tuple(::fast_io::tuple<Fs...>) noexcept
            {
                return ::parser::wasm::concepts::binfmt_handle_version_func_p_type<module_stroate_t, Fs...>{};
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

            /// @brief Tuple merger for template elements
            template <typename F1, typename F2>
            struct tuple_type_merger;

            template <typename... F1, typename... F2>
            struct tuple_type_merger<::fast_io::tuple<F1...>, ::fast_io::tuple<F2...>>
            {
                using Result = ::fast_io::tuple<F1..., F2...>;
            };

            /// @brief Sift out tuples of the same version
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

            template <::std::uint_least32_t BinfmtVer, typename... Fs>
            using Fs_binfmt_controler_r = Fs_binfmt_controler<BinfmtVer, Fs...>::Result;

            /// @brief      function pointer return type getter
            /// @details    Getting the return type from a function pointer
            template <typename T>
            struct function_pointer_return_type_getter;

            template <typename Ret, typename... Args>
            struct function_pointer_return_type_getter<Ret (*)(Args...)>
            {
                using Type = Ret;
            };

            template <typename T>
            using function_pointer_return_type_getter_t = function_pointer_return_type_getter<T>::Type;
        }  // namespace details

        /// @brief Get the module storage type from all features in the same binfmt
        template <::parser::wasm::concepts::wasm_feature F, ::parser::wasm::concepts::wasm_feature... Fs1, ::parser::wasm::concepts::wasm_feature... AllFs>
        inline consteval auto get_module_storage_type_from_singal_tuple(::fast_io::tuple<AllFs...> all_feature_tuple) noexcept
        {
            constexpr bool can_func_get_module_storage_type{::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<F>};

            if constexpr(can_func_get_module_storage_type)
            {
                // Get the type of function pointer returned from define_wasm_binfmt_parsering_strategy
                using funcp_t = decltype(define_wasm_binfmt_parsering_strategy(::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<F>>,
                                                                               all_feature_tuple));
                // Getting the return type from a function pointer
                // This function only needs to return once, since a binfmt has only one processing option
                return details::function_pointer_return_type_getter_t<funcp_t>{};
            }
            else
            {
                // Proceed to the next search
                return get_module_storage_type_from_singal_tuple<Fs1...>(all_feature_tuple);
            }
        }

        template <::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval auto get_module_storage_type_from_tuple(::fast_io::tuple<Fs...> t) noexcept
        {
            return get_module_storage_type_from_singal_tuple<Fs...>(t);
        }

        /// @brief      Get the handler function for the corresponding version of binfmt from a series of features
        /// @see        test\non-platform-specific\0001.parser\0001.concept\get_handler_funcp.cc
        template <::parser::wasm::standard::wasm1::type::wasm_u32 BinfmtVer, ::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval auto get_binfmt_handler_func_p() noexcept
        {
            // check
            check_has_duplicate_binfmt_handler<Fs...>();

            // get required features for corresponding binfmt
            using current_binfmt_version_feature_tuple = details::Fs_binfmt_controler_r<BinfmtVer, Fs...>;
            using current_binfmt_version_feature_module_storage_t = decltype(get_module_storage_type_from_tuple(current_binfmt_version_feature_tuple{}));
            using current_binfmt_handle_version_func_p =
                decltype(details::get_binfmt_handle_version_func_p_type_from_tuple<current_binfmt_version_feature_module_storage_t>(
                    current_binfmt_version_feature_tuple{}));

            // create storage
            current_binfmt_handle_version_func_p handle_func_p{};

            // emplace
            [&handle_func_p]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                ((
                     [&handle_func_p]<::parser::wasm::concepts::wasm_feature FeatureType>() constexpr noexcept
                     {
                         constexpr auto binfmt_ver{get_binfmt_version<FeatureType>()};
                         // Determine if a requirement version is met
                         if constexpr(binfmt_ver == BinfmtVer)
                         {
                             // Is the type defined to correspond to the binfmt handler?
                             if constexpr(::parser::wasm::concepts::has_wasm_binfmt_parsering_strategy<FeatureType>)
                             {
                                 if(handle_func_p == nullptr)
                                 {
                                     constexpr auto handler{define_wasm_binfmt_parsering_strategy(
                                         ::parser::wasm::concepts::feature_reserve_type<::std::remove_cvref_t<FeatureType>>,
                                         current_binfmt_version_feature_tuple{})};
                                     // Storage, no subsequent access to this block
                                     handle_func_p = handler;
                                 }
                             }
                         }
                     }.template operator()<Fs...[I]>()),
                 ...);
            }(::std::make_index_sequence<sizeof...(Fs)>{});

            if(handle_func_p == nullptr)
            {
                // not found
                ::fast_io::fast_terminate();
            }

            return handle_func_p;
        }

        /// @brief      Get binfmt version handler functions from tuple
        /// @details    You can pass values directly when passing registers.
        template <::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version, ::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval auto get_binfmt_handler_func_p_from_tuple(::fast_io::tuple<Fs...>) noexcept
        {
            return get_binfmt_handler_func_p<binfmt_version, Fs...>();
        }

        /// @brief      Get binfmt version tuple type
        template <::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version, ::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval auto get_specified_binfmt_feature_tuple_from_all_freatures() noexcept
        {
            using current_binfmt_version_feature_tuple = details::Fs_binfmt_controler_r<binfmt_version, Fs...>;
            return current_binfmt_version_feature_tuple{};
        }

        /// @brief      Get binfmt version tuple type from tuple
        template <::parser::wasm::standard::wasm1::type::wasm_u32 binfmt_version, ::parser::wasm::concepts::wasm_feature... Fs>
        inline consteval auto get_specified_binfmt_feature_tuple_from_all_freatures_tuple(::fast_io::tuple<Fs...>) noexcept
        {
            return get_specified_binfmt_feature_tuple_from_all_freatures<binfmt_version, Fs...>();
        }

        /// @brief      Structure Replacement
        /// @details    Input unordered typename Replace fixed structure with typename, must replace starting from specified type,
        ///             only chains allowed, not directed graphs
        ///             An unordered chain of substitutions: b -> c, root -> a, a -> b, x -> y, x -> a ==> c
        ///             Automatic detection of duplicates, loops, different results with the same substitution
        template <typename A, typename B>
        struct type_replacer
        {
            // A -> B
            using superseded = A;
            using replacement = B;
        };

        struct root_of_replacement
        {
        };

        namespace details
        {
            template <typename T>
            struct type_wrapper
            {
                using Type = T;
            };

            // Overloading commas for subsequent type calculations
            template <typename T>
            inline consteval type_wrapper<T> operator, (type_wrapper<T>, type_wrapper<void>) noexcept
            {
                return type_wrapper<T>{};
            }

            template <typename T>
            inline consteval type_wrapper<T> operator, (type_wrapper<void>, type_wrapper<T>) noexcept
            {
                return type_wrapper<T>{};
            }

            template <typename T1, typename T2>
            inline consteval void operator, (type_wrapper<T1>, type_wrapper<T2>) noexcept = delete;

            inline consteval type_wrapper<void> operator, (type_wrapper<void>, type_wrapper<void>) noexcept { return type_wrapper<void>{}; }

            /// @details No substitution, for filling, use at your own risk
            struct irreplaceable_t1
            {
            };

            struct irreplaceable_t2
            {
            };

            // Type Calculation
            template <template <typename, typename> typename T, typename Superseded, typename... Args>
                requires (::std::same_as<T<typename Args::superseded, typename Args::replacement>,
                                         type_replacer<typename Args::superseded, typename Args::replacement>> &&
                          ...)
            inline consteval auto replacement_structure_followup_impl(::fast_io::array<bool, sizeof...(Args)>& repeating) noexcept
            {
                bool is_repeatable{};
                return [&is_repeatable, &repeating]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
                {
                    auto ret {
                        ((
                             [&is_repeatable, &repeating]<typename ArgCurr>() constexpr noexcept
                             {
                                 // check irreplaceable
                                 if constexpr(::std::same_as<typename ArgCurr::superseded, irreplaceable_t1> ||
                                              ::std::same_as<typename ArgCurr::superseded, irreplaceable_t2> || ::std::same_as<Superseded, irreplaceable_t1> ||
                                              ::std::same_as<Superseded, irreplaceable_t2>)
                                 {
                                     return type_wrapper<void>{};
                                 }

                                 if constexpr(::std::same_as<typename ArgCurr::superseded, typename ArgCurr::replacement>)
                                 {
                                     // Replacement of the same type
                                     ::fast_io::fast_terminate();
                                 }

                                 if constexpr(::std::same_as<typename ArgCurr::superseded, Superseded>)
                                 {
                                     if(is_repeatable)
                                     {
                                         // Prohibition of duplicate substitutions
                                         // a -> b, a -> c X
                                         ::fast_io::fast_terminate();
                                     }
                                     else
                                     {
                                         if(repeating[I])
                                         {
                                             // Type Loop
                                             ::fast_io::fast_terminate();
                                         }
                                         repeating[I] = true;
                                         using replacement = typename ArgCurr::replacement;
                                         is_repeatable = true;
                                         return replacement_structure_followup_impl<T, replacement, Args...>(repeating);
                                     }
                                 }
                                 else { return type_wrapper<void>{}; }
                             }.template operator()<Args...[I]>()),
                         ...)
                    };
                    using rettype = decltype(ret);
                    if constexpr(::std::same_as<rettype, type_wrapper<void>>)
                    {
                        // last one
                        return type_wrapper<Superseded>{};
                    }
                    else { return ret; }
                }(::std::make_index_sequence<sizeof...(Args)>{});
            }

            /// @details check_is_type_replacer<type_replacer, typename T::test>;
            template <template <typename, typename> typename TypeReplacer, typename Args>
            concept check_is_type_replacer = ::std::same_as<TypeReplacer<typename Args::superseded, typename Args::replacement>,
                                                            type_replacer<typename Args::superseded, typename Args::replacement>>;

        }  // namespace details

        using irreplaceable_t = type_replacer<details::irreplaceable_t1, details::irreplaceable_t2>;

        template <typename... Args>
        inline consteval auto replacement_structure() noexcept
        {
            // repeating_table is used to detect loops, if the loop will hit an existing element, terminate it.
            ::fast_io::array<bool, sizeof...(Args)> repeating_table{};
            return details::replacement_structure_followup_impl<type_replacer, root_of_replacement, Args...>(repeating_table);
        }

        template <typename... Args>
        using replacement_structure_t = decltype(replacement_structure<Args...>())::Type;

        /// @brief      Tuple merger for template expansion
        /// @details    Merge tuples by overloading operator,() operator
        template <typename... Fs>
        struct tuple_megger
        {
            using Type = ::fast_io::tuple<Fs...>;
        };

        template <typename... T1, typename... T2>
        inline constexpr tuple_megger<T1..., T2...> operator, (tuple_megger<T1...>, tuple_megger<T2...>) noexcept
        {
            // constexpr provides functions for use at runtime
            return tuple_megger<T1..., T2...>{};
        }

        template <typename... Fs>
        inline consteval tuple_megger<Fs...> get_tuple_megger_from_tuple(::fast_io::tuple<Fs...>) noexcept
        {
            return tuple_megger<Fs...>{};
        }

        template <typename TyGet, typename... Tys>
        inline consteval ::std::size_t get_first_type_index_in_tuple() noexcept
        {
            ::std::size_t ret{SIZE_MAX};
            [&ret]<::std::size_t... I>(::std::index_sequence<I...>) constexpr noexcept
            {
                ((
                     [&ret]<typename TyCurr>() constexpr noexcept
                     {
                         if constexpr(::std::same_as<TyCurr, TyGet>)
                         {
                             if(ret == SIZE_MAX) { ret = I; }
                         }
                     }.template operator()<Tys...[I]>()),
                 ...);
            }(::std::make_index_sequence<sizeof...(Tys)>{});

            if(ret == SIZE_MAX) { ::fast_io::fast_terminate(); }

            return ret;
        };

        /// @brief get first type in tuple
        template <typename TyGet, typename... Tys>
        inline constexpr auto&& get_first_type_in_tuple(::fast_io::tuple<Tys...>& tuple) noexcept
        {
            constexpr ::std::size_t type_index{get_first_type_index_in_tuple<TyGet, Tys...>()};
            return get<type_index>(tuple);
        }

        template <typename TyGet, typename... Tys>
        inline constexpr auto&& get_first_type_in_tuple(::fast_io::tuple<Tys...> const& tuple) noexcept
        {
            constexpr ::std::size_t type_index{get_first_type_index_in_tuple<TyGet, Tys...>()};
            return get<type_index>(tuple);
        }

        template <typename TyGet, typename... Tys>
        inline constexpr auto&& get_first_type_in_tuple(::fast_io::tuple<Tys...>&& tuple) noexcept
        {
            constexpr ::std::size_t type_index{get_first_type_index_in_tuple<TyGet, Tys...>()};
            return get<type_index>(tuple);
        }

        template <typename TyGet, typename... Tys>
        inline constexpr auto&& get_first_type_in_tuple(::fast_io::tuple<Tys...> const&& tuple) noexcept
        {
            constexpr ::std::size_t type_index{get_first_type_index_in_tuple<TyGet, Tys...>()};
            return get<type_index>(tuple);
        }
    }  // namespace operation
}  // namespace parser::wasm::concepts
