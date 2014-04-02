/*
 * ------------------------------------------------------------------------
 *   File Name: proc.c
 *      Author: Zhao Yanbai
 *              Sun Apr  1 19:56:12 2012
 * Description: none
 * ------------------------------------------------------------------------
 */

#include<beta/proc.h>

union proc proc[NR_PROCS];
union proc *current;

void setup_proc() {
    current = proc + NR_PROC_INIT;
}
