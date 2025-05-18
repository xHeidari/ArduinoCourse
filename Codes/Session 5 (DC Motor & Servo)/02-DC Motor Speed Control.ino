//using IRF520N MOSFET Arduino pin connected to Gate
void setup() {
	pinMode(3,OUTPUT);
}

void loop() {
  int PotValue = analogRead(A5);
  int pwmValue = map(PotValue,0,1023,0,255);
  analogWrite(3,pwmValue);
  delay(20);
}
