// Interrupter Test using ISR
int ledPin = 13;
int intrPin = 3;
volatile byte state = LOW;
volatile unsigned int cnt = 0;
volatile byte flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(intrPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intrPin), fBlink, FALLING);
 }

void loop() {
  if (flag) {
    if (digitalRead(intrPin)==HIGH) {
      cnt++;
      Serial.println(cnt);
      state=!state;
      digitalWrite(ledPin, state);
      flag=0;
    }
  }
}

void fBlink() {
  flag=1;
}


