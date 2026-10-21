// Button pin (using internal pull-up: connect button between Pin 3 and GND)
const int buttonPin = 3;

// RGB LED Pins (Red on 5, Green on 6, Blue on PWM Pin 9)
const int RLED = 5;
const int GLED = 6;
const int BLED = 9;

// Mode and Color tracking variables
int currentMode = 0;   // 0: Constant, 1: Blink, 2: Breathing, 3: Rainbow
int currentColor = 0;  // 0: Red, 1: Yellow, 2: Green, 3: Blue, 4: Purple, 5: White

// Color definition arrays (Base color values)
const int numColors = 6;
const byte colorR[numColors] = {255, 255,   0,   0, 128, 255}; 
const byte colorG[numColors] = {  0, 255, 255,   0,   0, 255};
const byte colorB[numColors] = {  0,   0,   0, 255, 128, 255};

// Button state variables for robust click/long-press separation
int lastButtonState = HIGH;
unsigned long pressingTime = 0;
bool isButtonPressed = false;
bool longPressTriggered = false;
const unsigned long longPressInterval = 1500; // 2 seconds threshold

// Non-blocking timing variables for animations
unsigned long previousMillis = 0;
bool blinkState = false;
int breathValue = 0;
int breathDirection = 1;
int rainbowHue = 0;

void setup() {
  // Use INPUT_PULLUP so the button reads LOW when pressed
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(BLED, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // 1. Detect button press (Transition from HIGH to LOW)
  if (reading == LOW && lastButtonState == HIGH && !isButtonPressed) {
    pressingTime = millis();
    isButtonPressed = true;
    longPressTriggered = false;
  }

  // 2. While holding, check if it reaches the long-press threshold
  if (isButtonPressed && reading == LOW) {
    if (!longPressTriggered && (millis() - pressingTime >= longPressInterval)) {
      // Long press reached while holding! Change mode immediately.
      currentMode = (currentMode + 1) % 4; 
      longPressTriggered = true; // Lock out short-click for this press
    }
  }

  // 3. Detect button release (Transition from LOW to HIGH)
  if (reading == HIGH && lastButtonState == LOW && isButtonPressed) {
    // If a long press was NOT triggered, it's a valid short click!
    if (!longPressTriggered) {
      currentColor = (currentColor + 1) % numColors; // Change color
    }
    isButtonPressed = false; // Reset for the next press
  }

  lastButtonState = reading;

  // Continuously update the LED based on active mode and color
  updateLED();
}

void updateLED() {
  unsigned long currentMillis = millis();

  switch (currentMode) {
    case 0: // 1/ Constant Light Mode (Common Anode inversion)
      analogWrite(RLED, 255 - colorR[currentColor]);
      analogWrite(GLED, 255 - colorG[currentColor]);
      analogWrite(BLED, 255 - colorB[currentColor]);
      break;

    case 1: // 2/ Blink Mode
      if (currentMillis - previousMillis >= 550) { 
        previousMillis = currentMillis;
        blinkState = !blinkState;
      }
      if (blinkState) {
        analogWrite(RLED, 255 - colorR[currentColor]);
        analogWrite(GLED, 255 - colorG[currentColor]);
        analogWrite(BLED, 255 - colorB[currentColor]);
      } else {
        analogWrite(RLED, 255); // OFF for Common Anode
        analogWrite(GLED, 255);
        analogWrite(BLED, 255);
      }
      break;

    case 2: // 3/ Breathing (Fading) Light Mode
      if (currentMillis - previousMillis >= 15) { 
        previousMillis = currentMillis;
        breathValue += breathDirection * 4;
        if (breathValue <= 0 || breathValue >= 255) {
          breathDirection = -breathDirection;
          breathValue = constrain(breathValue, 0, 255);
        }
      }
      analogWrite(RLED, 255 - ((colorR[currentColor] * breathValue) / 255));
      analogWrite(GLED, 255 - ((colorG[currentColor] * breathValue) / 255));
      analogWrite(BLED, 255 - ((colorB[currentColor] * breathValue) / 255));
      break;

    case 3: // 4/ Rainbow Mode
      if (currentMillis - previousMillis >= 20) {
        previousMillis = currentMillis;
        rainbowHue = (rainbowHue + 1) % 768; 
      }
      showRainbow(rainbowHue);
      break;
  }
}

// Helper function to generate rainbow transitions (Common Anode)
void showRainbow(int hue) {
  int r = 0, g = 0, b = 0;
  if (hue < 256) {
    r = 255 - hue;
    g = hue;
    b = 0;
  } else if (hue < 512) {
    int ahue = hue - 256;
    r = 0;
    g = 255 - ahue;
    b = ahue;
  } else {
    int ahue = hue - 512;
    r = ahue;
    g = 0;
    b = 255 - ahue;
  }
  analogWrite(RLED, 255 - r);
  analogWrite(GLED, 255 - g);
  analogWrite(BLED, 255 - b);
}