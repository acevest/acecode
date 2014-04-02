/*
 * ------------------------------------------------------------------------
 *   File Name: ipc.S
 *      Author: Zhao Yanbai
 *              Sun Apr  1 17:31:43 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

#define __ASSEMBLY__
#include<beta/ipc.h>
#include<beta/sysc.h>

.extern beta_sysenter
.global ___beta_notify
___beta_notify:
    movl    $SYSC_IPC,    %eax
    call    beta_sysenter
