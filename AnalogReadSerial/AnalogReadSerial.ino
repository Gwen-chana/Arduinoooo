/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/
const int RledPin = 3;
const int BledPin = 5;
const int GledPin = 6;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(RledPin, OUTPUT); pinMode(BledPin, OUTPUT); pinMode(GledPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  if(sensorValue < 256) {
    digitalWrite(RledPin,LOW);
     digitalWrite(BledPin,HIGH);
      digitalWrite(GledPin,HIGH);
  }
  else if (sensorValue < 512){
    digitalWrite(RledPin,HIGH);
     digitalWrite(BledPin,HIGH);
      digitalWrite(GledPin,LOW);
  }
  else if (sensorValue <767) {
      digitalWrite(RledPin,HIGH);
     digitalWrite(BledPin,LOW);
      digitalWrite(GledPin,HIGH);
  }
else if (sensorValue <1024) {
    digitalWrite(RledPin,LOW);
     digitalWrite(BledPin,LOW);
      digitalWrite(GledPin,LOW);
}
  delay(1);  // delay in between reads for stability
}
