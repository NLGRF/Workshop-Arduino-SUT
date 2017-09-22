#include "DHT.h"
#define CMD_LEN_MAX   10  // Max length of commands
#define CMD_LEN_FIX   4   // Length of self-defined commands 

//---------------------------------

typedef struct {
  tByte   state;
  char    cmd[CMD_LEN_MAX];  // String storing an instruction
  tByte   cmd_i;         // Index for string cmd
} tCmd;

tCmd  m_cmd;
DHT dht(DHTPIN, DHTTYPE);

//- Functions -------------------------------------

void fCmdHelp(void) {
  Serial.println("");
  Serial.println("** MyLittlePLC -------------------");
  Serial.println("  GETT : Get Temperature");
  Serial.println("  GETH : Get Humidity");
  Serial.println("  RYOF : Turn off Relay");
  Serial.println("  RYON : Turn on Relay");
  Serial.println("----------------------------------");
}

tByte fCmdStrLen(char *s) {
  tByte   i;

  for (i=0;i<CMD_LEN_MAX;i++) if (s[i]=='\0') return i;
  return bNull;
}

tByte fCmdApp(tCmd *m,char c) {

  if (m->cmd_i>=CMD_LEN_MAX-1) return bNull;    // Too long
  m->cmd[m->cmd_i]=c;
  m->cmd_i++;
  return 0;
}

tByte fCmdCmp(tCmd *m,char *s) {
  tByte   i,len,l;

  if (m->cmd_i-1>CMD_LEN_FIX) return 0;
  l=fCmdStrLen(s);if (l==bNull) return 0;
  if (m->cmd_i-1>l) len=m->cmd_i-1; else len=l; 
  for (i=0;i<len;i++) {
    if (m->cmd[i]!=s[i]) return 0;
  }
  return 1;
}

void fCmdGetT(void) {
  float t = dht.readTemperature();
  Serial.print("Temp = ");
  Serial.println(t);
}

void fCmdGetH(void) {
  float h = dht.readHumidity();
  Serial.print("Humid = ");
  Serial.println(h);
}

void fCmdRyOn(void) {
  digitalWrite(RELAY,HIGH);
  Serial.println("Relay On");
}

void fCmdRyOf(void) {
  digitalWrite(RELAY,LOW);
  Serial.println("Relay Off");
}

//- State Machine ----------------------------------

tByte fCmdState0(tCmd *m) {
  char   c;

  if (!fComIsBufEmpty()) {
    c=(char)fComBufOut();
    if (isAlpha(c)) fCmdApp(m,c);
    if (c==0x0D) {
      fCmdApp(m,'\0');
      m->state=1;         // Check command
    }
  }
  return 0;
} 

tByte fCmdState1(tCmd *m) {

  if (fCmdCmp(m,"GETT")) {fCmdGetT();} else
  if (fCmdCmp(m,"GETH")) {fCmdGetH();} else  
  if (fCmdCmp(m,"RYON")) {fCmdRyOn();} else
  if (fCmdCmp(m,"RYOF")) {fCmdRyOf();} else
  if (fCmdCmp(m,"H")) {fCmdHelp();}
  else {Serial.println("Invalid command, man!");}

  m->cmd_i=0;
  m->state=0;         
  return 0;
}

tByte fCmdEntry(tCmd *m) {

  switch (m->state) {
    case 0 : fCmdState0(m); break;
    case 1 : fCmdState1(m); break;
    default : break;
  }
  return 0;
}

//--------------------------------------------------

tByte fCmdOpen(void) {

  pinMode(RELAY,OUTPUT);
  dht.begin();
  //-------------------------
  fCmdHelp();
  fCmdRyOf();

  m_cmd.cmd_i=0;
  //-------------------------
  m_cmd.state=0;

  return 0;
}

void fCmdRun(void) {

  fCmdEntry(&m_cmd);
}
