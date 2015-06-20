#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define TEMP_WIRE_BUS 2

OneWire TempWire(TEMP_WIRE_BUS);
DallasTemperature TempSensors(&TempWire);


SoftwareSerial BTSerial(10, 11); // RX | TX


DHT dht;

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
  
  TempSensors.begin();//TEMP_WIRE_BUS);
  TempSensors.setResolution(12);
  
  dht.setup(4, DHT::DHT11);
}

char *itos(int n)
{
    static char buf[16];
    sprintf(buf, "%d", n);
    return buf;
}

char *ftos(float f)
{
  static char buf[32];
  sprintf(buf, "%.2f", f);
  return buf; 
}

void loop() {
  cnt ++;
#if 0
  int bd = digitalRead(7);
  
    Serial.print(">");
    Serial.print(bd);
    Serial.println("<");
  delay(100);
  return; 
#endif
  
  TempSensors.requestTemperatures();
  float tv = TempSensors.getTempCByIndex(0);

  //delay(dht.getMinimumSamplingPeriod());
  float hv = dht.getHumidity();  // Humidity

  int lv = analogRead(0);  // Light
 
  //int tv = analogRead(1);  // Temperature
  
  int hb = analogRead(2);  // Human Body 
  
  //int hv = analogRead(3);  // humidity
  
  
  if(cnt % 1 == 0)
  {
    Serial.print(">");
    Serial.print(lv);
    Serial.print(":");
    Serial.print(tv);
    Serial.print(":");
    Serial.print(hb);
    Serial.print(":");
    Serial.print(hv);
    Serial.print(" Humidity:");
    Serial.print(dht.getHumidity());
    Serial.print(" Temp:");
    Serial.print(dht.getTemperature());
    Serial.println(" ");

    
#if 1
    BTSerial.print(">");
    BTSerial.print(lv, DEC);
    BTSerial.print(":");
    BTSerial.print(tv, DEC);
    BTSerial.print(":");
    BTSerial.print(hv, DEC);
    BTSerial.print(":");
    BTSerial.print(hb, DEC);
    BTSerial.println("<");
#endif

    
#if 0
    BTSerial.write(">");
    BTSerial.write(itos(lv));
    BTSerial.write(":");
    BTSerial.write(ftos(tv));
    BTSerial.write(":");
    BTSerial.write(itos(hb));
    BTSerial.write(":");
    BTSerial.write(itos(hv));
    BTSerial.write("\n");
#endif

  }
}

