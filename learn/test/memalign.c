/*
 *--------------------------------------------------------------------------
 *   File Name:	memalign.c
 * 
 * Description:	测试按指定边界对齐分配内存
 * 		主要想用来按页对齐分配内存
 * 		测试结果：如果不按页分配内存则所分配的内存间隔也是以
 * 		页为单位
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Fri May 29 20:37:48 2009
 * Last Update: Fri May 29 20:37:48 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<stdlib.h>
#include<stdio.h>
int main()
{
	void *p;
	int i;
	for(i=0; i<100; i++)
	{
		p = (void *)memalign(4096, 4096);
		printf("***** %x *****\n", p);
	}
	for(i=0; i<100; i++)
	{
		p = (void *)memalign(2048, 1024);
		printf("===== %x =====\n", p);
	}

	return 0;
}
