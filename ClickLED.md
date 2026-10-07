const int pushButton = 2; // the number of the pushbutton pin

const int REDPin= 7;
const int BLUEPin= 6; // the number of the LED pin
const int GREENPin= 5;

// variables will change:

int buttonState = 1 ;
int ledcolor = 0; // variable for reading the pushbutton status
bool ButtonPressed = false;

void setup() {

// initialize the LED pin as an output:

pinMode (REDPin, OUTPUT);
pinMode (BLUEPin, OUTPUT);
pinMode (GREENPin, OUTPUT);
pinMode (pushButton, INPUT);
}

// initialize the pushbutton pin as an input: pinMode (pushButton, INPUT);

void loop() {

buttonState = digitalRead(pushButton);

if (buttonState == LOW && !ButtonPressed) {
  ledcolor = ledcolor + 1;
  ButtonPressed = true;
}
if (buttonState == HIGH && ButtonPressed) {
  delay(200);
  ButtonPressed = false;
}

if (ledcolor == 0) {
  digitalWrite(REDPin, HIGH);
  digitalWrite(BLUEPin, HIGH);
  digitalWrite(GREENPin, HIGH);
}
else if (ledcolor == 1) {
  //red
  digitalWrite(REDPin, LOW);
  digitalWrite(BLUEPin, HIGH);
  digitalWrite(GREENPin, HIGH);
}
else if (ledcolor == 2) {
  //GREEN
  digitalWrite(REDPin, HIGH);
  digitalWrite(BLUEPin, HIGH);
  digitalWrite(GREENPin, LOW);
}
else if (ledcolor == 3) {
  //BLUE
  digitalWrite(REDPin, HIGH);
  digitalWrite(BLUEPin, LOW);
  digitalWrite(GREENPin, HIGH);
}
else if (ledcolor == 4) {
  //PURPLE
  digitalWrite(REDPin, LOW);
  digitalWrite(BLUEPin, LOW);
  digitalWrite(GREENPin, HIGH);
}
else if (ledcolor == 5) {
  //CORTIS
  digitalWrite(REDPin, LOW);
  digitalWrite(BLUEPin, HIGH);
  digitalWrite(GREENPin, LOW);
}
else if (ledcolor == 6) {
  //CYAN
  digitalWrite(REDPin, HIGH);
  digitalWrite(BLUEPin, LOW);
  digitalWrite(GREENPin, LOW);
}
else if (ledcolor == 7) {
  //WHITE
  digitalWrite(REDPin, LOW);
  digitalWrite(BLUEPin, LOW);
  digitalWrite(GREENPin, LOW);
}
else if (ledcolor == 8) {
  ledcolor = 0;
}
}
