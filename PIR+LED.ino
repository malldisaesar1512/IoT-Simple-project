// C++ code
//
int PIR = 4;
int LED = 3;
int statusPin = 0;

void setup()
{
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  statusPin = digitalRead(PIR);
  if (statusPin == HIGH){
  	digitalWrite(LED, HIGH);
  }else{
  	digitalWrite(LED, LOW);
  }
}
