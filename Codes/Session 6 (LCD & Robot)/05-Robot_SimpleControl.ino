#include <Servo.h>

// Create Servo objects
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

// Set initial positions
int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;

void setup() {
  // Attach servos to pins
  baseServo.attach(8);
  shoulderServo.attach(9);
  elbowServo.attach(10);

  // Set initial positions
  baseServo.write(baseAngle);
  shoulderServo.write(shoulderAngle);
  elbowServo.write(elbowAngle);

  // Begin serial communication
  Serial.begin(9600);
  Serial.println("Robotic arm controller ready.");
  Serial.println("Enter angles as: B90 S90 E90");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Parse base
    int bIndex = input.indexOf('B');
    if (bIndex != -1) {
      baseAngle = input.substring(bIndex + 1).toInt();
      baseAngle = constrain(baseAngle, 0, 180);
      baseServo.write(baseAngle);
    }

    // Parse shoulder
    int sIndex = input.indexOf('S');
    if (sIndex != -1) {
      shoulderAngle = input.substring(sIndex + 1).toInt();
      shoulderAngle = constrain(shoulderAngle, 0, 180);
      shoulderServo.write(shoulderAngle);
    }

    // Parse elbow
    int eIndex = input.indexOf('E');
    if (eIndex != -1) {
      elbowAngle = input.substring(eIndex + 1).toInt();
      elbowAngle = constrain(elbowAngle, 0, 180);
      elbowServo.write(elbowAngle);
    }

    Serial.print("Updated angles -> Base: ");
    Serial.print(baseAngle);
    Serial.print(" Shoulder: ");
    Serial.print(shoulderAngle);
    Serial.print(" Elbow: ");
    Serial.println(elbowAngle);
  }
}
