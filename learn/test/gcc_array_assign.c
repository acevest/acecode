/*
 *--------------------------------------------------------------------------
 *   File Name:	gcc_array_assign.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Aug  9 19:20:11 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<stdio.h>

int main()
{

	static int a[100];

	a[0] = { [0 ... 20] = 3};

	return 0;
}
