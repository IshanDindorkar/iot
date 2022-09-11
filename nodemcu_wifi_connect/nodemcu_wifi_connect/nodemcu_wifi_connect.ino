#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "wfr49TP0GdM2_TvLAXxx4la_1kMqUG09";

// WiFi credentials
char ssid[] = "Dilip Dindorkar";
char pass[] = "Tinkya12@#";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
