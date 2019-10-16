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

## USART转发优化版本

```
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#define BOARD_STANDARD
//#define BOARD_NBIOT

// 如果要测试BOARD_STANDARD上的M6312，则必需：
// 1. 5V/2A电源要供电
// 2. PC4_M6312_PWR_KEY 要设置为推挽输入，高电平
// 3. J10接线端子用跳线帽接到M6312上

#define USART_RX_BUFSZ  32
#define USART_TX_BUFSZ  32
typedef struct {
    uint8_t rxbuf[USART_RX_BUFSZ];
    uint8_t txbuf[USART_TX_BUFSZ];
    uint16_t rxwp;
    uint16_t rxrp;
    UART_HandleTypeDef *huart;
    uint8_t rxdata;
} DebugUsart_t;

#define INIT_DEBUG_USART(_name, _huart)	\
	static DebugUsart_t _name = {		\
			.rxwp	= 0,		\
			.rxrp   = 0,		\
			.huart  = &_huart,	\
			.rxdata = 0			\
	};



INIT_DEBUG_USART(__usart1, huart1)

#if defined(BOARD_STANDARD)
	INIT_DEBUG_USART(__usart2, huart2)
	#define LED_GPIO_Port	STANDARD_LED_GPIO_Port
	#define LED_Pin		 	STANDARD_LED_Pin
	#define UsartA __usart1
	#define UsartB __usart2
#elif defined(BOARD_NBIOT)
	INIT_DEBUG_USART(__usart3, huart3)
	#define LED_GPIO_Port	NB_LED_GPIO_Port
	#define LED_Pin		 	NB_LED_Pin
	#define UsartA __usart1
	#define UsartB __usart3
#else
	#error "must define board"
#endif



void InitUsartTransfer(){
    if(HAL_OK != HAL_UART_Receive_IT(UsartA.huart, &UsartA.rxdata, 1)) {
        Error_Handler();
    }

    if(HAL_OK != HAL_UART_Receive_IT(UsartB.huart, &UsartB.rxdata, 1)) {
        Error_Handler();
    }
}


int ReadUsartData(DebugUsart_t *data, uint8_t *ch) {
    uint16_t rxwp = data->rxwp;
    if(data->rxrp == rxwp) {
        // empty
        return -1;
    }
    *ch = data->rxbuf[data->rxrp];
    data->rxrp = (data->rxrp + 1) % USART_RX_BUFSZ;
    return 0;
}


void ReceiveUsartData(DebugUsart_t *data) {
    if((data->rxwp + 1) % USART_RX_BUFSZ == data->rxrp) {
        // full
        goto end;
    }

    data->rxbuf[data->rxwp] = data->rxdata;

    data->rxwp =(data->rxwp + 1) % USART_RX_BUFSZ;

end:
    if(HAL_OK != HAL_UART_Receive_IT(data->huart, &data->rxdata, 1)) {
        //Error_Handler();
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == UsartA.huart) {
        return ReceiveUsartData(&UsartA);
	}

	if(huart == UsartB.huart) {
        return ReceiveUsartData(&UsartB);
    }
}


int TransferData(DebugUsart_t *from ,DebugUsart_t *to) {
	int cnt = 0;
	while(cnt < USART_TX_BUFSZ) {
		uint8_t ch;
		if(0 != ReadUsartData(from, &ch)) {
			break;
		}
		from->txbuf[cnt++] = ch;
	}

	if(cnt > 0) {
		HAL_UART_Transmit(to->huart, from->txbuf, cnt, 0xFFFF);
	}

	return cnt;
}

void TransferTask(void *arg) {
	while(1) {
		// 以下两次调用不得直接放到if表达式中
		int cnt1 = TransferData(&UsartA, &UsartB);
		int cnt2 = TransferData(&UsartB, &UsartA);

		if(cnt1 == 0 && cnt2 == 0) {
			osDelay(1);
		}
	}
}

void LedTask(void *pdata) {
    while(1) {
    	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        osDelay(100);
    }
}

osThreadDef(transferTask, TransferTask, osPriorityNormal, 0, 128);
osThreadDef(ledTask, LedTask, osPriorityLow, 0, 64);

void InitDebug() {
	InitUsartTransfer();

#if defined(BOARD_STANDARD)
	HAL_GPIO_WritePin(M6312_PWRKEY_GPIO_Port, M6312_PWRKEY_Pin, GPIO_PIN_SET);
#endif

	osThreadId taskHandle;
	taskHandle = osThreadCreate(osThread(transferTask), NULL);
	if(taskHandle == NULL) {
		Error_Handler();
	}

	taskHandle = osThreadCreate(osThread(ledTask), NULL);
	if(taskHandle == NULL) {
		Error_Handler();
	}
}


#if 1
#include <stdio.h>
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
#if defined(BOARD_CHINA_MOBILE_NBIOT)
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
#endif
	return ch;
}
#endif


```


# USART1、USART2 DMA转发
```
#define USART_RX_BUFSZ	64
typedef struct {
	uint32_t len : 24;
	uint32_t end : 8;
	DMA_HandleTypeDef *dmarx;
	DMA_HandleTypeDef *dmatx;
	uint8_t  buf[USART_RX_BUFSZ];
}UsartDmaData_t;

UsartDmaData_t  usart1_dma_data;
UsartDmaData_t  usart2_dma_data;

void InitUsartDmaTransfer(){
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);

	memset(&usart1_dma_data, 0, sizeof(usart1_dma_data));
	memset(&usart2_dma_data, 0, sizeof(usart2_dma_data));

	usart1_dma_data.dmarx = &hdma_usart1_rx;
	usart2_dma_data.dmarx = &hdma_usart2_rx;
	usart1_dma_data.dmatx = &hdma_usart1_tx;
	usart2_dma_data.dmatx = &hdma_usart2_tx;

	HAL_UART_Receive_DMA(&huart1, usart1_dma_data.buf, USART_RX_BUFSZ);
	HAL_UART_Receive_DMA(&huart2, usart2_dma_data.buf, USART_RX_BUFSZ);
}


void TransferToUsart(UsartDmaData_t *data, UART_HandleTypeDef *from_huart, UART_HandleTypeDef *to_huart){
	if(data->end != 1) {
		return;
	}

	HAL_UART_Transmit_DMA(to_huart, data->buf, data->len);
	//HAL_UART_Transmit(to_huart, data->buf, data->len, 0xFFFF);
	data->len = 0;
	data->end = 0;
	HAL_UART_Receive_DMA(from_huart, data->buf, USART_RX_BUFSZ);
}

void TransferUsartData() {
	TransferToUsart(&usart1_dma_data, &huart1, &huart2);
	TransferToUsart(&usart2_dma_data, &huart2, &huart1);
}

void ReceiveUsartDmaData(UsartDmaData_t *data, UART_HandleTypeDef *huart) {
	uint32_t flag = __HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE);
	if(flag == RESET) {
		return;
	}

	__HAL_UART_CLEAR_IDLEFLAG(huart);

	//软件清空空闲中断标志位
	volatile tmp;
	tmp =huart->SR;
	tmp =huart->DR;   

	HAL_UART_DMAStop(huart);

	data->len = USART_RX_BUFSZ - data->dmarx->Instance->CNDTR;
	data->end = 1;
}


void ReceiveUsartData(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART1) {
		return ReceiveUsartDmaData(&usart1_dma_data, huart);
	}

	if(huart->Instance == USART2) {
		return ReceiveUsartDmaData(&usart2_dma_data, huart);
	}
}
```

```
// stm32f1xx_it.c


void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
  ReceiveUsartData(&huart1);
  /* USER CODE END USART1_IRQn 1 */
}


void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
  ReceiveUsartData(&huart2);
  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
  /* USER CODE END USART2_IRQn 1 */
}

```

```
  // main.c
  InitUsartDmaTransfer();
  while (1)
  {
	TransferUsartData();
  }
```