int fmpin=12;  //设置蜂鸣器数字接口1
void setup()
{
  pinMode(fmpin,OUTPUT);
}

void fm(float f)
{
  float T = (float) ((float)1000000) / f;
  
  int d = (int) (T/2);
  
  int cnt = 1*(int)f;
  
  int i;
  for(i=0; i<cnt; ++i)
  {
    digitalWrite(fmpin,HIGH);   //产生1KHz的脉冲
    delayMicroseconds(d);
    digitalWrite(fmpin,LOW);
    delayMicroseconds(d);
  }
  
  delay(200);
}

void loop()
{
  fm(2560);
  fm(2880);
  fm(3200);
  fm(3413.33);
  fm(3840);
  fm(4266.67);
  fm(4800);
  fm(5120);
  fm(5120);
}
