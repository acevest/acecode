/*
 *--------------------------------------------------------------------------
 *   File Name:	syscall.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct 16 15:42:46 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<asm/ptrace.h>
#include<errno.h>
#include<beta/sysc.h>


void init_sysenter();
int sysc_none();

typedef int (*sysc_func_t)();
sysc_func_t sysc_handler_tbl[NR_SYSC];

void setup_syscall() {
    int i;

	init_sysenter();

    for(i=0; i<NR_SYSC; i++) {
        sysc_handler_tbl[i] = sysc_none;
    }

    sysc_handler_tbl[SYSC_IPC] = sysc_ipc;
}

int sysc_none() {
	unsigned char *p = (unsigned char *)0xB8002;
	*p = *p == ' ' ? 'S' : ' ';
	return 0xAABB;
}

int syscall(int syscvec) {
    if(syscvec < 0 || syscvec >= NR_SYSC)
        return -EBADRQC;
    sysc_func_t p = (sysc_func_t)sysc_handler_tbl[syscvec];
    p();   
}
