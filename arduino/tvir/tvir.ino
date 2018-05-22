// arduino ~3号引脚接940纳米发送头的长引脚
// 短引脚接100欧电阻，再接GND

#include <IRremote.h>
#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 4); // RX, TX


IRsend irsend;
const int ledPin = 5;


const int xiaomiRawCodeLen = 23;
enum {
  XIAOMI_RAWCODE_POWER,
  XIAOMI_RAWCODE_RETURN,
  XIAOMI_RAWCODE_SUBMIT,
  XIAOMI_RAWCODE_VOLUME_DEC,
  XIAOMI_RAWCODE_VOLUME_INC,
  
  XIAOMI_RAWCODE_UP,
  XIAOMI_RAWCODE_DOWN,
  XIAOMI_RAWCODE_LEFT,
  XIAOMI_RAWCODE_RIGHT,
  XIAOMI_RAWCODE_MENU,
  XIAOMI_RAWCODE_HOME,
  
  // ...
  XIAOMI_RAWCODE_MAX_INX
};


unsigned int xiaomiRawCode[][xiaomiRawCodeLen] = {
  // power
  {1100, 500, 650, 500, 650, 1400, 650, 1350, 650, 500, 650, 1400, 650, 500, 650, 1350, 650, 550, 650, 1350, 650, 1350, 650},
  // return
  {950, 650, 500, 1200, 550, 650, 550, 850, 550, 1250, 500, 650, 450, 650, 550, 900, 550, 1500, 500, 1250, 500, 900, 550},
  // submit
  {1000, 600, 550, 1200, 550, 600, 550, 900, 550, 1150, 600, 600, 550, 600, 550, 1450, 550, 900, 550, 600, 550, 1500, 550},
  // decrease volume signal
  {1050, 550, 650, 1050, 650, 500, 650, 800, 650, 1100, 650, 500, 650, 500, 650, 1400, 650, 1350, 650, 500, 650,800, 650},
  // increase volume signal
  {1000, 600, 550, 1150, 600, 600, 550, 900, 550, 1150, 600, 550, 600, 600, 550, 1450, 550, 1200, 550, 600, 550,600, 550},

  // 上
  {1100, 500, 600, 1150, 650, 500, 600, 850, 650, 1050, 650, 550, 650, 500, 650, 800, 650, 800, 650, 1050, 650, 1400, 650},
  // 下
  {1050, 550, 600, 1150, 600, 550, 600, 850, 650, 1050, 650, 550, 600, 550, 600, 850, 650, 1050, 650, 1100, 650, 500, 650},
  // 左
  {1000, 600, 600, 1150, 550, 600, 550, 900, 550, 1200, 550, 600, 550, 600, 550, 1200, 550, 1450, 550, 900, 550, 900, 550},
  // 右
  {1000, 600, 550, 1200, 550, 600, 550, 900, 550, 1150, 600, 600, 550, 600, 550, 1450, 550, 600, 600, 600, 550, 1150, 550},
  // Menu
  {1000, 600, 550, 1200, 550, 600, 550, 900, 550, 1200, 550, 600, 550, 600, 550, 900, 550, 600, 550, 1200, 550, 1150, 600},
  // Home
  {1000, 600, 550, 1200, 550, 600, 550, 900, 550, 1150, 600, 600, 550, 600, 550, 1150, 600, 600, 550, 900, 550, 1150, 550}
};

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
}

void BlinkLed(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
}

void SendXiaoMiSignal(int inx, const char *msg) {
  
  // 小米电视遥控
  const int khz = 38; // 38kHz carrier frequency for the NEC protocol
  irsend.sendRaw(xiaomiRawCode[inx], xiaomiRawCodeLen, khz);
  Serial.print("XiaoMi Signal: ");
  Serial.println(msg);
}

void loop() {
 
  int cmd = -1;
  
  if(btSerial.available() <= 0) {
    delay(10);
    return;
  }

  cmd = btSerial.read();
  Serial.print("Received Cmd: " );
  Serial.println(cmd);


  switch(cmd) {
  case 0:
    SendXiaoMiSignal(XIAOMI_RAWCODE_POWER, "power");
    break;
  case 1:
    SendXiaoMiSignal(XIAOMI_RAWCODE_SUBMIT, "submit");
    break;
    
  case 2:
    SendXiaoMiSignal(XIAOMI_RAWCODE_RETURN, "return");
    break;

  case 3:
    SendXiaoMiSignal(XIAOMI_RAWCODE_UP, "up");
    break;
    
  case 4:
    SendXiaoMiSignal(XIAOMI_RAWCODE_DOWN, "down");
    break;
    
  case 5:
    SendXiaoMiSignal(XIAOMI_RAWCODE_LEFT, "left");
    break;
    
  case 6:
    SendXiaoMiSignal(XIAOMI_RAWCODE_RIGHT, "right");
    break;

  case 7:
    irsend.sendNEC(0xCD32619E, 32); // 电信机顶盒频道-
    Serial.println("tvbox channel-");
    break;
  case 8:
    irsend.sendNEC(0xCD32A15E, 32); // 电信机顶盒频道+
    Serial.println("tvbox channel+");
    break; 

    
  case 9:
    SendXiaoMiSignal(XIAOMI_RAWCODE_MENU, "menu");
    break;
    
  case 10:
    SendXiaoMiSignal(XIAOMI_RAWCODE_HOME, "home");
    break;
       
  case 11:
    SendXiaoMiSignal(XIAOMI_RAWCODE_VOLUME_DEC, "tv volume -");
    break;
  case 12:
    SendXiaoMiSignal(XIAOMI_RAWCODE_VOLUME_INC, "tv volume +");
    break;
   
  case 13:
    irsend.sendNEC(0xCD32817E, 32); // 电信机顶盒音量-
    Serial.println("tvbox volume-");
    break;
  case 14:
    irsend.sendNEC(0xCD3201FE, 32); // 电信机顶盒音量+
    Serial.println("tvbox volume+");
    break;
    
  default:
    Serial.print("error code: ");
    Serial.println(cmd);
    BlinkLed(ledPin);
    break;
  }
  btSerial.write("OK:");
  btSerial.write(cmd);
  BlinkLed(ledPin);
}
