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



# USART1、USART2转发

需要开启这两个串口的中断

```
#define USART_RX_BUFSZ	10
typedef struct {
	uint8_t rxdata;
	uint8_t rxbuf[USART_RX_BUFSZ];
	uint16_t rxwp;
	uint16_t rxrp;
} UsartData_t;

UsartData_t usart1_data;
UsartData_t usart2_data;


void InitUsartTransfer(){
	usart1_data.rxrp = usart1_data.rxwp = 0;
	usart2_data.rxrp = usart2_data.rxwp = 0;
	if(HAL_OK != HAL_UART_Receive_IT(&huart1, &usart1_data.rxdata, 1)) {
		Error_Handler();
	}

	if(HAL_OK != HAL_UART_Receive_IT(&huart2, &usart2_data.rxdata, 1)) {
		Error_Handler();
	}
}

void TransferToUsart(UsartData_t *data, UART_HandleTypeDef *to_huart){
	uint16_t rxwp = data->rxwp;
	if(data->rxrp == rxwp) {
		// empty
		return ;
	}
	HAL_UART_Transmit(to_huart, data->rxbuf+data->rxrp, 1, 0xFFFF);
	data->rxrp = (data->rxrp + 1) % USART_RX_BUFSZ;
}

void TransferUsartData() {
	TransferToUsart(&usart1_data, &huart2);
	TransferToUsart(&usart2_data, &huart1);
}

void ReceiveUsartData(UsartData_t *data, UART_HandleTypeDef *huart) {
	if((data->rxwp + 1) % USART_RX_BUFSZ == data->rxrp) {
		// full
		goto end;
	}

	data->rxbuf[data->rxwp] = data->rxdata;

	data->rxwp =(data->rxwp + 1) % USART_RX_BUFSZ;

end:
	if(HAL_OK != HAL_UART_Receive_IT(huart, &data->rxdata, 1)) {
		//Error_Handler();
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART1) {
		return ReceiveUsartData(&usart1_data, huart);
	}

	if(huart->Instance == USART2) {
		return ReceiveUsartData(&usart2_data, huart);
	}
}
```

```
  // main.c
  InitUsartTransfer();

  while (1)
  {
	  TransferUsartData();
  }
```