/*
 * ------------------------------------------------------------------------
 *   File Name: sysc_ipc.c
 *      Author: Zhao Yanbai
 *              Sun Apr  1 17:16:19 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

#include<beta/ipc.h>
int kprintf(const char *fmt, ...);
int do_ipc_notify() {
	unsigned char *p = (unsigned char *)0xB8006;
	*p = *p == ' ' ? 'N' : ' ';
    //*(p+1) = ++*(p+1);
}
int sysc_ipc(int ipcvec) {
    //    do_ipc_notify();
    switch(ipcvec) {
    case SEND:
        break;
    case RECV:
        break;
    case NOTIFY:
        do_ipc_notify();
        break;
    case SNDRCV:
        break;
    default:
        break;
    };
}
