// I2C-LCD Example
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  // initialize the LCD
  lcd.begin();

  // Turn on/off the blacklight
  //lcd.noBacklight();
  lcd.backlight();

  // Cursor blink/no blink
  lcd.blink();
  //lcd.noBlink();
 
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  lcd.setCursor(4,1);
  lcd.print(123.56,1);
}

void loop()
{

}


