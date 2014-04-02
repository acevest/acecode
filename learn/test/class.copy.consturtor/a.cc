/*
 *--------------------------------------------------------------------------
 *   File Name:	a.cc
 * 
 * Create Date: Fri Aug 21 21:38:32 2009
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
#include<a.h>

A::A():a(1234),b("AAAA"){}
A::A(const A& a)
{
	*this = a;
}
