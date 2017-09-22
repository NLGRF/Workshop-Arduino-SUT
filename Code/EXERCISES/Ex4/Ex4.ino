// Interrupt service routine via a switch input

#define LED2   9
#define SW     3
#define N      5

boolean tog = false; 

void setup() {
  pinMode(LED2,OUTPUT);
  pinMode(SW,INPUT);
  attachInterrupt(digitalPinToInterrupt(SW), fSwISR, FALLING);
}

void loop() {

}

void fSwISR() {
    tog = !tog;
    digitalWrite(LED2,tog);
}


