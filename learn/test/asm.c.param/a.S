#include<a.h>
.text
.code32
.align 32
.global	asm_fun
#if PTR1
asm_fun:
	pushl	$0x1
	pushl	$0x2
	call	c_fun
	addl	$8,%esp
	ret
#endif
#if PTR2
asm_fun:
	pushl	$0x1
	pushl	$0x2
	pushl	%esp
	call	c_fun
	addl	$12,%esp
	ret
#endif

#if PTR3
asm_fun:
	pushl	$0x1
	pushl	$0x2
	movl	%esp,%eax
	call	c_fun
	addl	$8,%esp
	ret
#endif

#if PTR4
asm_fun:
	movl	$0x1111, %eax
	movl	$0x2222, %ebx
	movl	$0x3333, %ecx
	movl	$0x4444, %edx
	movl	$0x5555, %esi
	movl	$0x6666, %edi
	call	c_fun
	ret
#endif
