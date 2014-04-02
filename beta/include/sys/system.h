/*
 * ------------------------------------------------------------------------
 *   File Name: system.h
 *      Author: Zhao Yanbai
 *              Mon Apr  2 17:12:16 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#ifndef  __H_SYSTEM_H__
#define  __H_SYSTEM_H__

#include<sys/types.h>

#ifndef __ASSEMBLY__
typedef unsigned long reg_t;

typedef struct stack_frame
{
	reg_t	ebx;
	reg_t	edx;
	reg_t	ecx;
	reg_t	edi;
	reg_t	esi;
	reg_t	ebp;
	reg_t	eax;
	u16_t	ds, _ds;
	u16_t	es, _es;
	u16_t	fs, _fs;
	u16_t	gs, _gs;
	union
	{
		reg_t	sysc_nr;
		reg_t	irq;
		reg_t	errcode;
	};
	reg_t	eip;
	u16_t	cs, _cs;
	reg_t	eflags;
	reg_t	esp;
	u16_t	ss, _ss;
} stack_frame_t;
#endif

#endif /*__H_SYSTEM_H__*/
