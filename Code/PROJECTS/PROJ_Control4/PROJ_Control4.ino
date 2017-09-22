#include "MPublic.h"
#include <TimerOne.h>
#include "Test.h"
#include "Key.h"
#include "KCon.h"
#include "Contr.h"
#include "Speed.h"

void fTimerIsr(void);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);         // set timer=1000000 us
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  //fTestOpen();
  fKeyOpen();
  fKConOpen();
  fContrOpen();
  fSpeedOpen();
}

void loop() {

  schZone = true;
  //fTestRun();
  fKeyRun();
  fKConRun();
  fContrRun();
  fSpeedRun();
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
  fSpeedRun();
}



