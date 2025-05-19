#include <Arduino.h>
#include <Servo.h>

#define ASK_PIN 2

Servo MG995_Servo1;
Servo MG995_Servo2;
Servo MG995_Servo3;

uint8_t v1 = 0, v2 = 180, v3 = 0;
uint8_t last_v1 = 0, last_v2 = 180, last_v3 = 0;
unsigned long time_v1, time_v2, time_v3;
char speed = 5;

volatile uint32_t receive_code = 0;
volatile bool receive_flag = false;

const uint32_t bit_shift[25] = {
  0x000000, 0x000001, 0x000002, 0x000004, 0x000008, 0x000010, 0x000020,
  0x000040, 0x000080, 0x000100, 0x000200, 0x000400, 0x000800, 0x001000,
  0x002000, 0x004000, 0x008000, 0x010000, 0x020000, 0x040000, 0x080000,
  0x100000, 0x200000, 0x400000, 0x800000
};

void ASK() {
  static unsigned long T_High = 0, T_Low = 0, last_T_Low = 0, last_T_High = 0;
  static uint32_t new_receive_code = 0;
  static uint8_t bit_index = 24;
  static bool start_bit = false;

  if (digitalRead(ASK_PIN)) {
    T_Low = micros() - last_T_Low;
    last_T_High = micros();

    if (((T_High * 25) < T_Low) && ((T_High * 35) > T_Low)) {
      bit_index = 24;
      start_bit = true;
      new_receive_code = 0;
    } 
    else if (start_bit) {
      if (bit_index > 0) {
        if (((T_Low * 5) > T_High) && (T_High > T_Low)) { // high bit
          new_receive_code |= bit_shift[bit_index--];
        } 
        else if (((T_High * 5) > T_Low) && (T_High < T_Low)) { // low bit
          bit_index--;
        } 
        else {
          bit_index = 24;
          start_bit = false;
          new_receive_code = 0;
        }
      }

      if (bit_index == 0 && start_bit) {
        start_bit = false;
        receive_code = new_receive_code;
        receive_flag = true;
      }
    }
  } 
  else {
    T_High = micros() - last_T_High;
    last_T_Low = micros();
  }
}

void set_servo() {
  if (v1 != last_v1) {
    if (millis() - time_v1 > speed) {
      time_v1 = millis();
      if (last_v1 < v1) last_v1++;
      else if (last_v1 > v1) last_v1--;
      MG995_Servo1.write(last_v1);
    }
  }
  if (v2 != last_v2) {
    if (millis() - time_v2 > speed) {
      time_v2 = millis();
      if (last_v2 < v2) last_v2++;
      else if (last_v2 > v2) last_v2--;
      MG995_Servo2.write(last_v2);
    }
  }
  if (v3 != last_v3) {
    if (millis() - time_v3 > speed) {
      time_v3 = millis();
      if (last_v3 < v3) last_v3++;
      else if (last_v3 > v3) last_v3--;
      MG995_Servo3.write(last_v3);
    }
  }
}

void setup() {
  Serial.begin(115200);

  MG995_Servo1.attach(3);
  MG995_Servo2.attach(5);
  MG995_Servo3.attach(6);

  pinMode(ASK_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(ASK_PIN), ASK, CHANGE);

  Serial.println("Remote control servo test started");
}

void loop() {
  set_servo();

  if (receive_flag) {
    receive_flag = false;
    Serial.print("Received code: 0x");
    Serial.println(receive_code, HEX);

    // Map received codes to servo control commands
    if (receive_code == 0x27F121) {
      if (v1 < 177) v1 += 4;
    }
    else if (receive_code == 0x27F12E) {
      if (v1 > 3) v1 -= 4;
    }
    else if (receive_code == 0x27F122) {
      if (v2 > 3) v2 -= 4;
    }
    else if (receive_code == 0x27F12C) {
      if (v2 < 177) v2 += 4;
    }
    else if (receive_code == 0x27F126) {
      if (v3 < 177) v3 += 4;
    }
    else if (receive_code == 0x27F12A) {
      if (v3 > 3) v3 -= 4;
    }
    else if (receive_code == 0x27F128) {
      v1 = 0;
      v2 = 180;
      v3 = 0;
    }
    else if (receive_code == 0x27F124) {
      v1 = 0;
      v2 = 120;
      v3 = 0;
    }
  }
}
