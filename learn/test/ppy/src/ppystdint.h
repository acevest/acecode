/*
 *--------------------------------------------------------------------------
 *   File Name:	ppystdint.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 10 15:55:29 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_PPYSTDINT_H
#define	_PPY_PPYSTDINT_H

#include <stdio.h>

#if defined(_WIN32) && !defined(__MINGW32__)

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef	unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#else

#include <stdint.h>

#endif

#endif //_PPY_PPYSTDINT_H
