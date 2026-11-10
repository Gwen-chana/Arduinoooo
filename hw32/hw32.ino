// Define pins
const int buttonPin = 2;  // Button connected to pin D2
const int ledPin = 3;     // LED connected to pin D3 as required[cite: 1]

// State tracking variables
int buttonState = 0;         // Current reading from the input pin
int lastButtonState = HIGH;  // Previous reading from the input pin (using INPUT_PULLUP)
int mode = 0;                // Current blinking mode (0 to 3)

// Debounce timing variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Timing variables for non-blocking blinking modes
unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button uses internal pull-up resistor
  pinMode(ledPin, OUTPUT);          // LED pin set as output
}

void loop() {
  // Read the state of the switch/button
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing, reset the debouncing timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Whatever the reading is at, it's been there for longer than the debounce delay,
    // so take it as the actual current state:
    if (reading != buttonState) {
      buttonState = reading;

      // Only toggle state when the button is pressed (transition from HIGH to LOW)
      if (buttonState == LOW) {
        mode = (mode + 1) % 4; // Cycles through 0, 1, 2, 3[cite: 1]
      }
    }
  }

  lastButtonState = reading;

  // Execute behavior based on the current mode
  unsigned long currentMillis = millis();

  switch (mode) {
    case 0: // State 1: Steady lighting[cite: 1]
      digitalWrite(ledPin, HIGH);
      break;

    case 1: // State 2: Slow blink (~1000ms interval)[cite: 1]
      if (currentMillis - previousMillis >= 500) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
      break;

    case 2: // State 3: Medium blink (~300ms interval)[cite: 1]
      if (currentMillis - previousMillis >= 150) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
      break;

    case 3: // State 4: Fast blink (~100ms interval)[cite: 1]
      if (currentMillis - previousMillis >= 50) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }
      break;
  }
}