/*
 *--------------------------------------------------------------------------
 *   File Name:	class.static.const.string.h
 * 
 * Create Date: Fri Aug 21 19:52:50 2009
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 * Description:	none
 * 
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_CLASS_STATIC_CONST_STRING_H
#define	_CLASS_STATIC_CONST_STRING_H

#include<string>
class A
{
public:
	A();
	int get();
private:
	static const std::string str;
	int a;
};


#endif //_CLASS_STATIC_CONST_STRING_H
