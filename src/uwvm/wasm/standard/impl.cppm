﻿/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       WebAssembly Standard
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-02
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

export module uwvm.wasm.standard;
export import uwvm.wasm.standard.wasm1;
export import uwvm.wasm.standard.wasm1p1;
export import uwvm.wasm.standard.wasm2;
export import uwvm.wasm.standard.wasm2_MultiMemory;
export import uwvm.wasm.standard.wasm2_TailCalls;
export import uwvm.wasm.standard.wasm2_TailCalls_FunctionReference;
export import uwvm.wasm.standard.wasm2_TailCalls_FunctionReference_GC;
export import uwvm.wasm.standard.wasm2_thread;
export import uwvm.wasm.standard.wasm3;
