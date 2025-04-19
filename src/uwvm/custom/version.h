/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-24
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

#ifdef UWVM_MODULE
export import utils.version;  // print defined method should be export
#else
// std
# include <cstdint>
# include <cstddef>
// import
# include <utils/version/impl.h>
#endif

#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT
#endif

UWVM_MODULE_EXPORT namespace uwvm::custom
{
    /// @brief      UWVM Version
    /// @details    2.major.minor.patch
#if defined(UWVM_VERSION_X) && defined(UWVM_VERSION_Y) && defined(UWVM_VERSION_Z) && defined(UWVM_VERSION_S)
    inline constexpr ::utils::version uwvm_version{UWVM_VERSION_X, UWVM_VERSION_Y, UWVM_VERSION_Z, UWVM_VERSION_S};
#else
    inline constexpr ::utils::version uwvm_version{0, 0, 0, 0};
#endif
}  // namespace uwvm::custom
