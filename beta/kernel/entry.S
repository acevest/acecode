/*
 *--------------------------------------------------------------------------
 *   File Name:	entry.S
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Oct  6 20:28:36 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#define	__ASSEMBLY__
#include<asm/ptrace.h>
#include<beta/const.h>
#include<beta/system.h>
#include<beta/proc.h>

/*
 *-------------------------------------------------------------------------
 *			INTERRUPT ENTRY
 *-------------------------------------------------------------------------
 */
.extern irq_handler
.extern	schedule
_irq_handler:
    
	SAVE_REGS

	movw	%ss,%dx
	movw	%dx, %ds
	movw	%dx, %es
	movw	$(USER_DS), %dx
	movw	%dx, %fs
	movw	%dx, %gs

	call	irq_handler
		
	RESTORE_REGS

	addl	$4,%esp		/* 跳过(中断号 or ErrorCode) */

	iret


/*
 *-------------------------------------------------------------------------
 *			SYSENTER ENTRY
 *-------------------------------------------------------------------------
 */
.global sysenter_entry
.extern	syscall
sysenter_entry:
	/*
	 * 这个时候不用担心会被中断.而用tss结构体作为中断栈.
	 * 因为执行sysenter后，IF=0
	 */
	movl	(%esp), %esp	/* 切换到进程的内核栈 */
    addl    $PROC_SIZE, %esp

	/* 构造栈中没有stack_frame的部分 */
	pushl	$(USER_DS)
	pushl	%ebp
	pushfl
	pushl	$(USER_CS)
	pushl	%esi		/* sysenter return address */

	pushl	%eax		/* syscall vector */
	
	SAVE_REGS

	sti
	movw	%ss, %dx
	movw	%dx, %ds
	movw	%dx, %es
	movw	$(USER_DS), %dx
	movw	%dx, %fs
	movw	%dx, %gs

	call	*sysc_handler_tbl(,%eax,4)

	/* 存入返回值 */
	movl	%eax, PT_EAX(%esp)

	/* 存入sysexit返回所需要的参数 */
	movl	PT_ESP(%esp), %ecx
	movl	PT_EIP(%esp), %edx
	movl	%ecx, PT_ECX(%esp)
	movl	%edx, PT_EDX(%esp)

	RESTORE_REGS

	sysexit	


/*
 *-------------------------------------------------------------------------
 *			INTERRUPT ENTRY	TABLE LIST
 *-------------------------------------------------------------------------
 */
#define	IRQ_SYMBL(a,b)	irq_0x##a##b_handler
#define	IRQ_LIST(x)	\
IRQ_SYMBL(x,0),		\
IRQ_SYMBL(x,1),		\
IRQ_SYMBL(x,2),		\
IRQ_SYMBL(x,3),		\
IRQ_SYMBL(x,4),		\
IRQ_SYMBL(x,5),		\
IRQ_SYMBL(x,6),		\
IRQ_SYMBL(x,7),		\
IRQ_SYMBL(x,8),		\
IRQ_SYMBL(x,9),		\
IRQ_SYMBL(x,A),		\
IRQ_SYMBL(x,B),		\
IRQ_SYMBL(x,C),		\
IRQ_SYMBL(x,D),		\
IRQ_SYMBL(x,E),		\
IRQ_SYMBL(x,F)

#define	DEF_IRQ(a,b)		\
.align	0x04,0x90;		\
.global	irq_0x##a##b##_handler;	\
irq_0x##a##b##_handler:		\
pushl	$0x##a##b;		\
jmp	_irq_handler;


DEF_IRQ(0,0)
DEF_IRQ(0,1)
DEF_IRQ(0,2)
DEF_IRQ(0,3)
DEF_IRQ(0,4)
DEF_IRQ(0,5)
DEF_IRQ(0,6)
DEF_IRQ(0,7)
DEF_IRQ(0,8)
DEF_IRQ(0,9)
DEF_IRQ(0,A)
DEF_IRQ(0,B)
DEF_IRQ(0,C)
DEF_IRQ(0,D)
DEF_IRQ(0,E)
DEF_IRQ(0,F)




/*
 *-------------------------------------------------------------------------
 *			EXCEPTION ENTRY TABLE LIST
 *-------------------------------------------------------------------------
 */
#define	_ENTRY_(name)			\
	.extern	do_##name;		\
	.global name;			\
	.align	0x04,0x90;		\
	name:				\
	cli;

#define	_CALLDO_(name)			\
	SAVE_REGS;			\
	call	do_##name;		\
	RESTORE_REGS;			\
	iret;


#define	NOERRCODE(name)			\
	_ENTRY_(name)			\
	pushl	$0;			\
	_CALLDO_(name)

#define	ERRORCODE(name)			\
	_ENTRY_(name)			\
	_CALLDO_(name)


NOERRCODE	(divide_error)
NOERRCODE	(debug)
NOERRCODE	(nmi)
NOERRCODE	(break_point)
NOERRCODE	(over_flow)
NOERRCODE	(bounds_check)
NOERRCODE	(invalid_opcode)
NOERRCODE	(device_not_available)
NOERRCODE	(double_fault)
NOERRCODE	(coproc_seg_over_run)
ERRORCODE	(invalid_tss)
ERRORCODE	(seg_not_present)
ERRORCODE	(stack_fault)
ERRORCODE	(general_protection)
ERRORCODE	(page_fault)
NOERRCODE	(coproc_error)

