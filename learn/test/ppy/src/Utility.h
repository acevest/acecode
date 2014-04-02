/*
 *--------------------------------------------------------------------------
 *   File Name:	Utility.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 23 15:54:55 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_UTILITY_H
#define	_PPY_UTILITY_H

#include <memory.h>
#include <cerrno>

#include <sys/types.h>
#include <sys/socket.h>

#if	ENABLE_ASSERT
#define	PPY_ASSERT(x) assert(x)
#else
#define	PPY_ASSERT(x)
#endif

namespace ppy {
namespace util {

} // end namespace util
} // end namespace ppy

#endif //_PPY_UTILITY_H
