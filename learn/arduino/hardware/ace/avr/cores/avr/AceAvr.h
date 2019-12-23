/*
 * ------------------------------------------------------------------------
 *   File Name: AceAvr.h
 *      Author: Zhao Yanbai
 *              2018-06-14 20:28:08 Thursday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include <HardwareSerial.h>
#include <kernel.h>

#define LOW  0
#define HIGH 1

#define INPUT	        0
#define OUTPUT	        1
#define INPUT_PULLUP    2

void delay(unsigned long ms);
void acevest();

// ATmega328P
#define __SFR_OFFSET 0x20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define DDRB    _SFR_IO8(0x04)
#define PORTB   _SFR_IO8(0x05)
#define DDRC    _SFR_IO8(0x07)
#define PORTC   _SFR_IO8(0x08)
#define DDRD    _SFR_IO8(0x0A)
#define PORTD   _SFR_IO8(0x0B)
#define SREG    _SFR_IO8(0x3F)


// F_CPU 定义在命令行中
#ifndef F_CPU
#error "did not define F_CPU"
#endif
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)
#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)


#define cli()  __asm__ __volatile__ ("cli" ::: "memory")
#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

const uint8_t PA = 1;
const uint8_t PB = 2;
const uint8_t PC = 3;
const uint8_t PD = 4;


uint8_t get_digital_pin_port(uint8_t pin);
uint8_t get_digital_pin_bit_mask(uint8_t pin);
volatile uint8_t* get_digital_pin_port_mode_register(uint8_t pin);
volatile uint8_t* get_digital_pin_port_output_register(uint8_t pin);


void set_digital_pin_mode(uint8_t pin, uint8_t mode);
void digital_write(uint8_t pin, uint8_t val);
void yield(void);

unsigned long millis();


typedef bool boolean;
typedef uint8_t byte;
