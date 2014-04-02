/*
 *--------------------------------------------------------------------------
 *   File Name:	msr.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:58:07 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_MSR_H
#define	_MSR_H

#define	MSR_SYSENTER_CS		0x174
#define	MSR_SYSENTER_ESP	0x175
#define	MSR_SYSENTER_EIP	0x176

#define	wrmsr(msr, lowval, highval) do{\
	asm("wrmsr;"::"c"(msr),"a"(lowval),"d"(highval));\
}while(0);

#endif //_MSR_H
