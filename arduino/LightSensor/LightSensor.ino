const int ledPin = 12;
int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  cnt ++;
  
  int lv = analogRead(0);  // Light
 
  delay(1);
  
  if(cnt % 10 == 0)
  {
    Serial.print("Light Sensor Value: ");
    Serial.println(lv);
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
