#include <PID_v1.h>

typedef struct {
  tByte   state;
  tWord   mspeed;
} tSpeed;

tSpeed  m_Speed;

double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
//double Kp=2, Ki=5, Kd=1;
double Kp=0.9, Ki=0.2, Kd=0.2;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

//- State Machines ----------------------------------

tByte fSpeedState0(tSpeed *m) {

  Input=m->mspeed;
  myPID.Compute();
  analogWrite(MOTB, Output); 

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

  Setpoint = 60;
  myPID.SetMode(AUTOMATIC);        //turn the PID on
  fContrCntSpeed();
  //-------------------------
  m_Speed.state=100;

  return 0;
}

void fSpeedRun(void) {

  fSpeedEntry(&m_Speed);
}
