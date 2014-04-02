/*
 *--------------------------------------------------------------------------
 *   File Name:	class.static.size.cc
 * 
 * Description:	none
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 *     Version:	1.0
 * Create Date: Thu Aug 20 16:00:18 2009
 * Last Update: Thu Aug 20 16:00:18 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
class test
{
public:
	test();
	static int getcsi(){return csi;}
private:
	static int fun();
	int a;
	int p;
	static int b,c,d,e,f;
	const int fa,fb,fc;
	const static int csi  = 1234;
};
int test::f = 1;
int test::e = test::fun();
const int test::csi;
test::test()
:fa(1),fb(1),fc(1)
{
}
int test::fun(){return 1;}

int main()
{
	test t;
	std::cout<<sizeof(t)<<std::endl;
	std::cout<<t.getcsi()<<std::endl;
	return 0;
}
