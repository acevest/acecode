/*
 * ------------------------------------------------------------------------
 *   File Name: sysc.h
 *      Author: Zhao Yanbai
 *              Sun Apr  1 17:09:44 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#ifndef  __H_SYSC_H__
#define  __H_SYSC_H__


#define SYSC_IPC    4
#define NR_SYSC 100


#ifndef __ASSEMBLY__
#include <errno.h>
int sysc_ipc();

int beta_sysenter();

#define	sysenter(vect)({ 	\
	asm(""::"a"(vect));	\
    beta_sysenter();        \
})

#define	_syscall0(vect)({	\
	sysenter(vect);		\
})

#define	_syscall1(vect, a)({	\
	asm(""::"b"(a));	\
	sysenter(vect);		\
})

#define	_syscall2(vect, a, b)({	\
	asm(""::"b"(a), "d"(b));\
	sysenter(vect);		\
})

#define	_syscall3(vect, a, b, c)({	\
	asm(""::"b"(a), "d"(b), "c"(c));\
	sysenter(vect);			\
})

#define	_syscall_ret()({	\
	int ret;		\
	asm("":"=a"(ret));	\
	if(ret < 0)		\
	{			\
		errno = -ret;	\
		ret = -1;	\
	}			\
	ret;})

#define	syscall0(vect)		\
	(({_syscall0(vect);}),		({_syscall_ret();}))
#define	syscall1(vect, a)	\
	(({_syscall1(vect, a);}),	({_syscall_ret();}))
#define	syscall2(vect, a, b)	\
	(({_syscall2(vect, a, b);}),	({_syscall_ret();}))
#define	syscall3(vect, a, b, c)	\
	(({_syscall3(vect, a, b, c);}),	({_syscall_ret();}))

#endif

#endif /*__H_SYSC_H__*/
