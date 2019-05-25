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


#define RCC_CR_HSION	0x00000001
#define RCC_CR_HSIRDY	0x00000002
#define RCC_CR_HSEON 	0x00010000
#define RCC_CR_HSERDY	0x00020000
#define RCC_CR_HSEBYP	0x00040000
#define RCC_CR_CSSON	0x00080000
#define RCC_CR_PLLON	0x01000000
#define RCC_CR_PLLRDY	0x02000000


#define RCC_CFGR_HPRE_DIV_MASK    0x000000F0
#define RCC_CFGR_HPRE_DIV1   0x00000000
#define RCC_CFGR_HPRE_DIV2   0x00000080
#define RCC_CFGR_HPRE_DIV4   0x00000090
#define RCC_CFGR_HPRE_DIV8   0x000000A0
#define RCC_CFGR_HPRE_DIV16  0x000000B0
#define RCC_CFGR_HPRE_DIV64  0x000000C0
#define RCC_CFGR_HPRE_DIV128 0x000000D0
#define RCC_CFGR_HPRE_DIV256 0x000000E0
#define RCC_CFGR_HPRE_DIV512 0x000000F0


#define RCC_CFGR_PPRE1_DIV_MASK 0x0000007FF
#define RCC_CFGR_PPRE1_DIV1	 0x00000000
#define RCC_CFGR_PPRE1_DIV2  0x00000400
#define RCC_CFGR_PPRE1_DIV4  0x00000500
#define RCC_CFGR_PPRE1_DIV8  0x00000600
#define RCC_CFGR_PPRE1_DIV16 0x00000700

#define RCC_CFGR_PPRE2_DIV_MASK 0x000038FF
#define RCC_CFGR_PPRE2_DIV1  0x00000000
#define RCC_CFGR_PPRE2_DIV2  0x00002000
#define RCC_CFGR_PPRE2_DIV4  0x00002800
#define RCC_CFGR_PPRE2_DIV8  0x00003000
#define RCC_CFGR_PPRE2_DIV16 0x00003800

#define RCC_CFGR_PLLMULL_MASK 0x003C0000
#define RCC_CFGR_PLLMULL_2 	 0x00000000
#define RCC_CFGR_PLLMULL_3 	 0x00040000
#define RCC_CFGR_PLLMULL_4 	 0x00080000
#define RCC_CFGR_PLLMULL_5 	 0x000C0000
#define RCC_CFGR_PLLMULL_6 	 0x00100000
#define RCC_CFGR_PLLMULL_7 	 0x00140000
#define RCC_CFGR_PLLMULL_8 	 0x00180000
#define RCC_CFGR_PLLMULL_9 	 0x001C0000
#define RCC_CFGR_PLLMULL_10	 0x00200000
#define RCC_CFGR_PLLMULL_11	 0x00200000
#define RCC_CFGR_PLLMULL_12	 0x00280000
#define RCC_CFGR_PLLMULL_13	 0x002C0000
#define RCC_CFGR_PLLMULL_14	 0x00300000
#define RCC_CFGR_PLLMULL_15	 0x00340000
#define RCC_CFGR_PLLMULL_16	 0x00380000


#define RCC_CFGR_PLLXTYPE_MASK		0x00020000
#define RCC_CFGR_PLLXTYPE_HSE		0x00000000
#define RCC_CFGR_PLLXTYPE_HSE_HALF	0x00020000

#define RCC_CFGR_PLLSRC_MASK 0x00010000
#define RCC_CFGR_PLLSRC_HSI	 0x00000000
#define RCC_CFGR_PLLSRC_HSE	 0x00010000

#define RCC_CFGR_SW_MASK	0x00000003
#define RCC_CFGR_SW_HSI		0x00000000
#define RCC_CFGR_SW_HSE		0x00000001
#define RCC_CFGR_SW_PLL		0x00000002




#define HSE_STARTUP_TIMEOUT	0x500


typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t RESERVED;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
} FLASH_t;


#define FLASH_R_BASE          	(AHBPERIPH_BASE + 0x2000)
#define FLASH               	((FLASH_t *) FLASH_R_BASE)
#define  FLASH_ACR_LATENCY_2    ((uint8_t)0x02)
#define FLASH_ACR_PRFTBE        ((uint8_t)0x10)
#define  FLASH_ACR_LATENCY      ((uint8_t)0x03)

void SetSystemClock72MHz() {


	RCC->CR |= RCC_CR_HSEON;

	volatile uint32_t StartupCnt = 0;
	volatile uint32_t Status = 0;

	do {
		Status = RCC->CR & RCC_CR_HSERDY;
		StartupCnt++;
	} while(Status == 0 && StartupCnt < HSE_STARTUP_TIMEOUT);



	// APB1 PRE
	RCC->CFGR &= ~RCC_CFGR_PPRE1_DIV_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	// APB2 PRE
	RCC->CFGR &= ~RCC_CFGR_PPRE2_DIV_MASK;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;


	FLASH->ACR |= FLASH_ACR_PRFTBE;
	FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
	FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

	// 以下设置需要关闭PLL
	RCC->CR &= ~RCC_CR_PLLON;

	// PLLMUL
	RCC->CFGR &= ~RCC_CFGR_PLLMULL_MASK;
	RCC->CFGR |= RCC_CFGR_PLLMULL_6;  // OneNet Mini板上是接的12MHz晶振，所以倍数为6就能得到72MHz


	// XTYPE: select HSE
	RCC->CFGR &= ~RCC_CFGR_PLLXTYPE_MASK;
	RCC->CFGR |= RCC_CFGR_PLLXTYPE_HSE;

	// PLLSRC: select PLLSRC
	RCC->CFGR &= ~RCC_CFGR_PLLSRC_MASK;
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;

	// SW: System Clock Switch
	RCC->CFGR &= ~RCC_CFGR_SW_MASK;
	RCC->CFGR |= RCC_CFGR_SW_PLL;


	RCC->CR |= RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLON == 0) { }
}

void InitSystemClock() {
	SetSystemClock72MHz();
	return;
	// 启动HSI
	RCC->CR |= RCC_CR_HSION;

	// WAIT HSI

	// SW： System Close Switch 重置为 HSI
	RCC->CFGR &= ~(0xF << 0);


	// HPRE: AHB预分频设置为不分频，即SYSCLK->HCLK不被分频
	RCC->CFGR &= ~(0xF << 4);


	// PPRE1: APB1预分频设置为不分频，即HCLK->PCLK1不被分频
	// 此处软件必需保证频率不能超过36MHz
	RCC->CFGR &= ~(0x7 << 8);

	// PPRE2: APB2预分频系数设置为不分频，即HCLK->PCLK2不被分频
	RCC->CFGR &= ~(0x7 << 11);


	// ADCPRE: ADC预分频系统设置为2分频,即PCLK2/2->ADCCLK
	RCC->CFGR &= ~(0x3 << 14);

	// MCO: Mironcontroller Clock Output 禁止时钟输出
	RCC->CFGR &= ~(0x7 << 24);

	// 关闭HSE
	RCC->CR &= ~RCC_CR_HSEON;

	// 关闭CSS
	RCC->CR &= ~RCC_CR_CSSON;

	// 关闭PLL
	RCC->CR &= ~RCC_CR_PLLON;

	// External High Speed Clock Ready Flag
	// 外部调整时钟没有旁路
	// 只有在外部4-16MHz振荡器关闭的情况下，才能写入该位。
	RCC->CR &= ~RCC_CR_HSEBYP;

	// 后续三项设置需要在PLL关闭的情况下进行才有效
	// PLL Src 设置为 HSI经2分频后输入
	RCC->CFGR &= ~(0x1 << 16);

	// PLLXTYPE 设置为HSE不分频输入
	RCC->CFGR &= ~(0x1 << 17);
	//RCC->CFGR |= 0x1 << 17;

	// PLLMUL 倍频系数设置为 2
	RCC->CFGR &= ~(0xF << 18);

	// USBPRE: USB预分频系数设置为1.5
	RCC->CFGR &= (~0x1) << 22;
}
