﻿#pragma once

// Don't forget to rerun codegen/win32mangling

namespace fast_io::win32
{

FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetLastError() noexcept FAST_IO_WINSTDCALL_RENAME(GetLastError, 0);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL LoadLibraryA(char const *) noexcept FAST_IO_WINSTDCALL_RENAME(LoadLibraryA, 4);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL LoadLibraryW(char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(LoadLibraryW, 4);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL LoadLibraryExA(char const *, void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(LoadLibraryExA, 12);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL LoadLibraryExW(char16_t const *, void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(LoadLibraryExW, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL FormatMessageA(::std::uint_least32_t, char const *, ::std::uint_least32_t, ::std::uint_least32_t, char *, ::std::uint_least32_t, void /*va_list*/ *) noexcept FAST_IO_WINSTDCALL_RENAME(FormatMessageA, 28);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL FormatMessageW(::std::uint_least32_t, char16_t const *, ::std::uint_least32_t, ::std::uint_least32_t, char16_t *, ::std::uint_least32_t, void /*va_list*/ *) noexcept FAST_IO_WINSTDCALL_RENAME(FormatMessageW, 28);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateFileMappingA(void *, ::fast_io::win32::security_attributes *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, char const *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateFileMappingA, 24);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateFileMappingW(void *, ::fast_io::win32::security_attributes *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateFileMappingW, 24);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL MapViewOfFile(void *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::size_t) noexcept FAST_IO_WINSTDCALL_RENAME(MapViewOfFile, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetEndOfFile(void *) noexcept FAST_IO_WINSTDCALL_RENAME(SetEndOfFile, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL UnmapViewOfFile(void const *) noexcept FAST_IO_WINSTDCALL_RENAME(UnmapViewOfFile, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WriteFile(void *, void const *, ::std::uint_least32_t, ::std::uint_least32_t *, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(WriteFile, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ReadFile(void *, void const *, ::std::uint_least32_t, ::std::uint_least32_t *, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(ReadFile, 20);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL SetFilePointer(void *, ::std::int_least32_t, ::std::int_least32_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetFilePointer, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetFilePointerEx(void *, ::std::int_least64_t, ::std::int_least64_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetFilePointerEx, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL DuplicateHandle(void *, void *, void *, void **, ::std::uint_least32_t, int, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(DuplicateHandle, 28);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL GetStdHandle(::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetStdHandle, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CreatePipe(void **, void **, ::fast_io::win32::security_attributes *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(CreatePipe, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL FreeLibrary(void *) noexcept FAST_IO_WINSTDCALL_RENAME(FreeLibrary, 4);
FAST_IO_DLLIMPORT ::fast_io::win32::farproc FAST_IO_WINSTDCALL GetProcAddress(void *, char const *) noexcept FAST_IO_WINSTDCALL_RENAME(GetProcAddress, 8);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL GetModuleHandleA(char const *) noexcept FAST_IO_WINSTDCALL_RENAME(GetModuleHandleA, 4);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL GetModuleHandleW(char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(GetModuleHandleW, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL WaitForSingleObject(void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(WaitForSingleObject, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL CancelIo(void *) noexcept FAST_IO_WINSTDCALL_RENAME(CancelIo, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetFileInformationByHandle(void *__restrict, ::fast_io::win32::by_handle_file_information *__restrict) noexcept FAST_IO_WINSTDCALL_RENAME(GetFileInformationByHandle, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetUserDefaultLocaleName(char16_t *, int) noexcept FAST_IO_WINSTDCALL_RENAME(GetUserDefaultLocaleName, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetUserDefaultLCID() noexcept FAST_IO_WINSTDCALL_RENAME(GetUserDefaultLCID, 0);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL GetSystemTimePreciseAsFileTime(::fast_io::win32::filetime *) noexcept FAST_IO_WINSTDCALL_RENAME(GetSystemTimePreciseAsFileTime, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL GetSystemTimeAsFileTime(::fast_io::win32::filetime *) noexcept FAST_IO_WINSTDCALL_RENAME(GetSystemTimeAsFileTime, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL QueryUnbiasedInterruptTime(::std::uint_least64_t *) noexcept FAST_IO_WINSTDCALL_RENAME(QueryUnbiasedInterruptTime, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL QueryPerformanceCounter(::std::int_least64_t *) noexcept FAST_IO_WINSTDCALL_RENAME(QueryPerformanceCounter, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL QueryPerformanceFrequency(::std::int_least64_t *) noexcept FAST_IO_WINSTDCALL_RENAME(QueryPerformanceFrequency, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetProcessTimes(void *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *) noexcept FAST_IO_WINSTDCALL_RENAME(GetProcessTimes, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetThreadTimes(void *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *, ::fast_io::win32::filetime *) noexcept FAST_IO_WINSTDCALL_RENAME(GetThreadTimes, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetHandleInformation(void *, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(GetHandleInformation, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetHandleInformation(void *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetHandleInformation, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetTempPathA(::std::uint_least32_t, char *buffer) noexcept FAST_IO_WINSTDCALL_RENAME(GetTempPathA, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetTempPathW(::std::uint_least32_t, char16_t *buffer) noexcept FAST_IO_WINSTDCALL_RENAME(GetTempPathW, 8);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateFileA(char const *, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::security_attributes *, ::std::uint_least32_t, ::std::uint_least32_t, void *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateFileA, 28);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateFileW(char16_t const *, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::security_attributes *, ::std::uint_least32_t, ::std::uint_least32_t, void *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateFileW, 28);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateIoCompletionPort(void *, void *, ::std::size_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(CreateIoCompletionPort, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SystemFunction036(void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SystemFunction036, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CloseHandle(void *) noexcept FAST_IO_WINSTDCALL_RENAME(CloseHandle, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL LockFileEx(void *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(LockFileEx, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL UnlockFileEx(void *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(UnlockFileEx, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL DeviceIoControl(void *, ::std::uint_least32_t, void *, ::std::uint_least32_t, void *, ::std::uint_least32_t, void *, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(DeviceIoControl, 32);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetFileType(void *) noexcept FAST_IO_WINSTDCALL_RENAME(GetFileType, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetACP() noexcept FAST_IO_WINSTDCALL_RENAME(GetACP, 0);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetEnvironmentVariableA(char const *, char *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetEnvironmentVariableA, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetEnvironmentVariableW(char16_t const *, char16_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetEnvironmentVariableW, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL MessageBoxA(void *, char const *, char const *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(MessageBoxA, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL MessageBoxW(void *, char16_t const *, char16_t const *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(MessageBoxW, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetConsoleMode(void *, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(GetConsoleMode, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetConsoleMode(void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetConsoleMode, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ReadConsoleA(void *, void *, ::std::uint_least32_t, ::std::uint_least32_t *, void *) noexcept FAST_IO_WINSTDCALL_RENAME(ReadConsoleA, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ReadConsoleW(void *, void *, ::std::uint_least32_t, ::std::uint_least32_t *, void *) noexcept FAST_IO_WINSTDCALL_RENAME(ReadConsoleW, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WriteConsoleA(void *, void const *, ::std::uint_least32_t, ::std::uint_least32_t *, void *) noexcept FAST_IO_WINSTDCALL_RENAME(WriteConsoleA, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WriteConsoleW(void *, void const *, ::std::uint_least32_t, ::std::uint_least32_t *, void *) noexcept FAST_IO_WINSTDCALL_RENAME(WriteConsoleW, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetConsoleScreenBufferInfo(void *, ::fast_io::win32::console_screen_buffer_info *) noexcept FAST_IO_WINSTDCALL_RENAME(GetConsoleScreenBufferInfo, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ScrollConsoleScreenBufferA(void *, ::fast_io::win32::small_rect const *, ::fast_io::win32::small_rect const *, ::fast_io::win32::coord, ::fast_io::win32::char_info const *) noexcept FAST_IO_WINSTDCALL_RENAME(ScrollConsoleScreenBufferA, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ScrollConsoleScreenBufferW(void *, ::fast_io::win32::small_rect const *, ::fast_io::win32::small_rect const *, ::fast_io::win32::coord, ::fast_io::win32::char_info const *) noexcept FAST_IO_WINSTDCALL_RENAME(ScrollConsoleScreenBufferW, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetConsoleCursorPosition(void *, ::fast_io::win32::coord) noexcept FAST_IO_WINSTDCALL_RENAME(SetConsoleCursorPosition, 8);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL InitializeCriticalSection(void *) noexcept FAST_IO_WINSTDCALL_RENAME(InitializeCriticalSection, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL EnterCriticalSection(void *) noexcept FAST_IO_WINSTDCALL_RENAME(EnterCriticalSection, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL TryEnterCriticalSection(void *) noexcept FAST_IO_WINSTDCALL_RENAME(TryEnterCriticalSection, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL LeaveCriticalSection(void *) noexcept FAST_IO_WINSTDCALL_RENAME(LeaveCriticalSection, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL DeleteCriticalSection(void *) noexcept FAST_IO_WINSTDCALL_RENAME(DeleteCriticalSection, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSADuplicateSocketA(void *, ::std::uint_least32_t, ::fast_io::win32::wsaprotocol_infoa *) noexcept FAST_IO_WINSTDCALL_RENAME(WSADuplicateSocketA, 12);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL WSADuplicateSocketW(void *, ::std::uint_least32_t, ::fast_io::win32::wsaprotocol_infow *) noexcept FAST_IO_WINSTDCALL_RENAME(WSADuplicateSocketW, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSACleanup() noexcept FAST_IO_WINSTDCALL_RENAME(WSACleanup, 0);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSAStartup(::std::uint_least32_t, ::fast_io::win32::wsadata *) noexcept FAST_IO_WINSTDCALL_RENAME(WSAStartup, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSAGetLastError() noexcept FAST_IO_WINSTDCALL_RENAME(WSAGetLastError, 0);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL closesocket(::std::size_t) noexcept FAST_IO_WINSTDCALL_RENAME(closesocket, 4);
FAST_IO_DLLIMPORT ::std::size_t FAST_IO_WINSTDCALL WSASocketW(int, int, int, ::fast_io::win32::wsaprotocol_infow *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(WSASocketW, 24);
FAST_IO_DLLIMPORT ::std::size_t FAST_IO_WINSTDCALL WSASocketA(int, int, int, ::fast_io::win32::wsaprotocol_infoa *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(WSASocketA, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL bind(::std::size_t, void const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(bind, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL listen(::std::size_t, int) noexcept FAST_IO_WINSTDCALL_RENAME(listen, 8);
FAST_IO_DLLIMPORT ::std::size_t FAST_IO_WINSTDCALL WSAAccept(::std::size_t, void const *, int *, ::fast_io::win32::lpconditionproc, ::std::size_t) noexcept FAST_IO_WINSTDCALL_RENAME(WSAAccept, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ioctlsocket(::std::size_t, long, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(ioctlsocket, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL sendto(::std::size_t, char const *, int, int, void const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(sendto, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSASend(::std::size_t, ::fast_io::win32::wsabuf *, ::std::uint_least32_t, ::std::uint_least32_t *, ::std::uint_least32_t, ::fast_io::win32::overlapped *, ::fast_io::win32::lpwsaoverlapped_completion_routine) noexcept FAST_IO_WINSTDCALL_RENAME(WSASend, 28);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSASendMsg(::std::size_t, ::fast_io::win32::wsamsg *, ::std::uint_least32_t, ::std::uint_least32_t *, ::fast_io::win32::overlapped *, ::fast_io::win32::lpwsaoverlapped_completion_routine) noexcept FAST_IO_WINSTDCALL_RENAME(WSASendMsg, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSASendTo(::std::size_t, ::fast_io::win32::wsabuf *, ::std::uint_least32_t, ::std::uint_least32_t *, ::std::uint_least32_t, void const *, int, ::fast_io::win32::overlapped *, ::fast_io::win32::lpwsaoverlapped_completion_routine) noexcept FAST_IO_WINSTDCALL_RENAME(WSASendTo, 36);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL recv(::std::size_t, char *buf, int len, int flags) noexcept FAST_IO_WINSTDCALL_RENAME(recv, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL recvfrom(::std::size_t, char *, int, int, void *, int *) noexcept FAST_IO_WINSTDCALL_RENAME(recvfrom, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSARecv(::std::size_t, ::fast_io::win32::wsabuf *, ::std::uint_least32_t, ::std::uint_least32_t *, ::std::uint_least32_t *, ::fast_io::win32::overlapped *, ::fast_io::win32::lpwsaoverlapped_completion_routine) noexcept FAST_IO_WINSTDCALL_RENAME(WSARecv, 28);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSARecvFrom(::std::size_t, ::fast_io::win32::wsabuf *, ::std::uint_least32_t, ::std::uint_least32_t *, ::std::uint_least32_t *, void *, int *, ::fast_io::win32::overlapped *, ::fast_io::win32::lpwsaoverlapped_completion_routine) noexcept FAST_IO_WINSTDCALL_RENAME(WSARecvFrom, 36);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL connect(::std::size_t, void const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(connect, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL WSAConnect(::std::size_t, void const *, int, ::fast_io::win32::wsabuf *, ::fast_io::win32::wsabuf *, ::fast_io::win32::qualityofservice *, ::fast_io::win32::qualityofservice *) noexcept FAST_IO_WINSTDCALL_RENAME(WSAConnect, 28);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL shutdown(::std::size_t, void const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(shutdown, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetCurrentProcessId() noexcept FAST_IO_WINSTDCALL_RENAME(GetCurrentProcessId, 0);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL FlushFileBuffers(void *) noexcept FAST_IO_WINSTDCALL_RENAME(FlushFileBuffers, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetQueuedCompletionStatus(void *, ::std::uint_least32_t *, ::std::size_t *, ::fast_io::win32::overlapped *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetQueuedCompletionStatus, 20);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL freeaddrinfo(::fast_io::win32::win32_addrinfo_9xa *) noexcept FAST_IO_WINSTDCALL_RENAME(freeaddrinfo, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL FreeAddrInfoW(::fast_io::win32::win32_addrinfo_ntw *) noexcept FAST_IO_WINSTDCALL_RENAME(FreeAddrInfoW, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL getaddrinfo(char const *, char const *, ::fast_io::win32::win32_addrinfo_9xa const *, ::fast_io::win32::win32_addrinfo_9xa **) noexcept FAST_IO_WINSTDCALL_RENAME(getaddrinfo, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetAddrInfoW(char16_t const *, char16_t const *, ::fast_io::win32::win32_addrinfo_ntw const *, ::fast_io::win32::win32_addrinfo_ntw **) noexcept FAST_IO_WINSTDCALL_RENAME(GetAddrInfoW, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CryptAcquireContextA(::std::size_t *, char8_t const *, char8_t const *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(CryptAcquireContextA, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CryptAcquireContextW(::std::size_t *, char16_t const *, char16_t const *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(CryptAcquireContextW, 20);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CryptReleaseContext(::std::size_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(CryptReleaseContext, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CryptGenRandom(::std::size_t, ::std::uint_least32_t, char unsigned *) noexcept FAST_IO_WINSTDCALL_RENAME(CryptGenRandom, 12);
FAST_IO_DLLIMPORT ::std::int_least32_t FAST_IO_WINSTDCALL RegOpenKeyA(::std::size_t, char8_t const *, ::std::size_t *) noexcept FAST_IO_WINSTDCALL_RENAME(RegOpenKeyA, 12);
FAST_IO_DLLIMPORT ::std::int_least32_t FAST_IO_WINSTDCALL RegOpenKeyW(::std::size_t, char16_t const *, ::std::size_t *) noexcept FAST_IO_WINSTDCALL_RENAME(RegOpenKeyW, 12);
FAST_IO_DLLIMPORT ::std::int_least32_t FAST_IO_WINSTDCALL RegQueryValueExA(::std::size_t, char8_t const *, ::std::uint_least32_t *, ::std::uint_least32_t *, void *, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(RegQueryValueExA, 24);
FAST_IO_DLLIMPORT ::std::int_least32_t FAST_IO_WINSTDCALL RegQueryValueExW(::std::size_t, char16_t const *, ::std::uint_least32_t *, ::std::uint_least32_t *, void *, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(RegQueryValueExW, 24);
FAST_IO_DLLIMPORT ::std::int_least32_t FAST_IO_WINSTDCALL RegCloseKey(::std::size_t) noexcept FAST_IO_WINSTDCALL_RENAME(RegCloseKey, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetTimeZoneInformation(::fast_io::win32::time_zone_information *) noexcept FAST_IO_WINSTDCALL_RENAME(GetTimeZoneInformation, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetConsoleCP(::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetConsoleCP, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetConsoleOutputCP(::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetConsoleOutputCP, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetConsoleCP() noexcept FAST_IO_WINSTDCALL_RENAME(GetConsoleCP, 0);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetConsoleOutputCP() noexcept FAST_IO_WINSTDCALL_RENAME(GetConsoleOutputCP, 0);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL GetSystemInfo(::fast_io::win32::system_info *) noexcept FAST_IO_WINSTDCALL_RENAME(GetSystemInfo, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetFileInformationByHandle(void *, ::fast_io::win32::file_info_by_handle_class, void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetFileInformationByHandle, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetFileTime(void *, ::fast_io::win32::filetime const *, ::fast_io::win32::filetime const *, ::fast_io::win32::filetime const *) noexcept FAST_IO_WINSTDCALL_RENAME(SetFileTime, 16);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL AcquireSRWLockExclusive(void *) noexcept FAST_IO_WINSTDCALL_RENAME(AcquireSRWLockExclusive, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL TryAcquireSRWLockExclusive(void *) noexcept FAST_IO_WINSTDCALL_RENAME(TryAcquireSRWLockExclusive, 4);
FAST_IO_DLLIMPORT void FAST_IO_WINSTDCALL ReleaseSRWLockExclusive(void *) noexcept FAST_IO_WINSTDCALL_RENAME(ReleaseSRWLockExclusive, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CreateProcessW(char16_t const *, char16_t *, ::fast_io::win32::security_attributes *, ::fast_io::win32::security_attributes *, int, ::std::uint_least32_t, void *, char16_t const *, ::fast_io::win32::startupinfow *, ::fast_io::win32::process_information *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateProcessW, 40);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CreateProcessA(char const *, char *, ::fast_io::win32::security_attributes *, ::fast_io::win32::security_attributes *, int, ::std::uint_least32_t, void *, char16_t const *, ::fast_io::win32::startupinfoa *, ::fast_io::win32::process_information *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateProcessA, 40);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetMappedFileNameW(void *, void *, char16_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetMappedFileNameW, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetMappedFileNameA(void *, void *, char *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetMappedFileNameA, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL K32GetMappedFileNameW(void *, void *, char16_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(K32GetMappedFileNameW, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL K32GetMappedFileNameA(void *, void *, char *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(K32GetMappedFileNameA, 16);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL GetExitCodeProcess(void *, ::std::uint_least32_t *) noexcept FAST_IO_WINSTDCALL_RENAME(GetExitCodeProcess, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL QueryDosDeviceW(char16_t const *, char16_t *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(QueryDosDeviceW, 12);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL QueryDosDeviceA(char const *, char *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(QueryDosDeviceA, 12);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL FindFirstFileW(char16_t const *, ::fast_io::win32::win32_find_dataw *) noexcept FAST_IO_WINSTDCALL_RENAME(FindFirstFileW, 8);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL FindFirstFileA(char const *, ::fast_io::win32::win32_find_dataa *) noexcept FAST_IO_WINSTDCALL_RENAME(FindFirstFileA, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL FindNextFileW(void *, ::fast_io::win32::win32_find_dataw *) noexcept FAST_IO_WINSTDCALL_RENAME(FindNextFileW, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL FindNextFileA(void *, ::fast_io::win32::win32_find_dataa *) noexcept FAST_IO_WINSTDCALL_RENAME(FindNextFileA, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL FindClose(void *) noexcept FAST_IO_WINSTDCALL_RENAME(FindClose, 4);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL ShellExecuteW(void *, char16_t const *, char16_t const *, char16_t const *, char16_t const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(ShellExecuteW, 24);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL ShellExecuteA(void *, char const *, char const *, char const *, char const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(ShellExecuteA, 24);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL DeleteFileW(char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(DeleteFileW, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL DeleteFileA(char const *) noexcept FAST_IO_WINSTDCALL_RENAME(DeleteFileA, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL RemoveDirectoryW(char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(RemoveDirectoryW, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL RemoveDirectoryA(char const *) noexcept FAST_IO_WINSTDCALL_RENAME(RemoveDirectoryA, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CreateDirectoryW(char16_t const *, ::fast_io::win32::security_attributes *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateDirectoryW, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CreateDirectoryA(char const *, ::fast_io::win32::security_attributes *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateDirectoryA, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetFileAttributesW(char16_t const *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetFileAttributesW, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL SetFileAttributesA(char const *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(SetFileAttributesA, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetFileAttributesW(char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(GetFileAttributesW, 4);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetFileAttributesA(char const *) noexcept FAST_IO_WINSTDCALL_RENAME(GetFileAttributesA, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CopyFileW(char16_t const *, char16_t const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(CopyFileW, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL CopyFileA(char const *, char const *, int) noexcept FAST_IO_WINSTDCALL_RENAME(CopyFileA, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL MoveFileW(char16_t const *, char16_t const *) noexcept FAST_IO_WINSTDCALL_RENAME(MoveFileW, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL MoveFileA(char const *, char const *) noexcept FAST_IO_WINSTDCALL_RENAME(MoveFileA, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL TerminateProcess(void *, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(TerminateProcess, 8);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetFinalPathNameByHandleW(void *, char16_t *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetFinalPathNameByHandleW, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetFinalPathNameByHandleA(void *, char *, ::std::uint_least32_t, ::std::uint_least32_t) noexcept FAST_IO_WINSTDCALL_RENAME(GetFinalPathNameByHandleA, 16);
FAST_IO_DLLIMPORT ::std::uint_least32_t FAST_IO_WINSTDCALL GetProcessId(void *) noexcept FAST_IO_WINSTDCALL_RENAME(GetProcessId, 4);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateNamedPipeW(char16_t const *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::security_attributes *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateNamedPipeW, 32);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateNamedPipeA(char const *, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::std::uint_least32_t, ::fast_io::win32::security_attributes *) noexcept FAST_IO_WINSTDCALL_RENAME(CreateNamedPipeA, 32);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL ConnectNamedPipe(void *, ::fast_io::win32::overlapped *) noexcept FAST_IO_WINSTDCALL_RENAME(ConnectNamedPipe, 8);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL DisconnectNamedPipe(void *) noexcept FAST_IO_WINSTDCALL_RENAME(DisconnectNamedPipe, 4);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL LookupPrivilegeValueA(char const *__restrict, char const *__restrict, ::std::int_least64_t *) noexcept FAST_IO_WINSTDCALL_RENAME(LookupPrivilegeValueA, 12);
FAST_IO_DLLIMPORT int FAST_IO_WINSTDCALL LookupPrivilegeValueW(char16_t const *__restrict, char16_t const *__restrict, ::std::int_least64_t *) noexcept FAST_IO_WINSTDCALL_RENAME(LookupPrivilegeValueW, 12);
FAST_IO_DLLIMPORT void *FAST_IO_WINSTDCALL CreateThread(security_attributes *, ::std::size_t, ::std::uint_least32_t (FAST_IO_WINSTDCALL*)(void*), void*, ::std::uint_least32_t, ::std::uint_least32_t*) noexcept FAST_IO_WINSTDCALL_RENAME(CreateThread, 24);
FAST_IO_DLLIMPORT char16_t **FAST_IO_WINSTDCALL CommandLineToArgvW(char16_t const *, int *) noexcept FAST_IO_WINSTDCALL_RENAME(CommandLineToArgvW, 8);

} // namespace fast_io::win32
