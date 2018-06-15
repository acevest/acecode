/*
 * ------------------------------------------------------------------------
 *   File Name: AceAvr.h
 *      Author: Zhao Yanbai
 *              2018-06-14 20:28:08 Thursday CST
 * Description: none
 * ------------------------------------------------------------------------
 */

#pragma once

// ATmega328P
#define __SFR_OFFSET 0x20
#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
#define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define SREG _SFR_IO8(0x3F)
#define DDRB _SFR_IO8(0x04)
#define PORTB _SFR_IO8(0x05)

// F_CPU 定义在命令行中
#ifndef F_CPU
#error "did not define F_CPU"
#endif
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )

#define cli()  __asm__ __volatile__ ("cli" ::: "memory")
#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
