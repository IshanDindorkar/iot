// Time since boot
unsigned long now;

// PIR Sensor
#define PIN_PIR 16      // GPIO16, D0
int pir = 0;
// Any motion detected within MOTION_TIMEOUT is considered as user being present.
// If motion is not detected for more than MOTION_TIMEOUT, user is considered to have moved away.
#define MOTION_TIMEOUT      10*1000
// If user is present for more than BREAK_PROMPT time, ask him to take a break every BREAK_PROMPT_REPEAT interval
#define BREAK_PROMPT      5*60*1000
#define BREAK_PROMPT_REPEAT 10*1000
unsigned long lastSeen = 0, lastAway = 0, seenSince = 0, breakTime = 0;
int isUserPresent = 0;

// DHT11 Sensor
#include "DHT.h"
DHT dht(4, DHT11);      // pin = GPIO4 (D2), type = DHT11
float h = 0, c = 0, f = 0;
#define DHT_READ_INTERVAL 5*1000; // Read every 5 seconds
unsigned long dhtReadTime = 0;

// LDR
unsigned int ldr = 0;   // LDR reading
unsigned int bars = 0;  // Number of bars to show on display

// OLED
#include <Wire.h>
#include "OLED.h"
OLED display(2, 14);    // SDA (GPIO2, D4), SCL (GPIO14, D5)
#define MSG_PERIOD 5*1000; // Messages are displayed for 5 seconds
unsigned int msgClearTime = 0;
char message[20];

// Wi-Fi
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
int wifiStatus = WL_IDLE_STATUS;
#define WIFI_PUBLISH_INTERVAL 15*1000; // Thingspeak requires minimum 15s interval
unsigned long wifiPublishTime = 0;
char tsUrl[1024];

void setup() {
  Serial.begin(9600);
  Serial.println("");

  // PIR Sensor
  pinMode(PIN_PIR, INPUT);

  // DHT11 Sensor
  dht.begin();

  // OLED Display on I2C
  display.begin();

  // Wi-Fi
  WiFi.mode(WIFI_STA);
  wifiStatus = WiFi.begin("Dilip Dindorkar", "Tinkya12@#");
  wifiStatus = WiFi.begin();
}

void loop() {
  // Note down current time
  now = millis();

  // PIR Sensor
  pir = digitalRead(PIN_PIR);
  // DHT11 Sensor
  if (dhtReadTime < now) {
    h = dht.readHumidity();
    c = dht.readTemperature();
    f = dht.readTemperature(true);
  
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(c) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    dhtReadTime = now + DHT_READ_INTERVAL;
  }
  // LDR
  ldr = analogRead(A0);
  
  // PIR Sensor
  if (pir == HIGH) { // User is present
    if (!isUserPresent) {
      Serial.printf("User is here.         %6ds break\n", (now - lastSeen) / 1000);
      display.print("Welcome back!   ", 0, 0);
      msgClearTime = now + MSG_PERIOD;
      seenSince = now;
      breakTime = now + BREAK_PROMPT;
      isUserPresent = 1;
      display.on();
    }
    if (now > breakTime) {
      Serial.printf("Time to take a break? %6ds work\n", (now - seenSince) / 1000);
      display.print("Break time!     ", 0, 0);
      msgClearTime = now + MSG_PERIOD;
      breakTime = now + BREAK_PROMPT_REPEAT;
    }
    lastSeen = now;
  }
  else { // User may be away or still
    if (now > MOTION_TIMEOUT && isUserPresent && lastSeen < (now - MOTION_TIMEOUT)) {
      Serial.printf("User is away...       %6ds work\n", (lastSeen - seenSince) / 1000);
      msgClearTime = now;
      isUserPresent = 0;
      display.off();
    }
    lastAway = now;
  }
  if (msgClearTime > 0 && msgClearTime <= now) {
    display.print("                ", 0, 0);
    msgClearTime = 0;
  }

  // LDR
  int i;
  bars = ((ldr + 32) / 64);
  for (i = 0; i < bars; i++)
    message[i] = '#';
  for (; i < 16; i++)
    message[i] = '-';
  message[i] = 0;
  display.print(message, 7, 0);
  if (bars < 4)
    display.print("Low Light", 6, 7);
  else
    display.print("         ", 6, 7);

  // DHT
  sprintf(message, "%2dC  %2d%%", (int)c, (int)h);
  display.print(message, 4, 4);

  // Publish
  wifiStatus = WiFi.status();
  if (wifiPublishTime < now && wifiStatus == WL_CONNECTED) {
    HTTPClient http;
    Serial.println(ldr);
    Serial.println(isUserPresent);
    sprintf(tsUrl, "http://api.thingspeak.com/update?api_key=3GUGH1S53J6741UY&field1=%d&field2=%d&field3=%d&field4=%d", (int)c, (int)h, (int)ldr, (int)isUserPresent);
    http.begin(tsUrl);
    int httpCode = http.GET();
    wifiPublishTime = now + WIFI_PUBLISH_INTERVAL;
  }

  // Run this loop regularly
  delay(1000);
}
