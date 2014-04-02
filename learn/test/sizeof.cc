/*
 *--------------------------------------------------------------------------
 *   File Name:	sizeof.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Sep  8 21:06:00 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<cstdio>
#include<iostream>
using namespace std;

#define	print(x) printf("sizeof("#x"):\t%d\n", sizeof(x));

int main()
{
	print(bool);
	print(char);
	print(short);
	print(int);
	print(long);
	print(float);
	print(double);
	print(long long);
	return 0;
}
