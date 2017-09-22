// TimerOne Example2
#include "TimerOne.h"

#define LED2  9
boolean tog = false;

void setup() {

  pinMode(LED2,OUTPUT);
  digitalWrite(LED2,HIGH);
  Timer1.initialize(2000000);         // set timer=2000000 us = 2s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
}

void loop() {

}

void fTimerIsr() {
  tog = !tog;
  digitalWrite(LED2,tog);
  if (tog) Timer1.initialize(500000); else Timer1.initialize(2000000);
}


