/*************************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)          *
 * Copyright (c) 2025-present UlteSoft. All rights reserved. *
 * Licensed under the APL-2 License (see LICENSE file).      *
 *************************************************************/

/**
 * @file        main.cc
 * @brief       main function for crt startup
 * @details     This function does nothing but call the cpp boot method of the other module
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-20
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

#include <uwvm2/utils/macro/push_macros.h>

#ifdef UWVM_MODULE
import uwvm2.uwvm.crtmain;
#else
// import
# include "crtmain/impl.h"
#endif

/// @brief      (crt) main func. The main function is a special function, but there are still meaningless [[gnu::used]].
/// @param      argc Argument Count
/// @param      argv Argument Vector
/// @return     exit(3)
/// @see        ::uwvm2::uwvm::uwvm_main()

UWVM_GNU_USED int main(int argc, char** argv) { return ::uwvm2::uwvm::uwvm_main(argc, argv); }

#include <uwvm2/utils/macro/pop_macros.h>
