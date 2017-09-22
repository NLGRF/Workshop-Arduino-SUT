typedef struct {
  tByte   state;
  tWord   mspeed;
} tSpeed;

tSpeed  m_Speed;

//- State Machines ----------------------------------

tByte fSpeedState0(tSpeed *m) {

  m->state=100;
  return 0;
} 

tByte fSpeedState1(tSpeed *m) {

    
  return 0;
}

//---------------------------------

tByte fSpeedState100(tSpeed *m) {

  m->mspeed=fContrCntRead();
  m->mspeed=m->mspeed/2;
  Serial.print("Speed = ");
  Serial.print(m->mspeed);
  Serial.println(" rps");

  fContrCntSpeed();
  m->state=0;
  return 0;
} 

tByte fSpeedState101(tSpeed *m) {

    
  return 0;
}

tByte fSpeedEntry(tSpeed *m) {

  if (schZone) { // running in normal scheduling
    switch (m->state) {
      case 0 : fSpeedState0(m); break;
      case 1 : fSpeedState1(m); break;
      default : break;
    }
  } else {       // running in timer scheduling 
    switch (m->state) {
      case 100 : fSpeedState100(m); break;
      case 101 : fSpeedState101(m); break;
      default : break;  
    }  
  }
  return 0;
}

//--------------------------------------------------

tByte fSpeedOpen(void) {

  
  //-------------------------
  m_Speed.state=100;

  return 0;
}

void fSpeedRun(void) {

  fSpeedEntry(&m_Speed);
}
