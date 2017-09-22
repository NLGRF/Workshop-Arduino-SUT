// Traffic light module
// D11 -> Red LED, D10 -> Yellow LED, D9 -> Green LED
#define RLED  11
#define YLED  10
#define GLED  9

#define RDLY  1
#define YDLY  1
#define GDLY  1

typedef struct {
  tByte   state;
  tByte   rTime;
  tByte   yTime;
  tByte   gTime;
  tByte   cnt;
} tTLight;

tTLight  m_TLight;

//- State Machine ----------------------------------

tByte fTLightState100(tTLight *m) {

  digitalWrite(GLED,HIGH);
  digitalWrite(RLED,LOW);
  if (m->cnt==m->rTime-1) {
    m->cnt=0;
    m->state=101;
  } else m->cnt++;

  return 0;
} 

tByte fTLightState101(tTLight *m) {

  digitalWrite(RLED,HIGH);
  digitalWrite(YLED,LOW);
  if (m->cnt==m->yTime-1) {
    m->cnt=0;
    m->state=102;
  } else m->cnt++;    
  return 0;
}

tByte fTLightState102(tTLight *m) {

  digitalWrite(YLED,HIGH);
  digitalWrite(GLED,LOW);
  if (m->cnt==m->gTime-1) {
    m->cnt=0;
    m->state=100;
  } else m->cnt++;      
  return 0;
}

tByte fTLightEntry(tTLight *m) {

  if (schZone) { // running in normal scheduling
    
  } else {       // running in timer scheduling
    switch (m->state) {
      case 100 : fTLightState100(m); break;
      case 101 : fTLightState101(m); break;
      case 102 : fTLightState102(m); break;    
      default : break;
    }
  }
  return 0;
}

//--------------------------------------------------

tByte fTLightOpen(void) {

  //- Set 3 outputs
  pinMode(RLED,OUTPUT);
  pinMode(YLED,OUTPUT);
  pinMode(GLED,OUTPUT);
  //- Turn off all LEDs
  digitalWrite(RLED,LOW);
  digitalWrite(YLED,HIGH);
  digitalWrite(GLED,HIGH);
  //- Set delay times
  m_TLight.rTime=RDLY;
  m_TLight.yTime=YDLY;
  m_TLight.gTime=GDLY;
  m_TLight.cnt=0;
  //-------------------------
  m_TLight.state=100;

  return 0;
}

void fTLightRun(void) {

  fTLightEntry(&m_TLight);
}
