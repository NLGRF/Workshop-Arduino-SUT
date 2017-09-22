#define MOTA 5       
#define MOTB 6
int analogPin = A1;   // Potentiometer connected to analog pin 1
int val = 0;         // Variable to store the read value
boolean dir = true;  // Motor's direction

void setup()
{
  pinMode(MOTA, OUTPUT);   // sets the pin as output
  pinMode(MOTB, OUTPUT);   // sets the pin as output
  digitalWrite(MOTA,LOW);
}

void loop()
{

  val = analogRead(analogPin);   // Read the input pin
  analogWrite(MOTB, val / 4);    // AnalogWrite values from 0 to 255
}


