/*
 * ------------------------------------------------------------------------
 *   File Name: kernel.cpp
 *      Author: Zhao Yanbai
 *              2018-06-17 16:42:56 Sunday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
#include <AceAvr.h>
#include <kernel.h>

void delay(unsigned long ms);

const uint8_t task_cnt = MAX_TASK_CNT + 1;
const uint8_t idle_task_priority = task_cnt - 1;
struct task *current_task = 0;
struct task tasks[task_cnt];
uint32_t ticks = 0;
int8_t kernel_initialized = 0;

#define IDLE_TASK (tasks+task_cnt-1)
#define LED_TASK (tasks+0);
#define DEBUG_TASK (tasks+1);

void task_scheduler();

// idle_task 在没有进程READY的情况下都会调度运行
// 所以task_delay不能在此进程生效
uint8_t idle_task_stack[TASK_STACK_SIZE];
uint32_t idle_cnt = 0;
void app_main();
void idle_task() {
    sei();
    kernel_initialized = 1;
    app_main();
    uint8_t pin = 12;
    set_digital_pin_mode(pin, OUTPUT);
    uint8_t state = LOW;
    while(1) {
        idle_cnt++;
        state = state == LOW ? HIGH : LOW;
        digital_write(pin, state);
        delay(1000);
    }
}


void task_delay(uint16_t ticks)
{
    cli();
    current_task->state = TASK_STATE_SLEEP;
    current_task->delay_ticks = ticks;
    sei();
    task_scheduler();
}

void create_task(void (*handler)(), uint8_t *stack, uint8_t priority)
{
    if(priority == idle_task_priority && handler != idle_task) {
        return;
    }

    if(priority > task_cnt) {
        return;
    }

    struct task *t = tasks + priority;
    t->handler = handler;
    t->state = TASK_STATE_READY;

    t->stack = stack + TASK_STACK_SIZE - 3;
    uint8_t *p = t->stack;
    *(p+0) = (((uint32_t)handler) >> 16);
    *(p+1) = (((uint32_t)handler) >> 8);
    *(p+2) = (((uint32_t)handler) >> 0);
    *(--(t->stack)) = 0x00;   // SREG
    *(--(t->stack)) = 0x00;   // R0
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;   // R10
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;   // 20
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;
    *(--(t->stack)) = 0x00;   // 30
    *(--(t->stack)) = 0x00;
}

void task_switch(struct task *prev, struct task *next) {
    if(prev == next) {
        return;
    }

    __asm__ __volatile__(
    "PUSH R31\n"
    "PUSH R30\n"
    "PUSH R29\n"
    "PUSH R28\n"
    "PUSH R27\n"
    "PUSH R26\n"
    "PUSH R25\n"
    "PUSH R24\n"
    "PUSH R23\n"
    "PUSH R22\n"
    "PUSH R21\n"
    "PUSH R20\n"
    "PUSH R19\n"
    "PUSH R18\n"
    "PUSH R17\n"
    "PUSH R16\n"
    "PUSH R15\n"
    "PUSH R14\n"
    "PUSH R13\n"
    "PUSH R12\n"
    "PUSH R11\n"
    "PUSH R10\n"
    "PUSH R09\n"
    "PUSH R08\n"
    "PUSH R07\n"
    "PUSH R06\n"
    "PUSH R05\n"
    "PUSH R04\n"
    "PUSH R03\n"
    "PUSH R02\n"
    "PUSH R01\n"
    "PUSH R00\n"
    "IN R00, __SREG__\n"
    "PUSH R00\n"
    );

    prev->stack = (uint8_t *) SP;
    SP = ((uint16_t)next->stack);
    current_task = next;

    __asm__ __volatile__(
    "POP R00\n"
    "OUT __SREG__, R00\n"
    "POP R00\n"
    "POP R01\n"
    "POP R02\n"
    "POP R03\n"
    "POP R04\n"
    "POP R05\n"
    "POP R06\n"
    "POP R07\n"
    "POP R08\n"
    "POP R09\n"
    "POP R10\n"
    "POP R11\n"
    "POP R12\n"
    "POP R13\n"
    "POP R14\n"
    "POP R15\n"
    "POP R16\n"
    "POP R17\n"
    "POP R18\n"
    "POP R19\n"
    "POP R20\n"
    "POP R21\n"
    "POP R22\n"
    "POP R23\n"
    "POP R24\n"
    "POP R25\n"
    "POP R26\n"
    "POP R27\n"
    "POP R28\n"
    "POP R29\n"
    "POP R30\n"
    "POP R31\n"
    "ret\n"
    );
}

void task_scheduler() {
    struct task *next = IDLE_TASK;
    for(uint8_t i=0; i<task_cnt; i++) {
        struct task *t = tasks+i;
        if(TASK_STATE_READY == t->state) {
            next = t;
            break;
        }
    }

    task_switch(current_task, next);
}

void yield(void)
{
    if(kernel_initialized == 0) {
        return ;
    }

    task_scheduler();
}

extern "C" void TIMER1_COMPA_vect() __attribute__ ((signal,used, externally_visible));
void TIMER1_COMPA_vect()
{
    ticks++;

    for(uint8_t i=0; i<task_cnt; i++) {
        struct task *t = tasks+i;
        if(TASK_STATE_SLEEP != t->state) {
            continue;
        }

        if(t->delay_ticks > 0) {
            t->delay_ticks--;
        }

        if(t->delay_ticks == 0) {
            t->state =  TASK_STATE_READY;
        }
    }

    task_scheduler();
}

void init_timer1() {
    //set timer1 interrupt at 100Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 100Hz increments
    OCR1A = 155; // = (16*10^6) / (1024*100Hz) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

void init_tasks() {
    cli();
    for(uint8_t i=0; i<task_cnt; i++) {
        struct task *t = tasks+i;
        t->pid          = i;
        t->handler      = 0;
        t->stack        = 0;
        t->state        = TASK_STATE_EMPTY;
        t->delay_ticks  = 0;
    }

    create_task(idle_task, idle_task_stack, idle_task_priority);
    current_task = IDLE_TASK;
    IDLE_TASK->stack = idle_task_stack+TASK_STACK_SIZE - 3;

    SP = (uint16_t)(IDLE_TASK->stack);
    asm("ret;");
}


