const int TrigPin = 2;  // 2
const int EchoPin = 3;  // ~3

float dist;

void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.println("Ultrasonic Sensor:");
}

void loop()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  dist = pulseIn(EchoPin, HIGH) / 58.0;
  
  Serial.print(dist);
  Serial.println("cm");
  delay(100);
}
