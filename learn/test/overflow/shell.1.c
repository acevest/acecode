/*
 *--------------------------------------------------------------------------
 *   File Name:	shell.1.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sun Oct 10 13:28:10 2010
 * 
 * Description:	本代码在2.6.21的内核下能运行，但在2.6.34下却不能
 * 		不知为何
 * 		>>主要是因为内核启用了页的NX位，通过向内核传递noexec=off来禁用，
 * 		>>则本全程可使用。
 * 
 *--------------------------------------------------------------------------
 */
#include<stdio.h>

int add(int x, int y){
	
	return x+y;
}

typedef int (* func)(int, int);
int main(){
	unsigned char buf[256];
	unsigned char *src = (unsigned char *)&add;
	unsigned char *dst = buf;
	func	pf = (func)buf;
	int	ret = 0;

	while(1){
		*dst = *src;
		printf("\\x%02x", *dst);
		if(*dst == 0xc3) break; /* ret */
		dst++;
		src++;
	}
	printf("\n");

	printf("%08x\n", buf);

	ret = (*pf)(0x111, 0x222);

	printf("result: %x\n", ret);

	return 0;
}
