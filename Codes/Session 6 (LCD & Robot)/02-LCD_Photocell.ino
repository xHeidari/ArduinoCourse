#include <LiquidCrystal.h>

// LCD pin setup
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Photocell pin
int photocellPin = A0;
int photocellReading;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // 16 columns, 2 rows
  lcd.print("Light Level:");
}

void loop() {
  photocellReading = analogRead(photocellPin);
  Serial.print("Analog reading = ");
  Serial.print(photocellReading);

  // Map light value to bar width (0 to 16)
  int barLength = map(photocellReading, 0, 1023, 0, 16);
  
  // Create bar string
  String bar = "";
  for (int i = 0; i < barLength; i++) {
    bar += byte(255); // Full block character
  }

  // Fill remaining space with blanks
  while (bar.length() < 16) {
    bar += " ";
  }

  // Display bar on first row
  lcd.setCursor(0, 0);
  lcd.print(bar);

  // Display value and category on second row
  lcd.setCursor(0, 1);
  lcd.print("Val:");
  lcd.print(photocellReading);
  lcd.print(" ");

  if (photocellReading < 10) {
    lcd.print("Dark      ");
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    lcd.print("Dim       ");
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    lcd.print("Light     ");
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    lcd.print("Bright    ");
    Serial.println(" - Bright");
  } else {
    lcd.print("VeryBright");
    Serial.println(" - Very bright");
  }

  delay(1000);
}
