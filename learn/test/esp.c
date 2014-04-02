/*
 * ------------------------------------------------------------------------
 *   File Name: esp.c
 *      Author: Zhao Yanbai
 *              Tue Mar 27 18:46:53 2012
 * Description: 测试在pushl时到底是先esp = esp - 4 再 填数据还是
 *              先填数据再esp = esp - 4
 * ------------------------------------------------------------------------
 */
#include <stdio.h>
int main() {
    int i;
    int esp;
    asm("movl %%esp, %%eax":"=a"(esp));
    unsigned long *p = (unsigned long *) esp;
    for(i=0; i<100; i++) {
        *p = 0xFFFFFFFF;
        p--;
    }

    asm("pushl $0xAABBCCDD");
    asm("movl %%esp, %%eax":"=a"(esp));

    p = (unsigned long *) esp;

    if(*p == 0xAABBCCDD) {
        printf("esp = esp - 4 before pushl\n");
    } else {
        printf("esp = esp - 4 after pushl\n");
    }
    return 0;
}
