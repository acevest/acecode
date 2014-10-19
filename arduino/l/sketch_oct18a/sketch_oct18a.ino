const int LedPins[] = {8, 9, 10, 11, 12};
const int cnt = 5;
void setup() {
  int i;
  for(i=0; i<cnt; ++i)
  {
    pinMode(LedPins[i], OUTPUT); 
  }
}

static int curt = 0;

void loop() {
  int i;
  for(i=0; i<cnt; ++i)
  {
    int ledPin = LedPins[i];
    
    if(i == curt)
    {
      digitalWrite(ledPin, LOW);
    }
    else
    {
      digitalWrite(ledPin, HIGH);
    }
  }
  
  curt = ++curt % cnt;
  delay(200);
}

