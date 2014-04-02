/*
 *--------------------------------------------------------------------------
 *   File Name:	Singleton.cc
 * 
 * Create Date: Thu Oct 15 13:57:50 2009
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 * Description:	
 * 	编译
 * 	g++ Singleton.cc -o Singleton -lisrc
 * 
 * 
 *--------------------------------------------------------------------------
 */

#include <iostream>
#include <ppy.h>
using namespace std;

class CSingleA : public ppy::Singleton<CSingleA>
{
public:
	CSingleA(){}
	~CSingleA(){}
	void	Display()
	{
		cout<<"CSingleA"<<endl;
	}
};

class CSingleB : public ppy::Singleton<CSingleB>
{
public:
	void	Display()
	{
		cout<<"CSingleB"<<endl;
	}
};


int main()
{
	cout<<CSingleA::getSingletonPtr()<<endl;
	CSingleA a;
	cout<<a.getSingletonPtr()<<endl;
	a.Display();
	a.getSingletonPtr()->Display();
	a.getSingleton().Display();

	CSingleB b;
	//CSingleB c;	// 注释掉会引起运行时的assert
	b.getSingletonPtr()->Display();

	return 0;
}
