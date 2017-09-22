#include "MPublic.h"
#include <TimerOne.h>
#include "Test.h"
#include "Key.h"
#include "KCon.h"
#include "USonic.h"

void fTimerIsr(void);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);         // set timer=500000 us = 0.5s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  //fTestOpen();
  fKeyOpen();
  fKConOpen();
  fUSonicOpen();
}

void loop() {

  schZone = true;
  //fTestRun();
  fKeyRun();
  fKConRun();
  fUSonicRun();
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
}



