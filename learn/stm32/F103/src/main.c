/*
 * main.c
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */


#include "stm32f103.h"


#include "gpio.h"
#include "rcc.h"

#define APB2ENR (*(unsigned int*)(RCC_BASE+0x18))

unsigned int pin = 8;


void SystemInit() {
	// 使能时钟
	RCCEnableGPIOBClock();

	GPIOSetOutput(GPIOB, pin, GPIO_OUTPUT_MODE_GP_PP, GPIO_OUTPUT_SPEED_50MHZ);
}

void delay() {
	int i=65536;
	while(i--);
}

int main() {

	while(1) {
		GPIOWrite(GPIOB, pin, HIGH);
		delay();
		GPIOWrite(GPIOB, pin, LOW);
		delay();
		continue;
		GPIOToggle(GPIOB, pin);
		delay();
	}

	return 0;
}
