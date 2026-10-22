const int buttonPin = 2;
const int buzzerPin = 8;
const int ledPin = 13;

int visitorCount = 0;
int lastButtonState = HIGH;
int buttonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Digital Doorbell System Ready!");
  Serial.println("Visitors: 0");
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        visitorCount++;

        Serial.print("Doorbell pressed! Visitors: ");
        Serial.println(visitorCount);

        digitalWrite(ledPin, HIGH);

        tone(buzzerPin, 1000, 200);
        delay(250);
        tone(buzzerPin, 1500, 200);
        delay(250);
        noTone(buzzerPin);

        digitalWrite(ledPin, LOW);
      }
    }
  }

  lastButtonState = reading;
}
