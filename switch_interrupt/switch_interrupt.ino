// Interrupt - An asynchronous event that can happen anytime due to change in state. For example, when we press a button, it is causing an interrupt as it
// changes state of circuit
// Interrupt Service Routine(ISR) - A piece of code that runs when an interrupt happens. On arduino board, D2, D3 can be hooked to interrupts.
// Properties of ISR - 
// 1. It cannot accept any argument or return a value
// 2. It should finish very quickly and minimum processing is required
// 3. It should not use any blocking function or perform any I/O function
// 4. regarding Global variables ....
 
// Types of ISR triggering conditions
// 1. LOW - pin state continues to remain LOW
// 2. RISING - pin changes state from LOW to HIGH
// 3. FALLING - pin changes state from HIGH to LOW
// 4. CHANGE - pin changes state from LOW to HIGH or HIGH to LOW


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
  toggleLED();
}

void loop() {
  // put your main code here, to run repeatedly:
//  if (digitalRead(PIN_SWITCH)) {
//    toggleLED();
//  }

  delay(200);
}
