#include <Arduino.h>
#include <Servo.h>
#include <NeoSWSerial.h>

// Bluetooth serial pins (as in your original code)
NeoSWSerial bluetooth(A4, A5);

Servo MG995_Servo1;
Servo MG995_Servo2;
Servo MG995_Servo3;

char message[15];
uint8_t index = 0;

uint8_t v1 = 0, last_v1 = 0;
uint8_t v2 = 180, last_v2 = 180;
uint8_t v3 = 0, last_v3 = 0;

unsigned long time_v1 = 0, time_v2 = 0, time_v3 = 0;
char speed = 7;

uint8_t mode = 3;  // default to bluetooth mode
uint8_t last_mode = 3;

void set_servo()
{
  if (v1 != last_v1)
  {
    if (millis() - time_v1 > speed)
    {
      time_v1 = millis();
      if (last_v1 < v1)
        MG995_Servo1.write(++last_v1);
      else if (last_v1 > v1)
        MG995_Servo1.write(--last_v1);
    }
  }
  else
    last_v1 = MG995_Servo1.read();

  if (v2 != last_v2)
  {
    if (millis() - time_v2 > speed)
    {
      time_v2 = millis();
      if (last_v2 < v2)
        MG995_Servo2.write(++last_v2);
      else if (last_v2 > v2)
        MG995_Servo2.write(--last_v2);
    }
  }
  else
    last_v2 = MG995_Servo2.read();

  if (v3 != last_v3)
  {
    if (millis() - time_v3 > speed)
    {
      time_v3 = millis();
      if (last_v3 < v3)
        MG995_Servo3.write(++last_v3);
      else if (last_v3 > v3)
        MG995_Servo3.write(--last_v3);
    }
  }
  else
    last_v3 = MG995_Servo3.read();
}

void setup()
{
  Serial.begin(115200);
  bluetooth.begin(9600);

  MG995_Servo1.attach(3);
  MG995_Servo2.attach(5);
  MG995_Servo3.attach(6);

  Serial.println("Bluetooth servo control mode started");
}

void loop()
{
  set_servo();

  if (mode == 3)  // bluetooth control mode
  {
    while (bluetooth.available() > 0)
    {
      char inByte = bluetooth.read();
      message[index] = inByte;

      if (inByte == '\n')
      {
        message[index] = 0;  // null terminate

        // Parse command: last 4 chars before '\n' are "idxxx"
        // Example command: "id100\n" => id=1, set=100
        if (index >= 4)
        {
          uint8_t id = message[index - 4] - '0';
          uint16_t set = (message[index - 3] - '0') * 100 + (message[index - 2] - '0') * 10 + (message[index - 1] - '0');

          if (id == 1)
            v1 = set;
          else if (id == 2)
            v2 = 180 - set;  // as in your original code
          else if (id == 3)
            v3 = set;
          else if (id == 4 && set == 188)
          {
            v1 = 0;
            v2 = 180;
            v3 = 0;
          }
        }
        index = 0;  // reset for next message

        // Flush any remaining chars in buffer
        while (bluetooth.available() > 0)
          bluetooth.read();
      }
      else
      {
        index++;
        if (index >= sizeof(message) - 1)
          index = 0;  // avoid overflow
      }
    }
  }
}
