//using IRF520N MOSFET Arduino pin connected to Gate
void setup()
{
  pinMode(3, OUTPUT);
  pinMode(8,INPUT_PULLUP);
}

void loop()
{
  if(!digitalRead(8)){
    
  digitalWrite(3, HIGH);
  }
  else{
     digitalWrite(3, LOW);
  }
  
}
