const int sensorPin = 5;     // the number of the Sensor pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int sensorState = 0;         // variable for reading the Sensor status

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the Sensor value:
  sensorState = digitalRead(sensorPin);
  Serial.println(sensorState);
}
