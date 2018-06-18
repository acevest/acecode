/*
 * ------------------------------------------------------------------------
 *   File Name: timer.cpp
 *      Author: Zhao Yanbai
 *              2018-06-15 18:31:24 Friday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#include<AceAvr.h>


volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

unsigned long millis()
{
    unsigned long m;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    cli();
    m = timer0_millis;
    SREG = oldSREG;

    return m;
}

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

extern "C" void TIMER0_OVF_vect() __attribute__ ((signal,used, externally_visible));
void TIMER0_OVF_vect()
{
    unsigned long m = timer0_millis;
    unsigned char f = timer0_fract;

    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX) {
        f -= FRACT_MAX;
        m += 1;
    }

    timer0_fract = f;
    timer0_millis = m;

    timer0_overflow_count++;
}


#if 0
extern "C" void TIMER1_COMPA_vect() __attribute__ ((signal,used, externally_visible));
void TIMER1_COMPA_vect() { }
#endif
