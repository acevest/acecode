const int ledPin = 12;
int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  cnt ++;
  
  int lv = analogRead(0);  // Light
 
  int tv = analogRead(1);  // Temperature
  
  int bd = analogRead(2);  // Human Body 
  
  delay(100);
  
  float temperature;
  float resistance = (float)(1023-tv)*10000/tv;
  temperature = 1/(log(resistance/10000)/3975+1/298.15) - 273.15;
  if(cnt % 10 == 0)
  {
    Serial.print("Light Sensor Value: ");
    Serial.println(lv);
  
    Serial.print("Temperature Sensor Value: ");
    Serial.println(tv); 
    
    Serial.print("Body: ");
    Serial.println(bd);
    
    Serial.print(">");
    Serial.print(lv);
    Serial.print(":");
    Serial.print(temperature);
    Serial.print(":");
    Serial.print(bd);
    Serial.println(" ");
  }
  
  if(lv < 400)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
  
}

