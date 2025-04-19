/********************************************************
 * Ultimate WebAssembly Virtual Machine (Version 2)     *
 * Copyright (c) 2025 MacroModel. All rights reserved.  *
 * Licensed under the APL-2 License (see LICENSE file). *
 ********************************************************/

/**
 * @author      MacroModel
 * @version     2.0.0
 * @date        2025-03-23
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

/// @brief      The following are the macros used by ansi escape sequences.
/// @details    Use `push_macro` to avoid side effects on existing macros. Please use `pop_macro` in conjunction.

#pragma once

/// @brief Text color variables:

#pragma push_macro("UWVM_AES_U8_BLACK")
#undef UWVM_AES_U8_BLACK
#define UWVM_AES_U8_BLACK u8"\033[30m"

#pragma push_macro("UWVM_AES_U8_RED")
#undef UWVM_AES_U8_RED
#define UWVM_AES_U8_RED u8"\033[31m"

#pragma push_macro("UWVM_AES_U8_GREEN")
#undef UWVM_AES_U8_GREEN
#define UWVM_AES_U8_GREEN u8"\033[32m"

#pragma push_macro("UWVM_AES_U8_ORANGE")
#undef UWVM_AES_U8_ORANGE
#define UWVM_AES_U8_ORANGE u8"\033[33m"

#pragma push_macro("UWVM_AES_U8_BLUE")
#undef UWVM_AES_U8_BLUE
#define UWVM_AES_U8_BLUE u8"\033[34m"

#pragma push_macro("UWVM_AES_U8_PURPLE")
#undef UWVM_AES_U8_PURPLE
#define UWVM_AES_U8_PURPLE u8"\033[35m"

#pragma push_macro("UWVM_AES_U8_CYAN")
#undef UWVM_AES_U8_CYAN
#define UWVM_AES_U8_CYAN u8"\033[36m"

#pragma push_macro("UWVM_AES_U8_GRAY")
#undef UWVM_AES_U8_GRAY
#define UWVM_AES_U8_GRAY u8"\033[37m"

#pragma push_macro("UWVM_AES_U8_DK_GRAY")
#undef UWVM_AES_U8_DK_GRAY
#if defined(__DJGPP__)
# define UWVM_AES_U8_DK_GRAY UWVM_AES_U8_BLACK
#else
# define UWVM_AES_U8_DK_GRAY u8"\033[90m"
#endif

#pragma push_macro("UWVM_AES_U8_LT_RED")
#undef UWVM_AES_U8_LT_RED
#if defined(__DJGPP__)
# define UWVM_AES_U8_LT_RED UWVM_AES_U8_RED
#else
# define UWVM_AES_U8_LT_RED u8"\033[91m"
#endif

#pragma push_macro("UWVM_AES_U8_LT_GREEN")
#undef UWVM_AES_U8_LT_GREEN
#if defined(__DJGPP__)
# define UWVM_AES_U8_LT_GREEN UWVM_AES_U8_GREEN
#else
# define UWVM_AES_U8_LT_GREEN u8"\033[92m"
#endif

#pragma push_macro("UWVM_AES_U8_YELLOW")
#undef UWVM_AES_U8_YELLOW
#if defined(__DJGPP__)
# define UWVM_AES_U8_YELLOW UWVM_AES_U8_ORANGE
#else
# define UWVM_AES_U8_YELLOW u8"\033[93m"
#endif

#pragma push_macro("UWVM_AES_U8_LT_BLUE")
#undef UWVM_AES_U8_LT_BLUE
#if defined(__DJGPP__)
# define UWVM_AES_U8_LT_BLUE UWVM_AES_U8_BLUE
#else
# define UWVM_AES_U8_LT_BLUE u8"\033[94m"
#endif

#pragma push_macro("UWVM_AES_U8_LT_PURPLE")
#undef UWVM_AES_U8_LT_PURPLE
#if defined(__DJGPP__)
# define UWVM_AES_U8_LT_PURPLE UWVM_AES_U8_PURPLE
#else
# define UWVM_AES_U8_LT_PURPLE u8"\033[95m"
#endif

#pragma push_macro("UWVM_AES_U8_LT_CYAN")
#undef UWVM_AES_U8_LT_CYAN
#if defined(__DJGPP__)
# define UWVM_AES_U8_LT_CYAN UWVM_AES_U8_CYAN
#else
# define UWVM_AES_U8_LT_CYAN u8"\033[96m"
#endif

#pragma push_macro("UWVM_AES_U8_WHITE")
#undef UWVM_AES_U8_WHITE
#if defined(__DJGPP__)
# define UWVM_AES_U8_WHITE UWVM_AES_U8_GRAY
#else
# define UWVM_AES_U8_WHITE u8"\033[97m"
#endif

/// @brief Background color variables:

#pragma push_macro("UWVM_AES_U8_BG_BLACK")
#undef UWVM_AES_U8_BG_BLACK
#define UWVM_AES_U8_BG_BLACK u8"\033[40m"

#pragma push_macro("UWVM_AES_U8_BG_RED")
#undef UWVM_AES_U8_BG_RED
#define UWVM_AES_U8_BG_RED u8"\033[41m"

#pragma push_macro("UWVM_AES_U8_BG_GREEN")
#undef UWVM_AES_U8_BG_GREEN
#define UWVM_AES_U8_BG_GREEN u8"\033[42m"

#pragma push_macro("UWVM_AES_U8_BG_ORANGE")
#undef UWVM_AES_U8_BG_ORANGE
#define UWVM_AES_U8_BG_ORANGE u8"\033[43m"

#pragma push_macro("UWVM_AES_U8_BG_BLUE")
#undef UWVM_AES_U8_BG_BLUE
#define UWVM_AES_U8_BG_BLUE u8"\033[44m"

#pragma push_macro("UWVM_AES_U8_BG_PURPLE")
#undef UWVM_AES_U8_BG_PURPLE
#define UWVM_AES_U8_BG_PURPLE u8"\033[45m"

#pragma push_macro("UWVM_AES_U8_BG_CYAN")
#undef UWVM_AES_U8_BG_CYAN
#define UWVM_AES_U8_BG_CYAN u8"\033[46m"

#pragma push_macro("UWVM_AES_U8_BG_GRAY")
#undef UWVM_AES_U8_BG_GRAY
#define UWVM_AES_U8_BG_GRAY u8"\033[47m"

#pragma push_macro("UWVM_AES_U8_BG_DK_GRAY")
#undef UWVM_AES_U8_BG_DK_GRAY
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_DK_GRAY UWVM_AES_U8_BG_BLACK
#else
# define UWVM_AES_U8_BG_DK_GRAY u8"\033[100m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_LT_RED")
#undef UWVM_AES_U8_BG_LT_RED
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_LT_RED UWVM_AES_U8_BG_RED
#else
# define UWVM_AES_U8_BG_LT_RED u8"\033[101m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_LT_GREEN")
#undef UWVM_AES_U8_BG_LT_GREEN
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_LT_GREEN UWVM_AES_U8_BG_GREEN
#else
# define UWVM_AES_U8_BG_LT_GREEN u8"\033[102m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_YELLOW")
#undef UWVM_AES_U8_BG_YELLOW
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_YELLOW UWVM_AES_U8_BG_ORANGE
#else
# define UWVM_AES_U8_BG_YELLOW u8"\033[103m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_LT_BLUE")
#undef UWVM_AES_U8_BG_LT_BLUE
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_LT_BLUE UWVM_AES_U8_BG_BLUE
#else
# define UWVM_AES_U8_BG_LT_BLUE u8"\033[104m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_LT_PURPLE")
#undef UWVM_AES_U8_BG_LT_PURPLE
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_LT_PURPLE UWVM_AES_U8_BG_PURPLE
#else
# define UWVM_AES_U8_BG_LT_PURPLE u8"\033[105m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_LT_CYAN")
#undef UWVM_AES_U8_BG_LT_CYAN
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_LT_CYAN UWVM_AES_U8_BG_CYAN
#else
# define UWVM_AES_U8_BG_LT_CYAN u8"\033[106m"
#endif

#pragma push_macro("UWVM_AES_U8_BG_WHITE")
#undef UWVM_AES_U8_BG_WHITE
#if defined(__DJGPP__)
# define UWVM_AES_U8_BG_WHITE UWVM_AES_U8_BG_GRAY
#else
# define UWVM_AES_U8_BG_WHITE u8"\033[107m"
#endif

/// @brief Bold color variables:
#pragma push_macro("UWVM_AES_U8_BD_BLACK")
#undef UWVM_AES_U8_BD_BLACK
#define UWVM_AES_U8_BD_BLACK u8"\033[1;30m"

#pragma push_macro("UWVM_AES_U8_BD_RED")
#undef UWVM_AES_U8_BD_RED
#define UWVM_AES_U8_BD_RED u8"\033[1;31m"

#pragma push_macro("UWVM_AES_U8_BD_GREEN")
#undef UWVM_AES_U8_BD_GREEN
#define UWVM_AES_U8_BD_GREEN u8"\033[1;32m"

#pragma push_macro("UWVM_AES_U8_BD_ORANGE")
#undef UWVM_AES_U8_BD_ORANGE
#define UWVM_AES_U8_BD_ORANGE u8"\033[1;33m"

#pragma push_macro("UWVM_AES_U8_BD_BLUE")
#undef UWVM_AES_U8_BD_BLUE
#define UWVM_AES_U8_BD_BLUE u8"\033[1;34m"

#pragma push_macro("UWVM_AES_U8_BD_PURPLE")
#undef UWVM_AES_U8_BD_PURPLE
#define UWVM_AES_U8_BD_PURPLE u8"\033[1;35m"

#pragma push_macro("UWVM_AES_U8_BD_CYAN")
#undef UWVM_AES_U8_BD_CYAN
#define UWVM_AES_U8_BD_CYAN u8"\033[1;36m"

#pragma push_macro("UWVM_AES_U8_BD_GRAY")
#undef UWVM_AES_U8_BD_GRAY
#define UWVM_AES_U8_BD_GRAY u8"\033[1;37m"

/// @brief Style variables:

#pragma push_macro("UWVM_AES_U8_STY_BOLD")
#undef UWVM_AES_U8_STY_BOLD
#define UWVM_AES_U8_STY_BOLD u8"\033[1m"

#pragma push_macro("UWVM_AES_U8_STY_FAINT")
#undef UWVM_AES_U8_STY_FAINT
#define UWVM_AES_U8_STY_FAINT u8"\033[2m"

#pragma push_macro("UWVM_AES_U8_STY_ITALICS")
#undef UWVM_AES_U8_STY_ITALICS
#define UWVM_AES_U8_STY_ITALICS u8"\033[3m"

#pragma push_macro("UWVM_AES_U8_STY_UNDERLINE")
#undef UWVM_AES_U8_STY_UNDERLINE
#define UWVM_AES_U8_STY_UNDERLINE u8"\033[4m"

#pragma push_macro("UWVM_AES_U8_STY_BLINK")
#undef UWVM_AES_U8_STY_BLINK
#define UWVM_AES_U8_STY_BLINK u8"\033[5m"

#pragma push_macro("UWVM_AES_U8_STY_INVERSE")
#undef UWVM_AES_U8_STY_INVERSE
#define UWVM_AES_U8_STY_INVERSE u8"\033[7m"

#pragma push_macro("UWVM_AES_U8_STY_INVISIABLE")
#undef UWVM_AES_U8_STY_INVISIABLE
#define UWVM_AES_U8_STY_INVISIABLE u8"\033[8m"

#pragma push_macro("UWVM_AES_U8_STY_CROSSED")
#undef UWVM_AES_U8_STY_CROSSED
#define UWVM_AES_U8_STY_CROSSED u8"\033[9m"

#pragma push_macro("UWVM_AES_U8_STY_DOUBLE_UNDERLINE")
#undef UWVM_AES_U8_STY_DOUBLE_UNDERLINE
#define UWVM_AES_U8_STY_DOUBLE_UNDERLINE u8"\033[21m"

/// @brief Reset features commands

#pragma push_macro("UWVM_AES_U8_RST_ALL")
#undef UWVM_AES_U8_RST_ALL
#define UWVM_AES_U8_RST_ALL u8"\033[0m"

#pragma push_macro("UWVM_AES_U8_RST_COLOR")
#undef UWVM_AES_U8_RST_COLOR
#define UWVM_AES_U8_RST_COLOR u8"\033[39m"

#pragma push_macro("UWVM_AES_U8_RST_BG_COLOR")
#undef UWVM_AES_U8_RST_BG_COLOR
#define UWVM_AES_U8_RST_BG_COLOR u8"\033[49m"

#pragma push_macro("UWVM_AES_U8_RST_BD_COLOR")
#undef UWVM_AES_U8_RST_BD_COLOR
#define UWVM_AES_U8_RST_BD_COLOR u8"\033[22m\033[39m"

#pragma push_macro("UWVM_AES_U8_RST_BD_FT")
#undef UWVM_AES_U8_RST_BD_FT
#define UWVM_AES_U8_RST_BD_FT u8"\033[22m"

#pragma push_macro("UWVM_AES_U8_RST_ITALICS")
#undef UWVM_AES_U8_RST_ITALICS
#define UWVM_AES_U8_RST_ITALICS u8"\033[23m"

#pragma push_macro("UWVM_AES_U8_RST_UNDERLINE")
#undef UWVM_AES_U8_RST_UNDERLINE
#define UWVM_AES_U8_RST_UNDERLINE u8"\033[24m"

#pragma push_macro("UWVM_AES_U8_RST_BLINK")
#undef UWVM_AES_U8_RST_BLINK
#define UWVM_AES_U8_RST_BLINK u8"\033[25m"

#pragma push_macro("UWVM_AES_U8_RST_INVERSE")
#undef UWVM_AES_U8_RST_INVERSE
#define UWVM_AES_U8_RST_INVERSE u8"\033[27m"

#pragma push_macro("UWVM_AES_U8_RST_INVISIABLE")
#undef UWVM_AES_U8_RST_INVISIABLE
#define UWVM_AES_U8_RST_INVISIABLE u8"\033[28m"

#pragma push_macro("UWVM_AES_U8_RST_CROSS")
#undef UWVM_AES_U8_RST_CROSS
#define UWVM_AES_U8_RST_CROSS u8"\033[29m"

/// @brief Control sequences variables

/// @brief Hide cursor
#pragma push_macro("UWVM_AES_U8_CTRL_HCRS")
#undef UWVM_AES_U8_CTRL_HCRS
#define UWVM_AES_U8_CTRL_HCRS u8"\033[?25l"

/// @brief Show cursor
#pragma push_macro("UWVM_AES_U8_CTRL_SCRS")
#undef UWVM_AES_U8_CTRL_SCRS
#define UWVM_AES_U8_CTRL_SCRS u8"\033[?25h"

/// @brief RGB
#pragma push_macro("UWVM_AES_U8_RGB")
#undef UWVM_AES_U8_RGB
#define UWVM_AES_U8_RGB(r, g, b) u8"\033[38;2;" #r u8";" #g u8";" #b u8"m"
