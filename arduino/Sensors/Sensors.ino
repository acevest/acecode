#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX


int cnt = 0;
const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // HC-06 current bound rate (default 9600)
  pinMode(ledPin, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

char* itos(int n)
{
    static char buf[16];
    sprintf(buf, "%d", n);
    return buf;
}

void loop() {
  cnt ++;
  
  int lv = analogRead(0);  // Light
 
  int tv = analogRead(1);  // Temperature
  
  int hb = analogRead(2);  // Human Body 
  
  int hv = analogRead(3);  // humidity
  
  if(hb < 100)
  {
    hb = 0;
  }
  
  digitalWrite(ledPin, hb > 0 ? HIGH : LOW);
  
  
  delay(10);
  
  if(cnt % 100 == 0)
  {
    float temperature;
    float resistance = (float)(1023.0-tv)*10000.0/tv;
    temperature = 1.00000/(log(resistance/10000)/3975+1/298.15) - 273.15;

    /*
    Serial.print("Light Sensor Value: ");
    Serial.println(lv);
  
    Serial.print("Temperature Sensor Value: ");
    Serial.println(tv); 
    
    Serial.print("Body: ");
    Serial.println(hb);
    */
    
    Serial.print(">");
    Serial.print(lv);
    Serial.print(":");
    Serial.print(tv);
    Serial.print(":");
    Serial.print(hb);
    Serial.print(":");
    Serial.print(hv);
    Serial.println(" ");
    
    BTSerial.write(">");
    BTSerial.write(itos(lv));
    BTSerial.write(":");
    BTSerial.write(itos(tv));
    BTSerial.write(":");
    BTSerial.write(itos(hb));
    BTSerial.write(":");
    BTSerial.write(itos(hv));
    BTSerial.write("\n");

  }
}

