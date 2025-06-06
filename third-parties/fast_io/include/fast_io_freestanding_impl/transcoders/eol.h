﻿#pragma once

namespace fast_io
{

namespace transcoders
{

enum class eol_scheme
{
	lf,
	crlf,
	cr,
	nl, /*EBCDIC*/
#if 0
lfcr,
newline,
#endif
#if (defined(_WIN32) && !defined(__WINE__)) || defined(__CYGWIN__) || defined(__MSDOS__)
	native = crlf
#else
	native = lf
#endif
};

template <::std::integral chtype, eol_scheme fromscheme, eol_scheme toscheme>
struct basic_eol
{
	using char_type = chtype;
	using from_char_type = chtype;
	using to_char_type = chtype;
	bool last_unfinished{};

	inline constexpr transcode_result<char_type, char_type>
	transcode(char_type const *fromfirst, char_type const *fromlast, char_type *tofirst, char_type *tolast) noexcept
	{
		constexpr ::std::size_t initialdiffn{::fast_io::details::optimal_simd_vector_run_with_cpu_instruction_size};
		if constexpr (fromscheme == eol_scheme::lf && toscheme == eol_scheme::crlf)
		{
			if (last_unfinished)
			{
				if (tofirst == tolast)
				{
					return {fromfirst, tofirst};
				}
				*tofirst = char_literal_v<u8'\n', char_type>;
				++tofirst;
			}
			last_unfinished = false;
			if constexpr (0 < initialdiffn)
			{
				auto [fromit,
					  toit]{::fast_io::details::simd_lf_crlf_process_chars(fromfirst, fromlast, tofirst, tolast)};
				fromfirst = fromit;
				tofirst = toit;
			}
			for (; fromfirst != fromlast && tofirst != tolast;)
			{
				auto ch{*fromfirst};
				if (ch == char_literal_v<u8'\n', char_type>)
				{
					if (tofirst != tolast)
					{
						*tofirst = char_literal_v<u8'\r', char_type>;
						++tofirst;
						if (tofirst == tolast)
						{
							last_unfinished = true;
							break;
						}
					}
				}
				*tofirst = ch;
				++fromfirst;
				++tofirst;
			}
		}
		else if constexpr (fromscheme == eol_scheme::crlf && toscheme == eol_scheme::lf)
		{
			if (last_unfinished)
			{
				if (tofirst == tolast || fromfirst == fromlast)
				{
					return {fromfirst, tofirst};
				}
				auto ch{*fromfirst};
				if (ch == char_literal_v<u8'\n', char_type>)
				{
					*tofirst = char_literal_v<u8'\n', char_type>;
					++tofirst;
					++fromfirst;
				}
				else
				{
					*tofirst = char_literal_v<u8'\r', char_type>;
					++tofirst;
				}
			}
			last_unfinished = false;
			if constexpr (0 < initialdiffn)
			{
				auto [fromit,
					  toit]{::fast_io::details::simd_crlf_lf_process_chars(fromfirst, fromlast, tofirst, tolast)};
				fromfirst = fromit;
				tofirst = toit;
			}
			for (; fromfirst != fromlast && tofirst != tolast;)
			{
				auto ch{*fromfirst};
				if (ch == char_literal_v<u8'\r', char_type>)
				{
					if (fromfirst + 1 == fromlast)
					{
						last_unfinished = true;
						return {fromlast, tofirst};
					}
					auto tch{fromfirst[1]};
					if (tch == char_literal_v<u8'\n', char_type>)
					{
						ch = tch;
						++fromfirst;
					}
				}
				*tofirst = ch;
				++fromfirst;
				++tofirst;
			}
		}
		else if constexpr ((fromscheme == eol_scheme::lf && toscheme == eol_scheme::cr) ||
						   (fromscheme == eol_scheme::cr && toscheme == eol_scheme::lf))
		{
			constexpr bool cr{(fromscheme == eol_scheme::cr && toscheme == eol_scheme::lf)};
			if constexpr (0 < initialdiffn)
			{
				auto [fromit,
					  toit]{::fast_io::details::simd_lf_cr_process_chars<cr>(fromfirst, fromlast, tofirst, tolast)};
				fromfirst = fromit;
				tofirst = toit;
			}
			for (; fromfirst != fromlast && tofirst != tolast;)
			{
				auto ch{*fromfirst};
				if (ch == char_literal_v<(cr ? u8'\r' : u8'\n'), char_type>)
				{
					ch = char_literal_v<(cr ? u8'\n' : u8'\r'), char_type>;
				}
				*tofirst = ch;
				++fromfirst;
				++tofirst;
			}
		}
		else /*For debugging purposes*/
		{
			for (; fromfirst != fromlast && tofirst != tolast;)
			{
				*tofirst = *fromfirst;
				++fromfirst;
				++tofirst;
			}
		}
		return {fromfirst, tofirst};
	}
};

using lf_to_crlf = basic_eol<char, eol_scheme::lf, eol_scheme::crlf>;
using crlf_to_lf = basic_eol<char, eol_scheme::crlf, eol_scheme::lf>;

using wlf_to_crlf = basic_eol<wchar_t, eol_scheme::lf, eol_scheme::crlf>;
using wcrlf_to_lf = basic_eol<wchar_t, eol_scheme::crlf, eol_scheme::lf>;

using u8lf_to_crlf = basic_eol<char8_t, eol_scheme::lf, eol_scheme::crlf>;
using u8crlf_to_lf = basic_eol<char8_t, eol_scheme::crlf, eol_scheme::lf>;

using u16lf_to_crlf = basic_eol<char16_t, eol_scheme::lf, eol_scheme::crlf>;
using u16crlf_to_lf = basic_eol<char16_t, eol_scheme::crlf, eol_scheme::lf>;

using u32lf_to_crlf = basic_eol<char32_t, eol_scheme::lf, eol_scheme::crlf>;
using u32crlf_to_lf = basic_eol<char32_t, eol_scheme::crlf, eol_scheme::lf>;

} // namespace transcoders

} // namespace fast_io
