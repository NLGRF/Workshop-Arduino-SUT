typedef struct {
  tByte   state;
  tByte   spd;    // Motor speed
} tContr;

tContr  m_Contr;

//- Local functions --------------------------------



//- State Machines ----------------------------------

tByte fContrState0(tContr *m) {


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

void fContrSpeed1(void) {
  digitalWrite(MOTA,LOW);
  analogWrite(MOTB,60);    
}

void fContrSpeed2(void) {
  digitalWrite(MOTA,LOW);
  analogWrite(MOTB,100);    
}

//--------------------------------------------------

tByte fContrOpen(void) {

 
  pinMode(MOTA, OUTPUT);   // sets the pin as output
  pinMode(MOTB, OUTPUT);   // sets the pin as output
  digitalWrite(MOTA,LOW);
  digitalWrite(MOTB,LOW);  
  //-------------------------
  m_Contr.state=0;

  return 0;
}

void fContrRun(void) {

  fContrEntry(&m_Contr);
}
