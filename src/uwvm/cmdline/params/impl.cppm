/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-27
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

export module uwvm.cmdline.params;
export import :version;
export import :run;
export import :help;
export import :mode;
export import :wasm_abi;
export import :wasm_binfmt;
export import :debug_output;

#ifdef _DEBUG
export import :test;
#endif

#ifndef UWVM_MODULE
# define UWVM_MODULE
#endif
#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT export
#endif

#include "impl.h"
