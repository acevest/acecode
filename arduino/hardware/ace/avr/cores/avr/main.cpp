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

void init() {
    cli();
    init_timer0();
    init_timer1();
    init_tasks();
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
