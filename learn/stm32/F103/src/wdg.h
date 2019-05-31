/*
 * iwdg.h
 *
 *  Created on: May 29, 2019
 *      Author: ace
 */

#ifndef WDG_H_
#define WDG_H_

#include "stm32f103.h"


#define IWDG_BASE (APB1PERIPH_BASE+0x3000)


//  超时时间

// Tout = ((2^(2+prer))xrlr)/40)
typedef struct {
	// 向KR里
	// 写入0x5555取消PR、RLR的写保护
	// 写入0xAAAA来喂狗
	// 写入0xCCCC来启动看门狗
	volatile uint32_t KR:16;	// 键寄存器
	volatile uint32_t __KR:16;
	volatile uint32_t PR:3;	// 预分频寄存器
	volatile uint32_t __PR:29;
	volatile uint32_t RLR:12;	// 重装载寄存器
	volatile uint32_t __RLR;
	volatile uint32_t SR;	// 状态寄存器
} IWDG_t;

#define IWDG ((IWDG_t *)IWDG_BASE)

#define IWDG_KEY_WRITE_DISABLE	0x0000
#define IWDG_KEY_WRITE_ENABLE	0x5555
#define IWDG_KEY_RELOAD			0xAAAA
#define IWDG_KEY_ENABLE			0xCCCC


#define IWDG_PRESCALER_4		0x00000000
#define IWDG_PRESCALER_8		0x00000001
#define IWDG_PRESCALER_16		0x00000002
#define IWDG_PRESCALER_32		0x00000003
#define IWDG_PRESCALER_64		0x00000004
#define IWDG_PRESCALER_128		0x00000005
#define IWDG_PRESCALER_256		0x00000006

void IWDG_Init(uint32_t prer, uint32_t rlr);
void IWDG_Feed();

#endif /* WDG_H_ */
