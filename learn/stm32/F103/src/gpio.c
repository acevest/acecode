/*
 * gpio.c
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */

#include "gpio.h"



void GPIOSetOutput(GPIO_t *gpio, uint32_t pin, GPIOOutputMode_t mode, GPIOOutputSpeed_t speed) {
	uint32_t *CR = pin < 8 ? &gpio->CRL : &gpio->CRH;
	uint32_t n = (pin < 8 ? pin : pin - 8) * 4;

	uint32_t mask = 0x0FU;
	*CR &=  ~mask << n; // 清除CNF、MODE的比特位
	*CR |=  (mode|speed) << n; // 设置为相应的输出模块+相应的速度
}


void GPIOToggle(GPIO_t *gpio, uint32_t pin) {
	gpio->ODR ^= 1 << pin;
}



void GPIOWrite(GPIO_t *gpio, uint32_t pin, uint32_t level) {
	if(level == LOW) {
		gpio->BRR |= 1 << pin;
	} else {
		gpio->BSRR |= 1 << pin;
	}
}
