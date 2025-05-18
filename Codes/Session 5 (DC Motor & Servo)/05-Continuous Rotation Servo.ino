/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(50);
  //myservo.write(0);    // Full speed reverse (maximum CCW)
  //myservo.write(30);   // Fast reverse (CCW)
  //myservo.write(50);   // Medium reverse (CCW)
  //myservo.write(70);   // Slow reverse (CCW)
  //myservo.write(90);   // Stop (no rotation)
  //myservo.write(100);  // Slow forward (CW)
  //myservo.write(120);  // Medium forward (CW)
  //myservo.write(150);  // Fast forward (CW)
  //myservo.write(180);  // Full speed forward (maximum CW)
}

void loop() {

}
