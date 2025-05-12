const int hallAnalogPin = A0;  // Connect A0 of Hall sensor to A0 of Arduino
const int hallDigitalPin = 5;  // Connect D0 of Hall sensor to D2 of Arduino

void setup() {
  Serial.begin(9600);
  pinMode(hallDigitalPin, INPUT);
}

void loop() {
  int analogValue = analogRead(hallAnalogPin);
  int digitalState = digitalRead(hallDigitalPin);

  Serial.print("Analog Magnetic Field Value: ");
  Serial.println(analogValue);

  Serial.print("Digital Magnetic State: ");
  if (digitalState == LOW) {
    Serial.println("Magnet Detected!");
  } else {
    Serial.println("No Magnet.");
  }

  delay(500);
}
