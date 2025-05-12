const int pingPin = 5; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

long duration;


void setup() {
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(pingPin, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  Serial.print(duration / 29 / 2);
  Serial.println(" cm");
  delay(300);
  }

