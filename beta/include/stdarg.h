/*
 *--------------------------------------------------------------------------
 *   File Name:	stdarg.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sun Oct  3 19:08:04 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_STDARG_H
#define	_STDARG_H

typedef	char *va_list;

#define	va_start(ap, last)	__builtin_va_start(ap, last)
#define	va_arg(ap, type)	__builtin_va_arg(ap, type)
#define	va_end(ap)		__builtin_va_end(ap)
#define	va_copy(dst, src)	__builtin_va_copy(dst, src)


#endif //_STDARG_H
