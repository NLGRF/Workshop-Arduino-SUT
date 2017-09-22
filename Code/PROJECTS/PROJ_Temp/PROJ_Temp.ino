#include "MPublic.h"
#include <TimerOne.h>
#include "Test.h"

void fTimerIsr(void);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);         // set timer=1000000 us = 1s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  fTestOpen();
 
}

void loop() {

  schZone = true;
  fTestRun();
}

void fTimerIsr(void) {

  schZone = false;
  fTestRun();
}



