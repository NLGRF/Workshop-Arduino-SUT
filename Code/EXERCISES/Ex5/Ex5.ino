// Deboucing switch

#define LED2   9
#define SW     3
#define N      5

boolean tog = false; 

void setup() {
  pinMode(LED2,OUTPUT);
  pinMode(SW,INPUT);
}

void loop() {

  if (digitalRead(SW) == LOW) {
    delay(300);          // Delay 300ms for debouncing
    tog = !tog;
    digitalWrite(LED2,tog);
  }
}


