/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @brief       Custom Page Sizes Proposal for WebAssembly
 * @details     antecedent dependency: WebAssembly Release 3.0 (Draft 2024-09-21)
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

#pragma once

#ifdef UWVM_MODULE
export module parser.wasm.proposal.custom_page_size;
export import parser.wasm.proposal.custom_page_size.type;
#else
# include "type/impl.h"
#endif
