/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


// arduino ~3号引脚接940纳米发送头的长引脚
// 短引脚接100欧电阻，再接GND

#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {

  // 电信机顶盒用NEC发送
  
	irsend.sendNEC(0xCD3201FE, 32); // 音量+
  Serial.println("+");
	delay(1000);
	irsend.sendNEC(0xCD32817E, 32); // 音量-
  Serial.println("-");
  delay(1000);


  // 小米电视遥控
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  // xiaomi increase volume signal
  unsigned int ivs[] = {1000,600, 550,1150, 600,600, 550,900, 550,1150, 600,550, 600,600, 550,1450, 550,1200, 550,600, 550,600, 550};
  // xiaomi decrease volume signal
  unsigned int dvs[] = {1050,550, 650,1050, 650,500, 650,800, 650,1100, 650,500, 650,500, 650,1400, 650,1350, 650,500, 650,800, 650};
  irsend.sendRaw(ivs, sizeof(ivs) / sizeof(ivs[0]), khz);
  Serial.println("tv+");
  delay(1000); 
  irsend.sendRaw(dvs, sizeof(dvs) / sizeof(dvs[0]), khz); 
  Serial.println("tv-");
  delay(1000); 
}
