// Blink a LED N times by pressing a switch

#define LED2   9
#define SW     3
#define N      5

boolean tog = false; 
byte i = 0;

void setup() {
  pinMode(LED2,OUTPUT);
  pinMode(SW,INPUT);
}

void fBlink() {
  digitalWrite(LED2,LOW);
  delay(500);
  digitalWrite(LED2,HIGH);
  delay(500);
}

void loop() {

  if (digitalRead(SW) == LOW) {
    tog = true;
  }
  if (tog) {
    if (i<N) {
      i++;
      fBlink();
    } else {i=0;tog=false;}
  }
}


