/*
 *--------------------------------------------------------------------------
 *   File Name:	overflow.1.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct  7 11:20:57 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<stdio.h>
#include<stdlib.h>
void func(){
	printf("Hello World\n");
	exit(0);
}

int main(int argc, char *argv[]){
#if 1
	int a;
	unsigned long p[1];
	int c;

	a = 0xAABB;
	c = 0xCCDD;
	p[0] = 0;
	p[1] = 1;	/* 覆盖a */
	p[2] = 2;	/* 覆盖c */
	p[3] = 2;	/* 覆盖ebp */
	p[4] = (unsigned long)func; /* 覆盖返回地址 */

	/* 通过反汇编分析，p[0]地址最低，其次是a, 其次是c
	   这就证明声明顺序与实际顺序无关*/
	/* 但是要调用下面的printf的话，则有关,c 的地址最小 */
#if 0
	printf("%08x %08x %08x\n", &a, p, &c);
#endif
#else
	unsigned long *p;
	asm("movl %%ebp, %%eax;":"=a"(p));
	p[1] = (unsigned long)func;
#endif
	return 0;
}
