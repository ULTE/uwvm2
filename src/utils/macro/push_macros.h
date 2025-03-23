/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author MacroModel
 * @version 2.0.0
 * @date 2025-03-23
 * @copyright APL-2 License
 */

/****************************************
 *  _   _ __        ____     __ __  __  *
 * | | | |\ \      / /\ \   / /|  \/  | *
 * | | | | \ \ /\ / /  \ \ / / | |\/| | *
 * | |_| |  \ V  V /    \ V /  | |  | | *
 *  \___/    \_/\_/      \_/   |_|  |_| *
 *                                      *
 ****************************************/

/// @brief The following are the macros used by uwvm.
/// @details Use `push_macro` to avoid side effects on existing macros. Please use `pop_macro` in conjunction.

// #pragma once /// pragma once is not necessary

/// @brief std and windows.h macro

#pragma push_macro("erase")
#undef erase

#pragma push_macro("interface")
#undef interface

#pragma push_macro("max")
#undef max

#pragma push_macro("min")
#undef min

#pragma push_macro("move")
#undef move

#pragma push_macro("new")
#undef new

#pragma push_macro("refresh")
#undef refresh

/// @brief        uwvm's macros

/// @brief        import func from dll
/// @details      on msvc: __declspec(dllimport)
///               on gcc, clang [[__gnu__::__dllimport__]]
#pragma push_macro("UWVM_DLLIMPORT")
#undef UWVM_DLLIMPORT
#if defined(_MSC_VER) && !defined(__clang__)
# define UWVM_DLLIMPORT __declspec(dllimport)
#elif __has_cpp_attribute(__gnu__::__dllimport__) && !defined(__WINE__) && !defined(__arm64ec__)
# define UWVM_DLLIMPORT [[__gnu__::__dllimport__]]
#else
# define UWVM_DLLIMPORT
#endif

/// @brief        import function from dll under the premise of having a `_DLL` macro
/// @details      same as `UWVM_DLLIMPORT`
#pragma push_macro("UWVM_DLL_DLLIMPORT")
#undef UWVM_DLL_DLLIMPORT
#if defined(_DLL) && !defined(__WINE__)
# define UWVM_DLL_DLLIMPORT UWVM_DLLIMPORT
#else
# define UWVM_DLL_DLLIMPORT
#endif

/// @brief        stdcall
/// @details      On x86-32 targets, the stdcall attribute causes the compiler to assume 
///               that the called function pops off the stack space used to pass arguments, 
///               unless it takes a variable number of arguments.
/// @details      on msvc: __stdcall
///               on gcc, clang: __attribute__((__stdcall__))
#pragma push_macro("UWVM_STDCALL")
#undef UWVM_STDCALL
#if defined(_MSC_VER) && (!__has_cpp_attribute(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWVM_STDCALL __stdcall
#elif (__has_cpp_attribute(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWVM_STDCALL __attribute__((__stdcall__))
#else
# define UWVM_STDCALL
#endif

/// @brief        stdcall attribute, same as UWVM_STDCALL
/// @see          UWVM_STDCALL
#pragma push_macro("UWVM_WINSTDCALL")
#undef UWVM_WINSTDCALL
#if defined(_MSC_VER) && (!__has_cpp_attribute(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWVM_WINSTDCALL __stdcall
#elif (__has_cpp_attribute(__gnu__::__stdcall__) && !defined(__WINE__))
# define UWVM_WINSTDCALL __attribute__((__stdcall__))
#else
# define UWVM_WINSTDCALL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWVM_WINSTDCALL
#pragma push_macro("UWVM_WINSTDCALL_RENAME")
#undef UWVM_WINSTDCALL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWVM_WINSTDCALL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWVM_WINSTDCALL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWVM_WINSTDCALL_RENAME(name, count) __asm__(#name "@" #count)
#  else
#   define UWVM_WINSTDCALL_RENAME(name, count) __asm__("_" #name "@" #count)
#  endif
# else
#  define UWVM_WINSTDCALL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWVM_WINSTDCALL_RENAME(name, count)
#endif

/// @brief        cdecl
/// @details      On the x86-32 targets, the cdecl attribute causes the compiler to assume that the calling function pops
///               off the stack space used to pass arguments. This is useful to override the effects of the -mrtd switch.
/// @details      on msvc: __cdecl
///               on gcc, clang: __attribute__((__cdecl__))
#pragma push_macro("UWVM_WINCDECL")
#undef UWVM_WINCDECL
#if defined(_MSC_VER) && (!__has_cpp_attribute(__gnu__::__cdecl__) && !defined(__WINE__))
# define UWVM_WINCDECL __cdecl
#elif (__has_cpp_attribute(__gnu__::__cdecl__) && !defined(__WINE__))
# define UWVM_WINCDECL __attribute__((__cdecl__))
#else
# define UWVM_WINCDECL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWVM_WINCDECL
#pragma push_macro("UWVM_WINCDECL_RENAME")
#undef UWVM_WINCDECL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWVM_WINCDECL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWVM_WINCDECL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWVM_WINCDECL_RENAME(name, count) __asm__(#name)
#  else
#   define UWVM_WINCDECL_RENAME(name, count) __asm__("_" #name)
#  endif
# else
#  define UWVM_WINCDECL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWVM_WINCDECL_RENAME(name, count)
#endif

/// @brief        fastcall
/// @details      On x86-32 targets, the fastcall attribute causes the compiler to pass the first argument
///               (if of integral type) in the register ECX and the second argument (if of integral type)
///               in the register EDX. Subsequent and other typed arguments are passed on the stack.
///               The called function pops the arguments off the stack. If the number of arguments is variable
///               all arguments are pushed on the stack.
/// @details      on msvc: __fastcall
///               on gcc, clang: __attribute__((__fastcall__))
#pragma push_macro("UWVM_WINFASTCALL")
#undef UWVM_WINFASTCALL
#if defined(_MSC_VER) && (!__has_cpp_attribute(__gnu__::__fastcall__) && !defined(__WINE__))
# define UWVM_WINFASTCALL __fastcall
#elif (__has_cpp_attribute(__gnu__::__fastcall__) && !defined(__WINE__))
# define UWVM_WINFASTCALL __attribute__((__fastcall__))
#else
# define UWVM_WINFASTCALL
#endif

/// @brief        Modify function symbol linkage via ASM on GCC or Clang
/// @see          UWVM_WINFASTCALL
#pragma push_macro("UWVM_WINFASTCALL_RENAME")
#undef UWVM_WINFASTCALL_RENAME
#if defined(__clang__) || defined(__GNUC__)
# if defined(_M_HYBRID)
#  define UWVM_WINFASTCALL_RENAME(name, count) __asm__("#" #name "@" #count)
# elif defined(__arm64ec__)
#  define UWVM_WINFASTCALL_RENAME(name, count) __asm__("#" #name)
# elif SIZE_MAX <= UINT_LEAST32_MAX && (defined(__x86__) || defined(_M_IX86) || defined(__i386__))
#  if !defined(__clang__)
#   define UWVM_WINFASTCALL_RENAME(name, count) __asm__("@" #name "@" #count)
#  else
#   define UWVM_WINFASTCALL_RENAME(name, count) __asm__("_@" #name "@" #count)
#  endif
# else
#  define UWVM_WINFASTCALL_RENAME(name, count) __asm__(#name)
# endif
#else
# define UWVM_WINFASTCALL_RENAME(name, count)
#endif

/// @brief        [[gnu::const]] is an attribute that can be applied to functions to indicate that they are pure in a specific way.
/// @details      on gcc, clang: [[__gnu__::__const__]]
#pragma push_macro("UWVM_GNU_CONST")
#undef UWVM_GNU_CONST
#if __has_cpp_attribute(__gnu__::__const__)
# define UWVM_GNU_CONST [[__gnu__::__const__]]
#else
# define UWVM_GNU_CONST
#endif

/// @brief        forceinline 
/// @details      After C++17, the `inline` keyword no longer indicates forced inlining; 
///               instead, it serves to prevent ODR violations. Forced inlining should be achieved using the forceinline attribute.
/// @details      on gcc, clang: [[__gnu__::__always_inline__]]
///               on msvc: [[msvc::forceinline]]
#pragma push_macro("UWVM_ALWAYS_INLINE")
#undef UWVM_ALWAYS_INLINE
#if __has_cpp_attribute(__gnu__::__always_inline__)
# define UWVM_ALWAYS_INLINE [[__gnu__::__always_inline__]]
#elif __has_cpp_attribute(msvc::forceinline)
# define UWVM_ALWAYS_INLINE [[msvc::forceinline]]
#else
# define UWVM_ALWAYS_INLINE
#endif

/// @brief        Marking a function with [[gnu::artificial]] hints to debuggers that it is not 
///               a user-defined function, reducing unnecessary debug info.
/// @details      on gcc, clang: [[__gnu__::__artificial__]]
#pragma push_macro("UWVM_GNU_ARTIFICIAL")
#undef UWVM_GNU_ARTIFICIAL
#if __has_cpp_attribute(__gnu__::__artificial__)
# define UWVM_GNU_ARTIFICIAL [[__gnu__::__artificial__]]
#else
# define UWVM_GNU_ARTIFICIAL
#endif

/// @brief        UWVM_ALWAYS_INLINE + UWVM_GNU_ARTIFICIAL
/// @see          UWVM_ALWAYS_INLINE
/// @see          UWVM_GNU_ARTIFICIAL
#pragma push_macro("UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL")
#undef UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL
#define UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL UWVM_ALWAYS_INLINE UWVM_GNU_ARTIFICIAL

/// @brief        UWVM_ALWAYS_INLINE + UWVM_GNU_ARTIFICIAL + [[nodiscard]] + UWVM_GNU_CONST
/// @see          UWVM_ALWAYS_INLINE
/// @see          UWVM_GNU_ARTIFICIAL
/// @see          C++ attribute: [[nodiscard]]
/// @see          UWVM_GNU_CONST
#pragma push_macro("UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST")
#undef UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST
#define UWVM_GNU_ALWAYS_INLINE_ARTIFICIAL_CONST UWVM_ALWAYS_INLINE [[nodiscard]] UWVM_GNU_ARTIFICIAL UWVM_GNU_CONST

/// @brief        This part refers to memory allocation functions, which are responsible for managing dynamic memory
///               (e.g., allocating and freeing memory).
/// @details      on gcc, clang: [[__gnu__::__malloc__]]
#pragma push_macro("UWVM_GNU_MALLOC")
#undef UWVM_GNU_MALLOC
#if __has_cpp_attribute(__gnu__::__malloc__)
# define UWVM_GNU_MALLOC [[__gnu__::__malloc__]]
#else
# define UWVM_GNU_MALLOC
#endif

/// @brief        Telling the compiler (and other developers) that the function will never return a null pointer
/// @details      on gcc, clang: [[__gnu__::__returns_nonnull__]]
#pragma push_macro("UWVM_GNU_RETURNS_NONNULL")
#undef UWVM_GNU_RETURNS_NONNULL
#if __has_cpp_attribute(__gnu__::__returns_nonnull__)
# define UWVM_GNU_RETURNS_NONNULL [[__gnu__::__returns_nonnull__]]
#else
# define UWVM_GNU_RETURNS_NONNULL
#endif

/// @brief        assert
/// @details      Avoid using C++26 contracts. Different modules including different handle_contract_violation 
///               implementations may result in multiple handling approaches. If a module without handle_contract_violation 
///               is included, std::terminate or std::abort will be used instead of the direct trap behavior we desire.
/// @details      on gcc, clang: __builtin_trap()
///               on msvc: abort()
#pragma push_macro("UWVM_ASSERT")
#undef UWVM_ASSERT
#if defined(_DEBUG) || defined(DEBUG)
# if (defined(_MSC_VER) && !defined(__clang__)) || !__has_builtin(__builtin_trap)
#  define UWVM_ASSERT(x)                                                                                                                                       \
      if(!__builtin_is_constant_evaluated() && !(x)) ::std::abort()
# else
#  define UWVM_ASSERT(x)                                                                                                                                       \
      if(!__builtin_is_constant_evaluated() && !(x)) __builtin_trap()
# endif
#else
# define UWVM_ASSERT(x) ((void)0)
#endif

/// @brief        Specify that a type is trivially relocatable if it meets certain conditions.
/// @see          trivially_relocatable_if_eligible
#pragma push_macro("UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE")
#undef UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
#if defined(__cpp_trivial_relocatability)
# undef UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
# define UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE trivially_relocatable_if_eligible
#else
# define UWVM_TRIVIALLY_RELOCATABLE_IF_ELIGIBLE
#endif

/// @brief        Indicates that the function will throw a Herbception exception.
/// @see          https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0709r4.pdf
#pragma push_macro("UWVM_THROWS")
#undef UWVM_THROWS
#if defined(__cpp_herbception)
# define UWVM_THROWS throws
#else
# define UWVM_THROWS
#endif

/// @brief        Indicates that a function is unlikely to be called frequently.
/// @details      on gcc, clang: [[__gnu__::__cold__]]
#pragma push_macro("UWVM_GNU_COLD")
#undef UWVM_GNU_COLD
#if __has_cpp_attribute(__gnu__::__cold__)
# define UWVM_GNU_COLD [[__gnu__::__cold__]]
#else
# define UWVM_GNU_COLD
#endif

/// @brief        Indicates that a function is likely to be called frequently.
/// @details      on gcc, clang: [[__gnu__::__hot__]]
#pragma push_macro("UWVM_GNU_HOT")
#undef UWVM_GNU_HOT
#if __has_cpp_attribute(__gnu__::__hot__)
# define UWVM_GNU_HOT [[__gnu__::__hot__]]
#else
# define UWVM_GNU_HOT
#endif
