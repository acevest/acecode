/*
 *--------------------------------------------------------------------------
 *   File Name:	fork.parent.child.share.variable.cc
 * 
 * Description:	测试子进程是否真的是拷贝了父进程的变量，父进程对改变量的
 * 		修改不会体现在子进程中。
 * 		预期结果:是
 * 		测试结果:是
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 *     Version:	1.0
 * Create Date: Thu Apr  9 10:39:48 2009
 * Last Update: Thu Apr  9 10:39:48 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
using namespace std;

int main()
{
	int shareVariable = 0x1234ABCD;
	pthread_t pid;

	pid = fork();

	if(pid == 0)
	{
		int i = 10;
		while(i--)
		{
			cout<<"Child\tpid:"<<getpid();
			printf("\tVariable: %x\n",shareVariable);
			sleep(1);
		}
		
	}
	else if(pid > 0)
	{
		int i = 10;
		while(i--)
		{
			cout<<"Parent\tpid:"<<getpid();
			printf("\tVariable: %x\n",shareVariable);
			shareVariable ++;
			sleep(1);
		}
	}
	else
	{
		cout<<"Failed to Create Child..."<<endl;
	}
	return 0;
}
