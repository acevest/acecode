#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 

const int RLedPin = 11;
const int BLedPin = 12;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RLedPin, OUTPUT);
  pinMode(BLedPin, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
int pos = 0;
int last_pos = 0;

void loop() 
{ 
  int lv = analogRead(0);  // Light
  int sign = 1;
  if(lv < 400)
  {
    sign = -1;
  }
  
  int st = sign * 10;
  
  pos += st;
  
  if(pos <= 30) pos = 30;
  if(pos >= 120) pos = 120;

  if(pos != last_pos)
  {
    if(sign == 1)
    {
      digitalWrite(RLedPin, HIGH);
      digitalWrite(BLedPin, LOW);
    }
    else
    {
      digitalWrite(RLedPin, LOW);
      digitalWrite(BLedPin, HIGH);      
    }
    Serial.print("<> pos");
    Serial.println(pos);
    myservo.write(pos);
    delay(15);
  }
  else
  {
   
      digitalWrite(RLedPin, LOW); 
      digitalWrite(BLedPin, LOW);
    Serial.print("== pos");
    Serial.println(pos);
  }
  
  last_pos = pos;
} 
