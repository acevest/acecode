/*
 *--------------------------------------------------------------------------
 *   File Name:	clock.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 21:09:12 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */


#include<asm/ptrace.h>

unsigned long ticks = 0;

int clock_handler(unsigned int irq, pt_regs *r, void *dev_id){

	ticks++;
	unsigned char *p = (unsigned char *)0xB8000;

	*p = *p == ' ' ? '*' : ' ';

	return 0;
}
