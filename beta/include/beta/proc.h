/*
 * ------------------------------------------------------------------------
 *   File Name: proc.h
 *      Author: Zhao Yanbai
 *              Sun Apr  1 16:50:00 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#ifndef  __H_PROC_H__
#define  __H_PROC_H__

#include<sys/system.h>

#define NR_PROC_START   128
#define NR_PROC_MM      128
#define NR_PROC_INIT    129
#define NR_PROCS        256

#define PROC_SIZE   0x2000

#ifndef __ASSEMBLY__
union proc {
    struct {

        stack_frame_t   regs;

        reg_t   cr3;

        reg_t   eip;
        
    };
    unsigned char _ [PROC_SIZE];
};

extern union proc proc[NR_PROCS];
extern union proc *current;
#endif

#endif /*__H_PROC_H__*/
