typedef struct {
  tByte   state;

  tByte   tog;
  tWord   cnt;
  tByte   iflag; 
} tContr;

tContr  m_Contr;

//- Local functions --------------------------------

void fContrIntr(void) {
  m_Contr.iflag=1;
}

//- State Machines ----------------------------------

tByte fContrState0(tContr *m) {


  if (m->iflag) {
    if (digitalRead(EIT)==HIGH) {
      m->cnt++;
      m->iflag=0;
    }    
  }
  
 
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

void fContrCntSpeed(void) {
  m_Contr.cnt=0;
}

tWord fContrCntRead(void) {
  return m_Contr.cnt;
}

void fContrSwTog(void) {
  if (m_Contr.tog) {    // Turn on motor
    m_Contr.tog=0;    
    m_Contr.state=0;
  } else {              // Turn off motor
    m_Contr.tog=1;
    digitalWrite(MOTA,LOW);
    digitalWrite(MOTB,LOW);      
    m_Contr.state=bNull;
  }

}

//--------------------------------------------------

tByte fContrOpen(void) {
    tWord     v;

  m_Contr.tog=1;
  pinMode(MOTA, OUTPUT);   // sets the pin as output
  pinMode(MOTB, OUTPUT);   // sets the pin as output
  digitalWrite(MOTA,LOW);
  digitalWrite(MOTB,LOW);  

  m_Contr.cnt=0;
  m_Contr.iflag=0;
  pinMode(EIT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(EIT), fContrIntr, FALLING);    

  v = analogRead(POT);          // Read the input pin
  analogWrite(MOTB, v/4);   
  //-------------------------
  m_Contr.state=0;

  return 0;
}

void fContrRun(void) {

  fContrEntry(&m_Contr);
}
