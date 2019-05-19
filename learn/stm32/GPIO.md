# GPIO




GPIO是挂在APB2下的

```
#define PERIPH_BASE 0x40000000
#define APB2PERIPH_BASE (PERIPH_BASE+0x10000)
#define GPIOA_BASE	(APB2PERIPH_BASE+0x0800)
#define GPIOB_BASE	(APB2PERIPH_BASE+0x0C00)
#define GPIOC_BASE	(APB2PERIPH_BASE+0x1000)
#define GPIOD_BASE	(APB2PERIPH_BASE+0x1400)
#define GPIOE_BASE	(APB2PERIPH_BASE+0x1800)
```

GPIO的时钟RCC是挂在AHB下的

```
#define AHBPERIPH_BASE (PERIPH_BASE+0x20000)
#define RCC_BASE	(AHBPERIPH_BASE+0x1000)
```


假设将PB9设置为推挽输出，并不断写高低电平

```
#define APB2ENR (*(unsigned int*)(RCC_BASE+0x18))
#define GPIOB_CRH (*(unsigned int*)(GPIOB_BASE+0x04))
#define GPIOB_ODR (*(unsigned int*)(GPIOB_BASE+0x0C))
#define GPIOB_BSRR (*(unsigned int*)(GPIOB_BASE+0x10))
#define GPIOB_BRR (*(unsigned int*)(GPIOB_BASE+0x14))

unsigned int pin = 9;

// 使能时钟
APB2ENR |= 1 << 3; // 使能PB的是第3个bit

// 设置为推挽输出
GPIOB_CRH &= ~(0xF<<((pin-8)*4));	// 清除CNF、MODE的比特位
GPIOB_CRH |= 0x3<<((pin-8)*4); // 设置为推挽输出的值

// 写高
GPIOB_BSRR = 1 << pin;

// 写低
GPIOB_BRR = 1 << pin;

// 取反
GPIOB_ODR ^= 1 << pin;
```