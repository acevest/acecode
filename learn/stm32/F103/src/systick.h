/*
 * systick.h
 *
 *  Created on: May 26, 2019
 *      Author: ace
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "stm32f103.h"

typedef struct {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
} SysTick_t;

#define SysTick ((SysTick_t*) 0xE000E010)

void InitSysTick();
void Delay(uint32_t ms);
void NoneIntDelay(uint32_t ms);
#endif /* SYSTICK_H_ */
