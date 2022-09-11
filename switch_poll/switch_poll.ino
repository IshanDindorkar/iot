// In this sketch, a switch is used to change state of a pin on Arduino board and it is sensed using a LED
#define PIN_LED 4
#define PIN_SWITCH 2

int LED = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
}

void toggleLED() {
  LED = 1 - LED;
  digitalWrite(PIN_LED, LED);
}

void loop() {
  if (digitalRead(PIN_SWITCH)) {
    toggleLED();
  }

  delay(200);
}
