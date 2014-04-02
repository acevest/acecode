/*
 *--------------------------------------------------------------------------
 *   File Name:	virtual.destructor.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Aug 27 14:17:13 2011
 * 
 * Description:	说明在基类中析构函数定义加上virtual关键字的原因。
 * 
 *--------------------------------------------------------------------------
 */

#include <iostream>
using namespace std;

class Base {
public:
	Base() {cout<<"Base Constructor"<<endl;}
	~Base() {cout<<"Base Deconstructor"<<endl;}
};

class Derived : public Base {
public:
	Derived() {cout<<"Derived Constructor"<<endl;}
	~Derived() {cout<<"Derived Deconstructor"<<endl;}
};

class VBase {
public:
	VBase() {cout<<"VBase Constructor"<<endl;}
	virtual ~VBase() {cout<<"VBase Deconstructor"<<endl;}
};

class VDerived : public VBase {
public:
	VDerived() {cout<<"VDerived Constructor"<<endl;}
	~VDerived() {cout<<"VDerived Deconstructor"<<endl;}
};

int main() {
	// 因为基类的析构函数不是虚拟的，且用的是基类指针
	// 所以无法调用到子类的析构函数
	cout<<"======================================="<<endl;
	Base *a = new Derived;
	delete a;

	// 因为用的是子类的指针，所以能调用到子类的析构函数
	cout<<"======================================="<<endl;
	Derived *b = new Derived;
	delete b;

	// 因为基类的析构函数是虚拟的，所以能调用到子类的
	// 析构函数,并且之后自动调用基类的析构函数
	cout<<"======================================="<<endl;
	VDerived *c = new VDerived;
	delete c;


	return 0;
}

