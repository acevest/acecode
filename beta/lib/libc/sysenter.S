/*
 *--------------------------------------------------------------------------
 *   File Name:	sysenter.S
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct 16 15:03:07 2010
 * 
 * Description:	系统调用进入内核的入口.
 *		可利用的寄存器包括 eax, ebx, ecx, edx, edi 共5个.
 *		eax 用来做调用号.
 * 
 *--------------------------------------------------------------------------
 */
.text
.code32
.global	beta_sysenter

beta_sysenter:
	pushl	%ecx
	pushl	%edx
	pushl	%ebp
	pushl	%esi
	movl	$1f, %esi
	movl	%esp,%ebp
	sysenter
1:
	popl	%esi
	popl	%ebp
	popl	%edx
	popl	%ecx

	ret
	
