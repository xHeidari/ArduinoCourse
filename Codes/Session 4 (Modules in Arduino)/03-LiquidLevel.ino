int water_ain=A0;
float ad_value=0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  ad_value=analogRead(water_ain);
  if(ad_value>200)
  {
    Serial.println("High water level");
  }
  else
  {
    Serial.println("Low water level");
  }
  delay(500);
  ad_value = ad_value*5/1024;
  Serial.println(ad_value);
}
