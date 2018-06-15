/*
 * ------------------------------------------------------------------------
 *   File Name: main.cpp
 *      Author: Zhao Yanbai
 *              2018-06-14 20:21:33 Thursday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
#include <Arduino.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define __SFR_OFFSET 0x20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define SREG _SFR_IO8(0x3F)
#define DDRB _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

#define cli()  __asm__ __volatile__ ("cli" ::: "memory")
#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


#define __INTR_ATTRS used, externally_visible
#ifdef __cplusplus
#  define ISR(vector, ...)            \
    extern "C" void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)
#else
#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)
#endif

volatile unsigned long timer0_overflow_count = 0;
volatile unsigned long timer0_millis = 0;
static unsigned char timer0_fract = 0;

ISR(TIMER0_OVF_vect)
{
    // copy these to local variables so they can be stored in registers
    // (volatile variables must be read from memory on every access)
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

static void __empty() {
    // Empty
}
//void yield(void) __attribute__ ((weak, alias("__empty")));
void yield(void) { }

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





void init() {
    sei();

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

#if 0
    // timers 1 and 2 are used for phase-correct hardware pwm
    // this is better for motors as it ensures an even waveform
    // note, however, that fast pwm mode can achieve a frequency of up
    // 8 MHz (with a 16 MHz clock) at 50% duty cycle
    TCCR1B = 0;
    sbi(TCCR1B, CS11);
//#if F_CPU >= 8000000L
    sbi(TCCR1B, CS10);
//#endif
    // put timer 1 in 8-bit phase correct pwm mode
    sbi(TCCR1A, WGM10);

    // set timer 2 prescale factor to 64
    sbi(TCCR2B, CS22);
    // configure timer 2 for phase correct pwm (8-bit)
    sbi(TCCR2A, WGM20);

//#if F_CPU >= 16000000 // 16 MHz / 128 = 125 KHz
    sbi(ADCSRA, ADPS2);
    sbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS0);
//#endif
    sbi(ADCSRA, ADEN);

    // the bootloader connects pins 0 and 1 to the USART; disconnect them
    // here so they can be used as normal digital i/o; they will be
    // reconnected in Serial.begin()
    UCSR0B = 0;
#endif
}

int main()
{
    init();

    uint8_t pin = 5;
    uint8_t bit = 1<<pin;
    volatile uint8_t *reg = ((volatile uint8_t *)((uint16_t)(&DDRB)));
    volatile uint8_t *out = ((volatile uint8_t *)((uint16_t)(&PORTB)));

    uint8_t oldSREG = SREG;
    cli();
    *reg |= bit;
    SREG = oldSREG;

	const int n = 500;

    for(;;) {
        delay(n);

        {
            oldSREG = SREG;
            cli();
            *out |= bit;
            SREG = oldSREG;
        }

        delay(n);

        {
            oldSREG = SREG;
            cli();
            *out &= ~bit;
            SREG = oldSREG;
        }
    }
    return 0;
}
