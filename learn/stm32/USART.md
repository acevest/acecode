# USART


# debug

如果是用STM32CubeIDE生成的代码

只需要在`usart.c`里添加如下几行

```
#include <stdio.h>
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
		HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
		return ch;
}
```

生成代码的时候，选`USART1`，其它也可以，只是OneNetMiniBoard是`USART1`连到USB

`Mode: Asynchronous`

`Hadware Flow Control (RS233): Disable`