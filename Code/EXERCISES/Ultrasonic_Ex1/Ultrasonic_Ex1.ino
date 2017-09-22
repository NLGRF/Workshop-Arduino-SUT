//Use with ultrasonic module HC-SR04
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Ultrasonic.h"

#define US_TRIG 12
#define US_ECHO 13

//12 (output) --> HC-SR04's TRIG
//13 (input) <-- HC-SR04's ECHO
Ultrasonic ultrasonic(US_TRIG,US_ECHO);
LiquidCrystal_I2C lcd(0x3F, 16, 2);     // addr, 16x2
unsigned int dist = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}

void loop()
{

  dist = ultrasonic.Ranging(CM);
  Serial.print(dist);  Serial.println("cm");

  lcd.clear();
  lcd.setCursor(0,0);  lcd.print("Distance:");
  lcd.setCursor(10,0); lcd.print(dist);
  lcd.setCursor(14,0); lcd.print("cm");
  delay(100);
}


