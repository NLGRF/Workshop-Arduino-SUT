// TimerOne Example
#include "TimerOne.h"

#define LED2  9
boolean tog = false;

void setup() {

  pinMode(LED2,OUTPUT);
  digitalWrite(LED2,HIGH);
  Timer1.initialize(1000000);         // set timer=1000000 us = 1s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
}

void loop() {

}

void fTimerIsr() {
  tog = !tog;
  digitalWrite(LED2,tog);
}


