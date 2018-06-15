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

void init() {
    sei();
    init_timer0();
}

int main()
{
    init();

    //uint8_t pin = 13;
    uint8_t bit = 1<<5; // pin 13是 B组的第5个
    volatile uint8_t *reg = ((volatile uint8_t *)((uint16_t)(&DDRB)));
    volatile uint8_t *out = ((volatile uint8_t *)((uint16_t)(&PORTB)));

    // set pin output
    uint8_t oldSREG = SREG;
    cli();
    *reg |= bit;
    SREG = oldSREG;

    const int d = 1000;
    int n = 0;

    while(1) {
        n++;

        oldSREG = SREG;
        cli();
                        /* HIGH */      /* LOW */
        n % 2 == 0 ? *out |= bit : *out &= ~bit;
        SREG = oldSREG;

        delay(d);
    }

    return 0;
}
