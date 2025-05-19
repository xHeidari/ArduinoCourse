#include <Servo.h>

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

void setup() {
  baseServo.attach(8);
  shoulderServo.attach(9);
  elbowServo.attach(10);

  // Set initial positions
  baseServo.write(50);         // Start at base 50°
  shoulderServo.write(90);     // Neutral shoulder
  elbowServo.write(100);       // Start elbow low

  Serial.begin(9600);
  Serial.println("Send 'HI' to wave hello!");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input == "HI") {
      sayHi();
    }
  }
}

void sayHi() {
  // Slowly rotate base from 50° to 90°
  for (int angle = 50; angle <= 90; angle++) {
    baseServo.write(angle);
    delay(20);  // Smooth rotation
  }

  delay(300);  // Pause

  // Do a waving motion with the elbow
  for (int i = 0; i < 3; i++) {
    elbowServo.write(200);  // Up
    delay(300);
    elbowServo.write(150);  // Down
    delay(300);
  }

  // Return to rest position
  elbowServo.write(100);
  baseServo.write(50);
}

