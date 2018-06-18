/*
 * ------------------------------------------------------------------------
 *   File Name: kernel.h
 *      Author: Zhao Yanbai
 *              2018-06-17 16:42:52 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once
#include <stdint.h>

#define MAX_TASK_CNT    8
#define TASK_STACK_SIZE 256

#if MAX_TASK_CNT > 32
#error "too much tasks"
#endif

enum task_state {
    TASK_STATE_EMPTY  = 0,
    TASK_STATE_READY  = 1,
    TASK_STATE_SLEEP  = 2,
};

struct task {
    uint8_t pid;
    enum task_state state;
    void (*handler)();
    uint8_t* stack;
    uint16_t delay_ticks;
};

void init_tasks();
void create_task(void (*handler)(), uint8_t *stack, uint8_t priority);
void task_switch(struct task *prev, struct task *next);
void task_delay(uint16_t ticks);
//void yield(void);

#define SAVE_CONTEXT  \
    __asm__ __volatile__( \
    "PUSH R31\n"    \
    "PUSH R30\n"    \
    "PUSH R29\n"    \
    "PUSH R28\n"    \
    "PUSH R27\n"    \
    "PUSH R26\n"    \
    "PUSH R25\n"    \
    "PUSH R24\n"    \
    "PUSH R23\n"    \
    "PUSH R22\n"    \
    "PUSH R21\n"    \
    "PUSH R20\n"    \
    "PUSH R19\n"    \
    "PUSH R18\n"    \
    "PUSH R17\n"    \
    "PUSH R16\n"    \
    "PUSH R15\n"    \
    "PUSH R14\n"    \
    "PUSH R13\n"    \
    "PUSH R12\n"    \
    "PUSH R11\n"    \
    "PUSH R10\n"    \
    "PUSH R09\n"    \
    "PUSH R08\n"    \
    "PUSH R07\n"    \
    "PUSH R06\n"    \
    "PUSH R05\n"    \
    "PUSH R04\n"    \
    "PUSH R03\n"    \
    "PUSH R02\n"    \
    "PUSH R01\n"    \
    "PUSH R00\n"    \
    "IN R00, __SREG__\n"    \
    "PUSH R00\n"    \
    );

#define RESTORE_CONTEXT    \
    __asm__ __volatile__(    \
    "POP R00\n"    \
    "OUT __SREG__, R00\n"    \
    "POP R00\n"    \
    "POP R01\n"    \
    "POP R02\n"    \
    "POP R03\n"    \
    "POP R04\n"    \
    "POP R05\n"    \
    "POP R06\n"    \
    "POP R07\n"    \
    "POP R08\n"    \
    "POP R09\n"    \
    "POP R10\n"    \
    "POP R11\n"    \
    "POP R12\n"    \
    "POP R13\n"    \
    "POP R14\n"    \
    "POP R15\n"    \
    "POP R16\n"    \
    "POP R17\n"    \
    "POP R18\n"    \
    "POP R19\n"    \
    "POP R20\n"    \
    "POP R21\n"    \
    "POP R22\n"    \
    "POP R23\n"    \
    "POP R24\n"    \
    "POP R25\n"    \
    "POP R26\n"    \
    "POP R27\n"    \
    "POP R28\n"    \
    "POP R29\n"    \
    "POP R30\n"    \
    "POP R31\n"    \
    );

