/*
 * rcc.h
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */

#ifndef RCC_H_
#define RCC_H_

#include "stm32f103.h"

typedef struct {
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
} RCC_t;

#define RCC ((RCC_t*) RCC_BASE)

#define RCC_APB2ENR_IOPAEN 0x00000004
#define RCC_APB2ENR_IOPBEN 0x00000008
#define RCC_APB2ENR_IOPCEN 0x00000010
#define RCC_APB2ENR_IOPDEN 0x00000020
#define RCC_APB2ENR_IOPEEN 0x00000040



void __RCCEnableAPB2(uint32_t en);

#define RCCEnableGPIOAClock() __RCCEnableAPB2(RCC_APB2ENR_IOPAEN)
#define RCCEnableGPIOBClock() __RCCEnableAPB2(RCC_APB2ENR_IOPBEN)
#define RCCEnableGPIOCClock() __RCCEnableAPB2(RCC_APB2ENR_IOPCEN)
#define RCCEnableGPIODClock() __RCCEnableAPB2(RCC_APB2ENR_IOPDEN)
#define RCCEnableGPIOEClock() __RCCEnableAPB2(RCC_APB2ENR_IOPEEN)

void InitSystemClock();
void EnableLSI();

#endif /* RCC_H_ */
