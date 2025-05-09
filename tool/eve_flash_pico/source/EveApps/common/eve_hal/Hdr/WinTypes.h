/**
 * @file WinTypes.h
 * @brief Window OS types
 *
 * @author Bridgetek
 *
 * @date 2018
 * 
 * MIT License
 *
 * Copyright (c) [2019] [Bridgetek Pte Ltd (BRTChip)]
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef __WINDOWS_TYPES__
#define __WINDOWS_TYPES__

#define MAX_NUM_DEVICES 50
#include <sys/time.h>

typedef unsigned int DWORD;
typedef unsigned int ULONG;
typedef unsigned short USHORT;
typedef unsigned short SHORT;
typedef unsigned char UCHAR;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef BYTE *LPBYTE;
typedef unsigned int BOOL;
typedef unsigned char BOOLEAN;
typedef unsigned char CHAR;
typedef BOOL *LPBOOL;
typedef UCHAR *PUCHAR;
typedef const char *LPCSTR;
typedef char *PCHAR;
typedef void *PVOID;
typedef void *HANDLE;
typedef unsigned int LONG;
typedef int INT;
typedef unsigned int UINT;
typedef char *LPSTR;
typedef char *LPTSTR;
typedef DWORD *LPDWORD;
typedef WORD *LPWORD;
typedef ULONG *PULONG;
typedef PVOID LPVOID;
typedef void VOID;
typedef unsigned long long int ULONGLONG;

typedef struct _OVERLAPPED
{
	DWORD Internal;
	DWORD InternalHigh;
	DWORD Offset;
	DWORD OffsetHigh;
	HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _SECURITY_ATTRIBUTES
{
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

typedef struct timeval SYSTEMTIME;
typedef struct timeval FILETIME;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//
// Modem Status Flags
//
#define MS_CTS_ON ((DWORD)0x0010)
#define MS_DSR_ON ((DWORD)0x0020)
#define MS_RING_ON ((DWORD)0x0040)
#define MS_RLSD_ON ((DWORD)0x0080)

//
// Error Flags
//

#define CE_RXOVER 0x0001 // Receive Queue overflow
#define CE_OVERRUN 0x0002 // Receive Overrun Error
#define CE_RXPARITY 0x0004 // Receive Parity Error
#define CE_FRAME 0x0008 // Receive Framing error
#define CE_BREAK 0x0010 // Break Detected
#define CE_TXFULL 0x0100 // TX Queue is full
#define CE_PTO 0x0200 // LPTx Timeout
#define CE_IOE 0x0400 // LPTx I/O Error
#define CE_DNS 0x0800 // LPTx Device not selected
#define CE_OOP 0x1000 // LPTx Out-Of-Paper
#define CE_MODE 0x8000 // Requested mode unsupported

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE 0xFFFFFFFF
#endif

#endif
