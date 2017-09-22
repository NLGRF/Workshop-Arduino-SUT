// DS1302:  CE/RST pin  -> Arduino Digital 8
//          DAT pin     -> Arduino Digital 7
//          CLK pin     -> Arduino Digital 6
#include <DS1302.h>

// Init the DS1302--> DS1302 rtc([CE/RST], [DAT], [CLK]);
DS1302 rtc(8, 7, 6);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  Serial.begin(9600);         // Setup Serial connection

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(SATURDAY);       // Set Day-of-Week to FRIDAY
  rtc.setTime(10, 50, 0);     // Set the time (24hr format)
  rtc.setDate(25, 2, 2017);   // Set the date (d/m/y)
}

void loop()
{
  // Get Day-of-Week --------------------
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  // Get date ---------------------------
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Get time ---------------------------
  Serial.println(rtc.getTimeStr());
  // Wait one second before repeating :)
  delay (1000);
}

