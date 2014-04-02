/*
 *--------------------------------------------------------------------------
 *   File Name:	assert.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:31:47 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_ASSERT_H
#define	_ASSERT_H



#ifndef	__STRING
# define __STRING(x)	#x
#endif

#define	assert(exp)							\
( (exp)									\
? (void) (0)								\
: assert_fail(__STRING(exp), __FILE__, __LINE__, __PRETTY_FUNCTION__))

#endif //_ASSERT_H
