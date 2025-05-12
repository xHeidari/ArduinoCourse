const int thermistorPin = A0;
const float seriesResistor = 5000.0; // known resistor in ohms
const float nominalResistance = 5000.0; // 5k ohms at 25°C
const float nominalTemperature = 25.0;  // in Celsius
const float bCoefficient = 3950.0; // typical B-value
const int adcMax = 1023;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(thermistorPin);
  float voltage = adcValue / (float)adcMax;
  float resistance = seriesResistor * (1.0 / voltage - 1.0);

  // Steinhart-Hart Equation
  float steinhart;
  steinhart = resistance / nominalResistance;
  steinhart = log(steinhart);
  steinhart /= bCoefficient;
  steinhart += 1.0 / (nominalTemperature + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;


  Serial.println(steinhart);

  delay(1000);
}
