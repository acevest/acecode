# arduino clock interrupt

## Clock Select Bit Description


|CS02|CS01|CS00|Description|
|---|---|---|---|
|0|0|0|no clock source (Timer/Counter stopped)|
|0|0|1|clk/1 (no prescaler)|
|0|1|0|clk/8 (from prescaler)|
|0|1|1|clk/64 (from prescaler)|
|1|0|0|clk/256 (from prescaler)|
|1|0|1|clk/1024 (from prescaler)|
|1|1|0|external clock source on T0 pin. clock falling edge|
|1|1|1|external clock source on T0 pin. clock rising edge|



|CS12|CS11|CS10|Description|
|---|---|---|---|
|0|0|0|no clock source (Timer/Counter stopped)|
|0|0|1|clk/1 (no prescaler)|
|0|1|0|clk/8 (from prescaler)|
|0|1|1|clk/64 (from prescaler)|
|1|0|0|clk/256 (from prescaler)|
|1|0|1|clk/1024 (from prescaler)|
|1|1|0|external clock source on T1 pin. clock falling edge|
|1|1|1|external clock source on T1 pin. clock rising edge|


|CS22|CS21|CS20|Description|
|---|---|---|---|
|0|0|0|no clock source (Timer/Counter stopped)|
|0|0|1|clk<sub>T2S</sub>/1 (no prescaler)|
|0|1|0|clk<sub>T2S</sub>/8 (from prescaler)|
|0|1|1|clk<sub>T2S</sub>/64 (from prescaler)|

## Compare Match Register计算方法

arduino有三个时钟计数器:Timer0、Timer1、Timer2。

arduino的时钟频率是16MHz，所以每个嘀嗒(tick)代表1/16000000秒(约为63ns)。而arduino的Timer0、Timer2的时钟计数器是8位、Timer1是16位。因此这就意味着就算把值设置成最大的，对于8位的将以256/1600000(约16us)，对于16位将以65536/16000000(约4ms)的频率触发。因此如果想让它频率变得更低一点，比如一秒触发一次就有点不现实。

除非可以利用预分频器(prescaler)来控制时钟计数器的增加方式：

`(时钟计数频率(Hz)) = 16MHz / prescaler`

所以当prescaler=1，时钟计数频率=16MHz；当prescaler=64，时钟计数频率=250KHz。

如上表所述，prescaler只能在1, 8, 64, 256, 1024中取值。

所以：

`(计数器触发频率(Hz)) = 16MHz / ( prescaler*(CompareMatchRegister+1) )`

变换一下上式：

`CompareMatchRegister = 16MHz / ( prescaler*(计数器触发频率(Hz)) ) - 1`

**注意：Timer0、Timer1的CompareMatchRegister必需小于256；Timer1的CompareMatchRegister必需小于65536**

所以如果想要1Hz的触发频率，则`CompareMatchRegister = 16MHz / ( 1024*1) - 1 = 15624`，这里的prescaler=1024，因为prescaler取到最大值了CompareMatchRegister还等于15624，256<15624<65536，所以必需要用到Timer1。


## 示例代码

```
void setup(){

  cli();//stop interrupts

  //设置timer0会影响到loop函数里调用的delay，会使其失效
  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler (参考上表)
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler (参考上表)
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  //set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler (参考上表)
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  sei();//allow interrupts

}//end setup

void loop() { }

ISR(TIMER0_COMPA_vect){ /* TODO */ }
ISR(TIMER1_COMPA_vect){ /* TODO */ }
ISR(TIMER2_COMPA_vect){ /* TODO */ }
```



## 注
1. 1MHz = 1 * 1000KHz = 1 * 1000 * 1000Hz，这里是1000不是1024