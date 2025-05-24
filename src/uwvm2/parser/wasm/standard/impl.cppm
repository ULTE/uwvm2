/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the ASHP-1.0 License (see LICENSE file).   *
 *************************************************************/

/**
 * @brief       WebAssembly Standard
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-02
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

module;

export module uwvm2.parser.wasm.standard;
export import uwvm2.parser.wasm.standard.wasm1;
export import uwvm2.parser.wasm.standard.wasm1p1;
export import uwvm2.parser.wasm.standard.wasm2;
export import uwvm2.parser.wasm.standard.wasm2_MultiMemory;
export import uwvm2.parser.wasm.standard.wasm2_TailCalls;
export import uwvm2.parser.wasm.standard.wasm2_TailCalls_FunctionReference;
export import uwvm2.parser.wasm.standard.wasm2_TailCalls_FunctionReference_GC;
export import uwvm2.parser.wasm.standard.wasm2_thread;
export import uwvm2.parser.wasm.standard.wasm3;

#ifndef UWVM_MODULE
# define UWVM_MODULE
#endif
#ifndef UWVM_MODULE_EXPORT
# define UWVM_MODULE_EXPORT export
#endif

#include "impl.h"
