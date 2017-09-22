// Analog Input

#define LDR   A0

unsigned int val;
float vin;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(LDR);
  vin = val * 5.0/1024;
  Serial.print("digital = ");
  Serial.print(val);
  Serial.print(", Vin = ");
  Serial.print(vin,2);
  Serial.println(" volts");
  delay(200);
}


