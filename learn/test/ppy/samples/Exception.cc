/*
 *--------------------------------------------------------------------------
 *   File Name:	Exception.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 24 13:36:10 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <ppy.h>
using namespace std;
using namespace ppy;

const int size = 4096000;

class TestExpt {
public:
	void Function() {
		char *p;
		do
		{
#if 0
			p = new char [size];
#else
			p = (char *) malloc(size);
#endif
		}while(p != 0);

		PPY_GENERIC_EXCEPT(errno);
	}
};

int main() {

	try
	{
		TestExpt te;
		te.Function();
		
	}
	catch(const ppy::Exception& e)
	{
		cout<<e.getDetail()<<endl;
	}
	catch(const std::exception& e)
	{
		cout<<e.what()<<endl;
	}
	return 0;
}
