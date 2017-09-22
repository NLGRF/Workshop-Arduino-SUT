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
      case 0x00:  break;
      case 0x01:  break;
    }
  }
  return 0;
} 

tByte fKConState1(tKCon *m) {

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
