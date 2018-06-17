# ATmega328P


## 中断
### 中断向量表
|Vector| No Program Address| Source Interrupts| definition|
|:-:|---|---|:--|
|0| 0x0000| RESET| External Pin, Power-on Reset, Brown-out Reset and Watchdog System Reset|
|1| 0x0002| INT0| External Interrupt Request 0|
|2| 0x0004| INT1| External Interrupt Request 1|
|3| 0x0006| PCINT0| Pin Change Interrupt Request 0|
|4| 0x0008| PCINT1| Pin Change Interrupt Request 1|
|5| 0x000A| PCINT2| Pin Change Interrupt Request 2|
|6| 0x000C| WDT| Watchdog Time-out Interrupt|
|7| 0x000E| TIMER2_COMPA| Timer/Counter2 Compare Match A|
|8| 0x0010| TIMER2_COMPB| Timer/Coutner2 Compare Match B|
|9| 0x0012| TIMER2_OVF| Timer/Counter2 Overflow|
|10| 0x0014| TIMER1_CAPT| Timer/Counter1 Capture Event|
|11| 0x0016| TIMER1_COMPA| Timer/Counter1 Compare Match A|
|12| 0x0018| TIMER1_COMPB| Timer/Coutner1 Compare Match B|
|13| 0x001A| TIMER1_OVF| Timer/Counter1 Overflow|
|14| 0x001C| TIMER0_COMPA| Timer/Counter0 Compare Match A|
|15| 0x001E| TIMER0_COMPB| Timer/Coutner0 Compare Match B|
|16| 0x0020| TIMER0_OVF| Timer/Counter0 Overflow|
|17| 0x0022| SPI STC| SPI Serial Transfer Complete|
|18| 0x0024| USART_RX| USART Rx Complete|
|19| 0x0026| USART_UDRE| USART Data Register Empty|
|20| 0x0028| USART_TX| USART Tx Complete|
|21| 0x002A| ADC| ADC Conversion Complete|
|22| 0x002C| EE READY| EEPROM Ready|
|23| 0x002E| ANALOG COMP| Analog Comparator|
|24| 0x0030| TWI| 2-wire Serial Interface (I2C)|
|25| 0x0032| SPM| READY Store Program Memory Ready|

上表中的地址是按16bit算的

编写对应的中断程序，以`TIMER1_OVF`举例，按如下格式

```
extern "C" void __vector_16() __attribute__ ((signal,used, externally_visible));
void __vector_16()
{
	// ...
}
```

### 中断向量表所在位置
|BOOTRST| IVSEL| Reset Address| Interrupt Vectors Start Address|
|---|---|---|:--|
|1| 0| 0x000| 0x002|
|1| 1| 0x000| Boot Reset Address + 0x0002|
|0| 0| Boot Reset Address| 0x002|
|0| 1| Boot Reset Address| Boot Reset Address + 0x0002|

* BOOTRST是fuse.high_byte.BOOTRST比特们，1表示unprogramed，reset时从地址0开始，0表示programed，reset时从地址`Boot Reset Address`开始
* 地址`Boot Reset Address`与BOOTSZ即fuse.hih_byte[2:1]相关
* IVSEL是MCUCR寄存器的第1个bit

### 外部中断
* 如果启用中断，就算将INT、PCINT引脚配置成`OUTPUT`也会触发中断
### PCINT和INT引脚的差别
* INT限制在了两个端口上面，而PCINT则是所有接口都具备。
* INT具有上沿，下沿，低电平，高电平触发这几种模式，而PCINT只有测量电平的变化这一个模式。
* INT可以了解具体是哪个口触发的，而PCINT不行。
* PCINT不会直接跳转入指定的程序，用户需要读取寄存器来做判断是哪个PCINT端口产生了变化。
* INT0和INT1各自可配置一个中断程序入口，而所有的PCINT都只会触发跳转进入一条指定的程序。

