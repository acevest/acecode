int cnt = 0;
const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
}

void loop() {
  cnt ++;
  
  int lv = analogRead(0);  // Light
 
  int tv = analogRead(1);  // Temperature
  
  int hb = analogRead(2);  // Human Body 
  
  if(hb < 100)
  {
    hb = 0;
  }
  
  digitalWrite(ledPin, hb > 0 ? HIGH : LOW);

  delay(100);
  
  if(cnt % 10 == 0)
  {
    float temperature;
    float resistance = (float)(1023-tv)*10000/tv;
    temperature = 1.00000/(log(resistance/10000)/3975+1/298.15) - 273.15;

    Serial.print("Light Sensor Value: ");
    Serial.println(lv);
  
    Serial.print("Temperature Sensor Value: ");
    Serial.println(tv); 
    
    Serial.print("Body: ");
    Serial.println(hb);
    
    Serial.print(">");
    Serial.print(lv);
    Serial.print(":");
    Serial.print(temperature);
    Serial.print(":");
    Serial.print(hb);
    Serial.println(" ");
  }
}

