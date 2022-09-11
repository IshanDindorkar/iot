// With simple ISR implementation, we noticed that an LED turns ON multiple times over the duration of pressing switch button due to extended pressure applied
// In order to avoid repetitive turning ON of LED, we put a check on when was the last time ISR was invoked by measuring time of last event and current event.
// It should not be less than 200ms.
// This pehnomenom is called as Debouncing

#define PIN_LED 4
#define PIN_SWITCH 2

int LED = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH), keyPressed, FALLING);
}

void toggleLED() {
  LED = 1 - LED;
  digitalWrite(PIN_LED, LED);
}

void keyPressed() {
  static unsigned long lastEvent = 0;
  unsigned long thisEvent = millis();
  // Logic for preventing bouncing of LED
  if (thisEvent - lastEvent > 400) {
    toggleLED();
  }
  lastEvent = thisEvent;
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(PIN_SWITCH)) {
//    toggleLED();
//  }

  delay(200);
}
