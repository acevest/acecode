/*
 *--------------------------------------------------------------------------
 *   File Name:	fork.parent.child.free.cc
 * 
 * Description:	在父进程中申请一个空间
 * 		在父进程和子进程都释放，不知会不会doublefree.
 * 		预期结果:不会
 * 		测试结果:不会
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Thu May 14 15:45:06 2009
 * Last Update: Thu May 14 15:45:06 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int main()
{

	pid_t pid;
	char *p;

	p = (char *)malloc(1024);

	pid =  fork();

	if(pid<0)
	{
		cout<<"failed"<<endl;
		return 0;
	}
	else if(pid == 0)
	{
		free(p);
	}
	else
	{
		free(p);
	}
	return 0;
}
