// Interrupter Test by polling
int pin_Counter = 3;
int counter = 0;
void setup() {
  pinMode(pin_Counter,INPUT);
  Serial.begin(9600);
}

void loop() {
  int isCount = digitalRead(pin_Counter);
  if (isCount == 1) {
    counter++;
    Serial.println(counter);
    delay(500);
  }
}


