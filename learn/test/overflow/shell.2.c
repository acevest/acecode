/*
 *--------------------------------------------------------------------------
 *   File Name:	shell.2.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sun Oct 10 14:10:31 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<stdio.h>
typedef int (*func)(int, int);
int main(){
	unsigned char *buf="\x55\x89\xe5\x8b\x45\x0c\x03\x45\x08\x5d\xc3";
	func pf = (func) buf;
	int ret = 0;
	//asm("pushl $0xaaa;pushl $0xbbb;");
	//asm("call buf");
	//while(1);
	ret = pf(0xAAA, 0xBBB);
	printf("result = %x\n", ret);
	return 0;
}
