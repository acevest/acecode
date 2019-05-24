/*
 * gpio.h
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f103.h"


typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR; 	// Bit Set Reset Register
	uint32_t BRR;  	// Bit Reset Register
	uint32_t LCKR;
} GPIO_t;

#define GPIOA ((GPIO_t*)GPIOA_BASE)
#define GPIOB ((GPIO_t*)GPIOB_BASE)
#define GPIOC ((GPIO_t*)GPIOC_BASE)
#define GPIOD ((GPIO_t*)GPIOD_BASE)
#define GPIOE ((GPIO_t*)GPIOE_BASE)


typedef enum {
	GPIO_OUTPUT_MODE_GP_PP	= 0x00,
	GPIO_OUTPUT_MODE_GP_OD	= 0x01,
	GPIO_OUTPUT_MODE_AF_PP 	= 0x02,
	GPIO_OUTPUT_MODE_AF_OD	= 0x03,
} GPIOOutputMode_t;


typedef enum {
	GPIO_OUTPUT_SPEED_10MHZ	= 0x01,
	GPIO_OUTPUT_SPEED_20MHZ	= 0x02,
	GPIO_OUTPUT_SPEED_50MHZ	= 0x03,
} GPIOOutputSpeed_t;

#define HIGH 1
#define LOW	 0



void GPIOSetOutput(GPIO_t *gpio, uint32_t pin, GPIOOutputMode_t mode, GPIOOutputSpeed_t speed);

void GPIOToggle(GPIO_t *gpio, uint32_t pin);
void GPIOWrite(GPIO_t *gpio, uint32_t pin, uint32_t level);


#endif /* GPIO_H_ */
