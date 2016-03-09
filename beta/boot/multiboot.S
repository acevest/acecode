/*
 *--------------------------------------------------------------------------
 *   File Name:	multiboot.S
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Oct  1 23:33:02 2010
 * 
 * Description:	
 *              Disable Paging [Sun Apr  1 23:43:27 2012]
 * 
 *--------------------------------------------------------------------------
 */
#include<beta/const.h>
#define	ASM
#include<multiboot.h>

.global BETA_ENTRY

.extern	kernel_end
.extern	kernel_entry
.extern	multi_boot

.text
.code32
.align 8
BETA_ENTRY:
	/* Reset eflags */
	pushl $0
	popf

	lgdt	gdtr

	movw	$0x10, %dx
	movw	%dx, %ds
	movw	%dx, %es
	movw	%dx, %ss
	movw	%dx, %fs
	movw	%dx, %gs



	movl	$(stack + MULTIBOOT_STACK_SIZE), %esp
	/* Save the pointer to the Multiboot information structure. */
	pushl	%ebx

	/* Save the magic value. */
	pushl	%eax

	jmp	1f
1:

	ljmp	$0x08, $_kernel

_kernel:
	call	multi_boot
	addl	$8, %esp
	call	kernel_entry

_loop:
	hlt
	jmp	_loop

.align 8
/* Multiboot header. */
multiboot_header:
magic:	.long	MULTIBOOT_HEADER_MAGIC
flags:	.long	MULTIBOOT_HEADER_FLAGS
chksum:	.long	-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

/* Global Descriptor Table */
boot_gdt:
empty:	.long	0x00000000, 0x00000000
code:	.long	0x0000FFFF, 0x00CF9B00
data:	.long	0x0000FFFF, 0x00CF9300
boot_gdt_end:
gdtr:
	gdtr_limit:	.word	boot_gdt_end - boot_gdt
	gdtr_base:	.long	boot_gdt

/* Stack */
.comm	stack, MULTIBOOT_STACK_SIZE
