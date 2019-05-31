/*
 * main.c
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */


#include "stm32f103.h"


#include "gpio.h"
#include "rcc.h"
#include "systick.h"
#include "wdg.h"
#include <stdio.h>
unsigned int pin = 8;


void SystemInit() {
	InitSystemClock();

	// 不知道为啥低于IWDG_PRESCALER_64不能正常复位
	IWDG_Init(IWDG_PRESCALER_64, 625*2);
	EnableLSI();


#define DBGMCU_CR (*((uint32_t*)0xE0042004))
	DBGMCU_CR &= ~(1 << 8);

	InitSysTick();

	// 使能时钟
	RCCEnableGPIOBClock();


	GPIOSetOutput(GPIOB, pin, GPIO_OUTPUT_MODE_GP_PP, GPIO_OUTPUT_SPEED_50MHZ);
	GPIOWrite(GPIOB, pin, HIGH);
}

void delay() {
	//Delay(100);
	NoneIntDelay(100);
}

int main() {
	delay();
	GPIOWrite(GPIOB, pin, LOW);

	uint32_t n = 0;
	while(1) {
		IWDG_Feed();
		continue;
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
