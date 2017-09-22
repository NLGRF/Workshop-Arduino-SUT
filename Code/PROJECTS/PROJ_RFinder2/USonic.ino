#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Ultrasonic.h"

typedef struct {
  tByte   state;
  tByte   dist;
  tWord   cnt;
} tUSonic;

tUSonic  m_USonic;

Ultrasonic ultrasonic(US_TRIG,US_ECHO);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

//- State Machines ----------------------------------

tByte fUSonicState0(tUSonic *m) {

  m->dist = ultrasonic.Ranging(CM);
  Serial.print(m->dist);  Serial.println(" cm"); 
  lcd.setCursor(10,0); lcd.print("   ");
  lcd.setCursor(10,0); lcd.print(m->dist);  
  m->cnt=0;
  m->state=1;
  return 0;
} 

tByte fUSonicState1(tUSonic *m) {

  m->cnt++;
  if (m->cnt==3000) m->state=0;
    
  return 0;
}

//---------------------------------

tByte fUSonicState100(tUSonic *m) {

 
  return 0;
} 

tByte fUSonicState101(tUSonic *m) {

    
  return 0;
}

tByte fUSonicEntry(tUSonic *m) {

  if (schZone) { // running in normal scheduling
    switch (m->state) {
      case 0 : fUSonicState0(m); break;
      case 1 : fUSonicState1(m); break;
      default : break;
    }
  } else {       // running in timer scheduling 
    switch (m->state) {
      case 100 : fUSonicState100(m); break;
      case 101 : fUSonicState101(m); break;
      default : break;  
    }  
  }
  return 0;
}

//--------------------------------------------------

void fUSonicStart(void) {
  m_USonic.state=0;
}

void fUSonicRead(void) {

  if (m_USonic.state!=bNull) {
    lcd.setCursor(10,0); lcd.print(m_USonic.dist);
    m_USonic.state=bNull;
  }
}

void fUSonicClr(void) {

  lcd.setCursor(10,0); lcd.print("   ");
}

//--------------------------------------------------

tByte fUSonicOpen(void) {

  m_USonic.dist=bNull;
  //-------------------------  
  lcd.begin();
  lcd.backlight();

  Serial.print("   ");  Serial.println(" cm");
  lcd.clear();
  lcd.setCursor(0,0);  lcd.print("Distance:");
  lcd.setCursor(10,0); lcd.print("XXX");
  lcd.setCursor(14,0); lcd.print("cm");  

  //-------------------------
  m_USonic.state=bNull;

  return 0;
}

void fUSonicRun(void) {

  fUSonicEntry(&m_USonic);
}
