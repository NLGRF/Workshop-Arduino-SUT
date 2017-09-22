#include "MPublic.h"
#include <TimerOne.h>
#include "Test.h"
#include "Key.h"
#include "KCon.h"
#include "Com.h"
#include "Cmd.h"

void fTimerIsr(void);

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);         // set timer=1000000 us = 1s 
  Timer1.attachInterrupt(fTimerIsr);  // attach ISR here 
  //------------

  //fTestOpen();
  fKeyOpen();
  fKConOpen();
  fComOpen();
  fCmdOpen();
}

void loop() {

  schZone = true;
  //fTestRun();
  fKeyRun();
  fKConRun();
  fComRun();
  fCmdRun();
}

void fTimerIsr(void) {

  schZone = false;
  //fTestRun();
}



