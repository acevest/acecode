/*
* 发射红外线信号
* 注意! 红外线发射器(IR LED)必须接到 pin 3, 不能接其它脚位
 
 Hisense 机顶盒 SD-16127 tested
 */
 
//By Leo 2013.02.19
//http://weibo.com/leolite
//Update: Pin 3 IR LED test function
 
 
#include <IRremote.h>                  // 引用 IRRemote 函式库
 
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

IRsend irsend;                          // 定义 IRsend 物件来发射红外线讯号
decode_results results;


void setup()
{
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  /*
  irrecv.enableIRIn();
  
  pinMode(3, OUTPUT);   
  digitalWrite(3, HIGH);   // 点亮LED测试（需通过手机摄像模式观察）
  delay(3000);             // 等待3秒
  digitalWrite(3, LOW);    // 结束测试*/
}

void showIRProtocol(decode_results *results) 
{
  Serial.print("Protocol: ");
  
  // 判断红外线协定种类
  switch(results->decode_type) {
   case NEC:
     Serial.print("NEC");
     break;
   case SONY:
     Serial.print("SONY");
     break;
   case RC5:
     Serial.print("RC5");
     break;
   case RC6:
     Serial.print("RC6");
     break;
   default:
     Serial.print("Unknown encoding");  
  }  

  // 把红外线编码印到 Serial port
  Serial.print(", irCode: ");            
  Serial.print(results->value, HEX);    // 红外线编码
  Serial.print(",  bits: ");           
  Serial.println(results->bits);        // 红外线编码位元数    
}

void loop()
{
  //Serial.print("SendIR: ");
  //irsend.sendNEC(0x807FE01F, 32);   // 记得换成你遥控器的红外线编码
  //delay(100);             // 等待3秒
  
  if(irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    //Serial.println();
    showIRProtocol(&results);
    irrecv.resume();
  }
}

