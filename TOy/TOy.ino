const int buttonPin = 2;              // the pin that the pushbutton is attached to
const int RledPin = 3;                // Red LED attached to PWM pin 3
const int BledPin = 5;                // Blue LED attached to PWM pin 5
const int GledPin = 6;                // Green LED attached to PWM pin 6

int mood = 0;                         // the toy's mood state[cite: 5]
const int neutralMood = 10;           // the neutral mood state[cite: 5]
int buttonState = 0;                  // Button Current State[cite: 4, 5]
bool ButtonPressed = false;           // Has the button been pressed or not[cite: 4, 5]

unsigned long touchedTimer = 0;       // the timer used to record the last touch time[cite: 5]
unsigned long reducedTimer = 0;       // the timer used to record the last reduced point time[cite: 5]
const long unTouchInterval = 5000;    // 5-second inactivity threshold before mood decreases[cite: 5]
const long reducedInterval = 1000;    // interval to decrease mood by 1 every second[cite: 5]

void setup() {
  pinMode(buttonPin, INPUT);          //[cite: 4, 5]
  pinMode(RledPin, OUTPUT);           //[cite: 1, 5]
  pinMode(GledPin, OUTPUT);           //[cite: 1, 5]
  pinMode(BledPin, OUTPUT);           //[cite: 1, 5]

  // Initialize the mood state
  mood = neutralMood;                 //[cite: 1, 5]
}

void loop() {
  // Show the toy's current mood on the RGB LED module[cite: 3, 5]
  showLEDState(mood);

  // Check if the button is pressed or not[cite: 4, 5]
  buttonState = digitalRead(buttonPin);

  // If the button is clicked[cite: 4, 5]
  if (buttonState == HIGH && !ButtonPressed) {
    // Increase the mood[cite: 4, 5]
    mood = mood + 1;
    if (mood > 20) {
      mood = 20;
    }
    // Update the touched timer[cite: 5]
    touchedTimer = millis();
    ButtonPressed = true;
  }
  
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;            //[cite: 4, 5]
  }

  // Check if the user hasn't touched the toy for longer than 5 seconds[cite: 5]
  unsigned long currentTimer = millis();
  if (currentTimer - touchedTimer > unTouchInterval) {
    // Reduce the mood point by 1 every second[cite: 5]
    if (currentTimer - reducedTimer > reducedInterval) {
      mood = mood - 1;                //[cite: 5]
      if (mood < 0) {
        mood = 0;                     //[cite: 5]
      }
      reducedTimer = currentTimer;    //[cite: 5]
    }
  }
}

// Common Anode corrected LED function for Pins 3 (Red), 5 (Blue), 6 (Green)
void showLEDState(int state) {
  float brightnessInterval = 255 / 10.0;
  
  if (state >= neutralMood) {
    // Happier mood (10 to 20): Transition from Green to Blue
    analogWrite(RledPin, 255); // Red is OFF
    analogWrite(GledPin, brightnessInterval * (state - neutralMood)); // Green fades out
    analogWrite(BledPin, 255 - brightnessInterval * (state - neutralMood)); // Blue fades in
  }
  else {
    // Sadder mood (0 to 10): Transition from Green to Red
    analogWrite(RledPin, 255 - brightnessInterval * (neutralMood - state)); // Red fades in
    analogWrite(GledPin, brightnessInterval * (neutralMood - state)); // Green fades out
    analogWrite(BledPin, 255); // Blue is OFF
  }
}