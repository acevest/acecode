/*
 * ------------------------------------------------------------------------
 *   File Name: main.cpp
 *      Author: Zhao Yanbai
 *              2018-06-14 20:21:33 Thursday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
#include <Arduino.h>

void init_timer0();
void init_timer1();
void init_tasks();

#if 1
void init() {
    cli();
    init_timer0();
    //init_timer1();
    //init_tasks();
    sei();
}

int main()
{
    init();

    uint8_t pin = 13;
    set_digital_pin_mode(pin, OUTPUT);
    digital_write(pin, LOW);

    uint8_t state = LOW;
    while(1) {
        state = state == LOW ? HIGH : LOW;
        digital_write(pin, state);
        delay(1000);
    }


    return 0;
}
#else

uint8_t stack[128];

void handler() {
    uint8_t pin = 12;
    set_digital_pin_mode(pin, OUTPUT);
    digital_write(pin, LOW);


    uint8_t state = LOW;
    while(1) {
        state = state == LOW ? HIGH : LOW;
        digital_write(pin, state);
        delay(1000);
    }
}


uint8_t * volatile p = 0;
int main()
{
    sei();
    init_timer0();

    p = stack+64;

    *(p+0) = 0;
    *(p+1) = 0; //(((uint16_t)handler) >> 8);
    *(p+2) = (((uint16_t)handler) >> 0);
    *(p+3) = (((uint16_t)handler) >> 8);


    asm("nop");
    asm("nop");
    #if 1
    SP = (uint16_t) p;
    #else
    asm volatile (
        "lds r26, p\n"
        "lds r27, p+1\n"
        "out __SP_L__, r26\n"
        "out __SP_H__, r27\n"
        );
    #endif
    asm("nop");
    asm("nop");

    asm("ret");

    return 0;
}

#endif
