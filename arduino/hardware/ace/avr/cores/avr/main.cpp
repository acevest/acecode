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

void init() {
    sei();
    init_timer0();
    init_timer1();
}

extern uint8_t tick;
int main()
{
    init();

    uint8_t pin = 12;
    set_digital_pin_mode(pin, OUTPUT);

    int n = 0;
    uint8_t state = LOW;
    while(1) {
        n++;

        if(tick > 100) {
            state = state == LOW ? HIGH : LOW;
            tick = 0;
        }

        digital_write(pin, state);
        delay(10);
    }

    return 0;
}
