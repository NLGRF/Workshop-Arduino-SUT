// Light Dimmer

#define POT   A1
#define LED2  9

unsigned int val;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(POT);
  val /= 4;
  analogWrite(LED2,val);
  Serial.println(val);
}


