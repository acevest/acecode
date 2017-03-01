/*
 *--------------------------------------------------------------------------
 *   File Name:	htc.c
 * 
 * Description:	translate hex number into character
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 *     Version:	1.0
 * Create Date: Mon Dec 29 00:16:56 2008
 * Last Update: Mon Dec 29 00:16:56 2008
 * 
 *--------------------------------------------------------------------------
 */


#include<stdio.h>
int main()
{
	unsigned int ch;
	while(scanf("%x",&ch) != EOF)
		printf("%c",(unsigned char)ch);

	return 0;
}
