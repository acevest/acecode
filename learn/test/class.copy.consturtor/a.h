/*
 *--------------------------------------------------------------------------
 *   File Name:	a.h
 * 
 * Create Date: Fri Aug 21 21:37:31 2009
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

#ifndef	_A_H
#define	_A_H
#include<string>
using namespace std;
class A
{
public:
	A();
	A(const A& a);
	int geta(){return a;}
	string getb(){return b;}
	void seta(int x){a=x;}
	void setb(string x){b=x;}
private:
	int a;
	string b;
};


#endif //_A_H
