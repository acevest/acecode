/*
 *--------------------------------------------------------------------------
 *   File Name:	types.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 22:54:15 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_TYPES_H
#define	_TYPES_H

#ifndef __ASSEMBLY__

typedef unsigned int size_t;
typedef int ssize_t;

typedef long time_t; /* time in second since 1 Jan 1970 0000 GMT */

typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned long       uint32_t;
typedef unsigned long long  uint64_t;

typedef	char        int8_t;
typedef	short       int16_t;
typedef	long        int32_t;
typedef long long   int64_t;

typedef	uint8_t     u8_t;
typedef uint16_t    u16_t;
typedef uint32_t    u32_t;
typedef uint64_t    u64_t;
typedef	int8_t      s8_t;
typedef int16_t     s16_t;
typedef int32_t     s32_t;
typedef int64_t     s64_t;

typedef uint32_t    vaddr_t;    /* virtual address */
typedef uint32_t    paddr_t;    /* physics address */

typedef	int	pid_t;

#define	NULL	((void *)0)

#endif

#endif //_TYPES_H
