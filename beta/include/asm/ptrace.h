/*
 *--------------------------------------------------------------------------
 *   File Name:	ptrace.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 16:15:52 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PTRACE_H
#define	_PTRACE_H

#ifndef	__ASSEMBLY__

typedef struct {
	unsigned long	ebx;
	unsigned long	edx;
	unsigned long	ecx;
	unsigned long	edi;

	unsigned long	esi;
	unsigned long	ebp;
	unsigned long	eax;

	unsigned short	ds, _ds;
	unsigned short	es, _es;
	unsigned short	fs, _fs;
	unsigned short	gs, _gs;

	union {
		unsigned long	sys;	/* syscall vector	*/
		unsigned long	irq;	/* irq vector		*/
		unsigned long	err;	/* error code		*/
	};

	unsigned long	eip;
	unsigned short	cs, _cs;
	unsigned long	eflags;
	unsigned long	esp;
	unsigned short	ss, _ss;
} pt_regs;

#endif	/* __ASSEMBLY__ */

#define	PT_EBX		0x00
#define	PT_EDX		0x04
#define	PT_ECX		0x08
#define	PT_EDI		0x0C
#define	PT_ESI		0x10
#define	PT_EBP		0x14
#define	PT_EAX		0x18
#define	PT_DS		0x1C
#define	PT_ES		0x20
#define	PT_FS		0x24
#define	PT_GS		0x28
#define	PT_SYS		0x2C
#define	PT_IRQ		0x2C
#define	PT_ERR		0x2C
#define	PT_EIP		0x30
#define	PT_CS		0x34
#define	PT_EFLAGS	0x38
#define	PT_ESP		0x3C
#define	PT_SS		0x40


#define	SAVE_REGS	\
	cld;		\
	pushl	%gs;	\
	pushl	%fs;	\
	pushl	%es;	\
	pushl	%ds;	\
	pushl	%eax;	\
	pushl	%ebp;	\
	pushl	%esi;	\
	pushl	%edi;	\
	pushl	%ecx;	\
	pushl	%edx;	\
	pushl	%ebx;

#define	RESTORE_REGS	\
	popl	%ebx;	\
	popl	%edx;	\
	popl	%ecx;	\
	popl	%edi;	\
	popl	%esi;	\
	popl	%ebp;	\
	popl	%eax;	\
	popl	%ds;	\
	popl	%es;	\
	popl	%fs;	\
	popl	%gs;

#endif //_PTRACE_H
