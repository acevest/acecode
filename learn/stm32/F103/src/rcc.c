/*
 * rcc.c
 *
 *  Created on: May 24, 2019
 *      Author: ace
 */

#include "rcc.h"

void __RCCEnableAPB2(uint32_t en) {
	RCC->APB2ENR |= en;
}
