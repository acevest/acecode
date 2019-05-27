/*
 * systick.c
 *
 *  Created on: May 26, 2019
 *      Author: ace
 */


#include "systick.h"

#define SYSTICK_CTRL_COUNTFLAG_POS		16
#define SYSTICK_CTRL_COUNTFLAG_MASK		(1 << SYSTICK_CTRL_COUNTFLAG_POS)
#define SYSTICK_CTRL_COUNTFLAG_ENABLE	(1 << SYSTICK_CTRL_COUNTFLAG_POS)

#define SYSTICK_CTRL_CLKSOURCE_POS	2
#define SYSTICK_CTRL_CLKSOURCE_MASK (1 << SYSTICK_CTRL_CLKSOURCE_POS)
#define SYSTICK_CTRL_CLKSOURCE_FCLK	(1 << SYSTICK_CTRL_CLKSOURCE_POS)

#define SYSTICK_CTRL_TICKINT_POS	1
#define SYSTICK_CTRL_TICKINT_MASK	(1 << SYSTICK_CTRL_TICKINT_POS)
#define SYSTICK_CTRL_TICKINT_ENABLE	(1 << SYSTICK_CTRL_TICKINT_POS)

#define SYSTICK_CTRL_ENABLE_POS		0
#define SYSTICK_CTRL_ENABLE_MASK	(1 << SYSTICK_CTRL_ENABLE_POS)
#define SYSTICK_CTRL_ENABLE 		(1 << SYSTICK_CTRL_ENABLE_POS)

uint32_t gSysTickCnt = 0;
void SysTick_Handler() {
	gSysTickCnt++;
}

// 每1ms触发一次SysTick中断
void InitSysTick() {
	SysTick->CTRL &= ~SYSTICK_CTRL_ENABLE_MASK;
	SysTick->CTRL &= ~SYSTICK_CTRL_TICKINT_MASK;
	SysTick->CTRL &= ~SYSTICK_CTRL_CLKSOURCE_MASK;


	SysTick->LOAD = 9000;
	SysTick->VAL  = 0;


	SysTick->CTRL |= SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_TICKINT_ENABLE;
}

void Delay(uint32_t ms) {
	gSysTickCnt = 0;
	while(gSysTickCnt < ms) {

	}
}

// 非中断版本的Delay
// ms 最大值为1864
void NoneIntDelay(uint32_t ms) {
	SysTick->CTRL &= ~SYSTICK_CTRL_ENABLE_MASK;
	SysTick->CTRL &= ~SYSTICK_CTRL_TICKINT_MASK;
	SysTick->CTRL &= ~SYSTICK_CTRL_CLKSOURCE_MASK;


	SysTick->LOAD = 9000*ms;
	SysTick->VAL  = 0;


	SysTick->CTRL |= SYSTICK_CTRL_ENABLE;

	uint32_t t = 0;
	do {
		t = SysTick->CTRL;
	} while(((t & SYSTICK_CTRL_ENABLE) != 0) && ((t & SYSTICK_CTRL_COUNTFLAG_ENABLE) == 0));

	SysTick->VAL  = 0;
	SysTick->CTRL &= ~SYSTICK_CTRL_ENABLE_MASK;
}
