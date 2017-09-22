#include "MPublic.h"
#include <TimerOne.h>
#include "Test.h"
#include "TLight.h"
#include "Key.h"
#include "KCon.h"

void fTimerIsr(void);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);         // set timer=1000000 us = 1s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  //fTestOpen();
  fTLightOpen();
  fKeyOpen();
  fKConOpen();
}

void loop() {

  schZone = true;
  //fTestRun();
  fTLightRun();
  fKeyRun();
  fKConRun();
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
  fTLightRun();
}



