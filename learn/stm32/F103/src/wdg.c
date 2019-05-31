/*
 * iwdg.c
 *
 *  Created on: May 29, 2019
 *      Author: ace
 */

#include "wdg.h"

void IWDG_Init(uint32_t prer, uint32_t rlr) {
	IWDG->KR = IWDG_KEY_WRITE_ENABLE;
	IWDG->PR = prer;
	IWDG->RLR= rlr;
	IWDG->KR = IWDG_KEY_RELOAD;
	IWDG->KR = IWDG_KEY_ENABLE;
}


void IWDG_Feed() {
	IWDG->KR = IWDG_KEY_RELOAD;
}
