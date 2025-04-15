﻿/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       WebAssembly Release 2.0 + multi-memory (Draft 2024-09-04)
 * @details     antecedent dependency: WebAssembly Release 2.0 (Draft 2025-01-30)
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-04-04
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

export module parser.wasm.standard.wasm2_MultiMemory;
export import parser.wasm.standard.wasm2;

#define UWVM_MODULE
#define UWVM_MODULE_EXPORT export

#include "impl.h"
