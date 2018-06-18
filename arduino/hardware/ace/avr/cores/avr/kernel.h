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

#define TASK_STACK_SIZE 64

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
void create_task(void (*handler)(), char *stack, uint8_t priority);
void task_switch(struct task *prev, struct task *next);
void task_delay(uint16_t ticks);
