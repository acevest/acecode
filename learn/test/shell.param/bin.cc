/*
 *--------------------------------------------------------------------------
 *   File Name:	bin.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Sep 21 23:27:50 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{

	for(int i=0; i<argc; i++)
		cout<<i<<"\t: "<<argv[i]<<endl;

	return 0;
}
