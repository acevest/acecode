/*
 *--------------------------------------------------------------------------
 *   File Name:	gethostbyname.cc
 * 
 * Description:	none
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 *     Version:	1.0
 * Create Date: Thu Aug 20 16:56:03 2009
 * Last Update: Thu Aug 20 16:56:03 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<netdb.h>
#include<iostream>

int main()
{
	struct hostent *ph;
	ph = gethostbyname("127.0.0.1");
	std::cout<<ph->h_name<<std::endl;

	return 0;
}
