/***************************************************************************
                          windefs.h  -  description
                             -------------------
    begin                : Mon Jan 8 2001
    copyright            : (C) 2001 by Sven Fischer
    email                : fischer@deutaeit.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is copyrighted by DEUTA Werke GmbH, Germany.             *
 *   All rights reserved. Redistribution is not permitted.                 *
 *                                                                         *
 ***************************************************************************/
#ifndef __WINDEFS_H__
#define __WINDEFS_H__

//*#ifndef UINT

// Windows/DOS define wraparounds
//#include <string>

#define NEAR
#define FAR
#define __cdecl
#define WINAPI
#define PASCAL

#ifdef bool
#define BOOL bool
#ifndef FALSE
#define FALSE false
#endif
#ifndef TRUE
#define TRUE true
#endif
#else
#define BOOL unsigned short int
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#endif // bool

#define BYTE unsigned char
#define UINT unsigned int
#define WORD int
#define DWORD long int
#define CALLBACK

#if defined( __QNXNTO__ ) || defined( HAVE_STL )
#define LPCSTR std::string
#define LPSTR std::string
#else // string
// QNX4 workarounds
#include <stddef.h>
#define LPCSTR const char*
#define LPSTR char*
#define string String
#define pthread_t int
#endif // string

#ifdef __cplusplus
extern "C" {
#endif
  extern long int GetTickCount();
  extern void EnterCriticalSection(int*);
  extern void LeaveCriticalSection(int*);
#ifdef __cplusplus
}
#endif
//*#endif // UINT


#endif // __WINDEFS_H__
