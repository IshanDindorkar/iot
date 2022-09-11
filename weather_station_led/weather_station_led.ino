// DHT11 Sensor
#include "DHT.h"
DHT dht(4, DHT11);      // pin = GPIO4 (D2), type = DHT11
float h = 0, c = 0, f = 0;
#define DHT_READ_INTERVAL 5*1000; // Read every 5 seconds
unsigned long dhtReadTime = 0;

// LDR
unsigned int ldr = 0;   // LDR reading
unsigned int bars = 0;  // Number of bars to show on display

// LED pin config
int LED = 13;

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

  // DHT11 Sensor
  dht.begin();

  // LED
  pinMode(LED, OUTPUT);

  // Wi-Fi
  WiFi.mode(WIFI_STA);
  wifiStatus = WiFi.begin("ssid", "password");
  wifiStatus = WiFi.begin();
}

void loop() {

	// DHT11 Sensor
	h = dht.readHumidity();
	c = dht.readTemperature();
	f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(c) || isnan(f)) {
	  Serial.println("Failed to read from DHT sensor!");
	  return;
	}

	// LDR
	ldr = analogRead(A0);
	// calculation of lux value from LDR reading
	// Reference: https://invootech.blogspot.com/2017/06/how-to-convert-ldr-dependent-resistor.html
	float lux = 0.00, ADC_VALUE = 0.0048828125;
	lux = (250.00 / (ADC_VALUE * ldr)) - 50.00;
	Serial.println("The value of lux is: ");
	Serial.println(lux);

	if ((c < 27) && (lux < 14.00)) {
		Serial.println("Temperature fell below 27 C and light intensity is below 14 lux");
		digitalWrite(LED, HIGH);
		Serial.println("LED ON");
		delay(1000);
	} else {
		digitalWrite(LED, LOW);
		Serial.println("LED OFF");
		delay(1000);
	  }

  // Publish
  wifiStatus = WiFi.status();
  if (wifiStatus == WL_CONNECTED) {
    HTTPClient http;
    sprintf(tsUrl, "http://api.thingspeak.com/update?api_key=3GUGH1S53J6741UY&field1=%d&field2=%d&field3=%d&field4=%d", (int)c, (int)h, (int)ldr, (int)isUserPresent);
    http.begin(tsUrl);
    int httpCode = http.GET();
    wifiPublishTime = now + WIFI_PUBLISH_INTERVAL;
  }

  // Run this loop regularly
  delay(1000);
}
