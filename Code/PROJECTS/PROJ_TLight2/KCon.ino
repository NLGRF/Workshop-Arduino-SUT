/*
  SW1 : Select a LED for setting its delay time (round robin) or 
        End of setting
  SW2 : Increase delay of the selected LED (round robin) or 
        Reset all LEDs' delay times.
*/
typedef struct {
  tByte   state;
  tByte   tabEn;
} tKCon;

tKCon  m_KCon;

//- State Machines ----------------------------------

tByte fKConState0(tKCon *m) {
  tByte   k;

  if (fKeyHit()) {
    k=fKeyGet();
    switch (k) {
      case 0x00: m->tabEn=1; fTLightTab(); break;
      case 0x01: 
        if (m->tabEn) {fTLightInc(); m->state=1;} else fTLightReset(); 
        break;
    }
  }
  return 0;
} 

tByte fKConState1(tKCon *m) {
  tByte   k;

  if (fKeyHit()) {
    k=fKeyGet();
    switch (k) {
      case 0x00: fTLightDone(); m->tabEn=0; m->state=0; break;
      case 0x01: fTLightInc(); break;
    }
  }  
  return 0;
}

tByte fKConEntry(tKCon *m) {

  switch (m->state) {
    case 0 : fKConState0(m); break;
    case 1 : fKConState1(m); break;
    default : break;
  }

  return 0;
}

//--------------------------------------------------

tByte fKConOpen(void) {

  m_KCon.tabEn = 0;
  //-------------------------
  m_KCon.state=0;

  return 0;
}

void fKConRun(void) {

  fKConEntry(&m_KCon);
}
