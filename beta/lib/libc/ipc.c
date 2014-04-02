/*
 * ------------------------------------------------------------------------
 *   File Name: ipc.c
 *      Author: Zhao Yanbai
 *              Sun Apr  1 17:14:26 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

#include <beta/sysc.h>
#include <beta/ipc.h>
int beta_notify() {


    syscall1(SYSC_IPC, NOTIFY);


}
