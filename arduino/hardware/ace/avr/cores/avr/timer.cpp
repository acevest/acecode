/*
 * ------------------------------------------------------------------------
 *   File Name: timer.cpp
 *      Author: Zhao Yanbai
 *              2018-06-15 18:31:24 Friday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#include<Arduino.h>


volatile unsigned long timer0_overflow_count = 0;
#if 0
static void __empty() {
    // Empty
}

void yield(void) __attribute__ ((weak, alias("__empty")));
#else
void yield(void) { }
#endif

unsigned long micros() {
    unsigned long m;
    uint8_t oldSREG = SREG, t;

    cli();
    m = timer0_overflow_count;

    t = TCNT0;
    if ((TIFR0 & _BV(TOV0)) && (t < 255)) {
        m++;
    }
    SREG = oldSREG;

    return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}

void delay(unsigned long ms)
{
    uint32_t start = micros();
    while (ms > 0) {
        yield();
        while ( ms > 0 && (micros() - start) >= 1000) {
            ms--;
            start += 1000;
        }
    }
}


void init_timer0() {
    // on the ATmega168, timer 0 is also used for fast hardware pwm
    // (using phase-correct PWM would mean that timer 0 overflowed half as often
    // resulting in different millis() behavior on the ATmega8 and ATmega168)
    sbi(TCCR0A, WGM01);
    sbi(TCCR0A, WGM00);

    // set timer 0 prescale factor to 64
    sbi(TCCR0B, CS01);
    sbi(TCCR0B, CS00);

    // enable timer 0 overflow interrupt
    sbi(TIMSK0, TOIE0);
}

void init_timer1() {
    //set timer1 interrupt at 100Hz
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    // set compare match register for 100Hz increments
    //OCR1A = 155; // = (16*10^6) / (1024*100Hz) - 1 (must be <65536)
    OCR1A = 15500; // = (16*10^6) / (1024*100Hz) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

extern "C" void TIMER0_OVF_vect() __attribute__ ((signal,used, externally_visible));
void TIMER0_OVF_vect()
{
    timer0_overflow_count++;
}
