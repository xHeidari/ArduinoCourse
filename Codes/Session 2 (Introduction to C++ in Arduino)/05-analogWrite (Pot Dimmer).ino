void setup() {
	pinMode(3,OUTPUT);
}

void loop() {
  int PotValue = analogRead(A0);
  int pwmValue = map(PotValue,0,1023,0,255);
  analogWrite(3,pwmValue);
  delay(20);
}
