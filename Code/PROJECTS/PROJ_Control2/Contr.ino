typedef struct {
  tByte   state;

  tByte   tog;
  tByte   tab;
  tByte   prev_tab;
} tContr;

tContr  m_Contr;

//- Local functions --------------------------------

void fContrSetSpeed(tByte spd) {
  digitalWrite(MOTA,LOW);
  analogWrite(MOTB,spd);
}

//- State Machines ----------------------------------

tByte fContrState0(tContr *m) {

  if (m->tab==m->prev_tab) return 0;
  switch (m->tab) {
    case 0 : fContrSetSpeed(90); break;
    case 1 : fContrSetSpeed(150); break;    
    case 2 : fContrSetSpeed(200); break;
    case 3 : fContrSetSpeed(250); break;
  }
  m->prev_tab=m->tab;

  return 0;
} 

tByte fContrState1(tContr *m) {


    
  return 0;
}

//---------------------------------

tByte fContrState100(tContr *m) {

 
  return 0;
} 

tByte fContrState101(tContr *m) {

    
  return 0;
}

tByte fContrEntry(tContr *m) {

  if (schZone) { // running in normal scheduling
    switch (m->state) {
      case 0 : fContrState0(m); break;
      case 1 : fContrState1(m); break;
      default : break;
    }
  } else {       // running in timer scheduling 
    switch (m->state) {
      case 100 : fContrState100(m); break;
      case 101 : fContrState101(m); break;
      default : break;  
    }  
  }
  return 0;
}

//--------------------------------------------------

void fContrSwTog(void) {
  if (m_Contr.tog) {
    m_Contr.tog=0;
    m_Contr.prev_tab=bNull;
    m_Contr.state=0;
  } else {
    m_Contr.tog=1;
    digitalWrite(MOTA,LOW);
    digitalWrite(MOTB,LOW);    
    m_Contr.state=bNull;
  }
}

void fContrIncTab(void) {
  m_Contr.tab++;
  if (m_Contr.tab==4) m_Contr.tab=0;
}

//--------------------------------------------------

tByte fContrOpen(void) {

  m_Contr.tog=1;
  m_Contr.tab=0;
  m_Contr.prev_tab=bNull;

  pinMode(MOTA, OUTPUT);   // sets the pin as output
  pinMode(MOTB, OUTPUT);   // sets the pin as output
  digitalWrite(MOTA,LOW);
  digitalWrite(MOTB,LOW);  
  //-------------------------
  m_Contr.state=bNull;

  return 0;
}

void fContrRun(void) {

  fContrEntry(&m_Contr);
}
