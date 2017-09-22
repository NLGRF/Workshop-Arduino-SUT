// Blinking a LED N times

#define LED2  9
#define N     5

unsigned char   i=0;
  
void setup() {
  pinMode(LED2,OUTPUT);
}

void loop() {
  if (i<N) {
    digitalWrite(LED2,LOW);
    delay(500);
    digitalWrite(LED2,HIGH);
    delay(500);
    i++;
  }
}


