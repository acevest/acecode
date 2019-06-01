/*
 * System.c
 *
 *  Created on: Jun 1, 2019
 *      Author: ace
 */


#include "stm32f1xx_hal.h"

void SystemPreInit() {
	__HAL_RCC_GPIOB_CLK_ENABLE();
}


#define LED_Pin 		GPIO_PIN_6
#define LED_GPIO_Port	GPIOB

void SystemSetup() {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode	= GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pin		= LED_Pin;
	GPIO_InitStruct.Pull	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
}

void SystemLoop() {
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	HAL_Delay(1000);
}
