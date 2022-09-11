// This is second part of Blynk task
// In this we will enable LED switched ON/OFF with physical button on board as well as with soft button using Blynk app
// The idea is to bring state of button changed by both ways in sync with each other
// It is also necessary to connect Arduino board to internet and it can be done via laptop port. In order to achieve this,
// follow these steps -
// 1. go to location - ~/IoT/softwares/arduino-1.8.13/libraries/Blynk/scripts
// 2. execute command - sudo ./blynk-ser.sh: This command will ensure that the Arduino board is connected to Internet so that LED state can be synchronized with the
// Blynk app


#define BLYNK_PRINT DebugSerial

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3);


#include <BlynkSimpleStream.h>

#define PIN_LED 4
#define PIN_SWITCH 2

volatile int LED = 0; // volatile?

char auth[] = "JLbSAKYwfUSuegJUGS8XG3aMqc5vaGQT";


void setup() {
  // put your setup code here, to run once:
  DebugSerial.begin(9600);
  
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH), keyPressed, FALLING);
}

void toggleLED() {
  LED = 1 - LED;
  digitalWrite(PIN_LED, LED);
  Blynk.virtualWrite(V1, LED);
}

void keyPressed() {
  static unsigned long lastEvent = 0;
  unsigned long thisEvent = millis();

  if (thisEvent - lastEvent > 200) {
    toggleLED();
  }
  lastEvent = thisEvent;
}

BLYNK_WRITE(V1) {
  toggleLED();
}

BLYNK_READ(V1) {
  Blynk.virtualWrite(V1, LED);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}
