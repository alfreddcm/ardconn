const int ledPin = 13;     // Pin connected to the LED
const int buttonPin = 2;   // Pin connected to the push button
bool ledState = false;     // Current LED state
bool buttonState = false;  // Current button state
bool lastButtonState = false; // Previous button state

unsigned long lastToggleTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Read the button state
  buttonState = digitalRead(buttonPin);

  // Check if the button state has changed
  if (buttonState != lastButtonState) {
    // If the button is pressed
    if (buttonState == HIGH) {
      ledState = !ledState;  // Toggle the LED state
      digitalWrite(ledPin, ledState ? HIGH : LOW);  // Turn LED on/off based on ledState
      Serial.println(ledState);  // Send the LED state back to the client
    }
    delay(50);  // Delay to debounce the button
  }

  lastButtonState = buttonState;

  // Check if there is serial data available
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '0') {
      ledState = false;  // Turn off the LED
    } else if (command == '1') {
      ledState = true;   // Turn on the LED
    }
    digitalWrite(ledPin, ledState ? HIGH : LOW);  // Turn LED on/off based on ledState
    Serial.println(ledState);  // Send the LED state back to the client

  }
}
