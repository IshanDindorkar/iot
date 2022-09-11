/**
 * This Arduino Sketch is written as part of bigger project where 2 machine talk to each other through
 * Gateway. Below is description
 * 1. NodeMCU: machine 1. It is connected to LDR which emits its resistance value.
 * 2. Arduino: machine 2. It is connected to blinking LED. The state of LED will be controlled by
 * the value received from LDR connected to NodeMCU
 * 3. Node-Red: Gateway server which is running on RaspberryPi board. NodeMCU and Arduino communicate with
 * each other through Node-Red gateway server.
 *
 * The sketch included below is responsible for controlling LDR through NodeMCU board
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

// Customizations
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {

	// Customizations
	dht.begin();

	USE_SERIAL.begin(9600);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("Dilip Dindorkar", "Tinkya12@#");
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

    	// Customizations
		float h = dht.readHumidity();
		float t = dht.readTemperature();
		if (isnan(h) || isnan(t)) {
		  Serial.println("Failed to read from DHT sensor");
		  delay(2000);
		  return;
		}
		USE_SERIAL.println("Temperature");
		USE_SERIAL.println(t);

        // Read LDR value
        int ldr = analogRead(A0);
        // calculation of lux value from LDR reading
        // Reference: https://invootech.blogspot.com/2017/06/how-to-convert-ldr-dependent-resistor.html
        float lux = 0.00, ADC_VALUE = 0.0048828125;
        lux = (250.00 / (ADC_VALUE * ldr)) - 50.00;
        USE_SERIAL.println("LDR in lux");
        USE_SERIAL.println(lux);


        // Form URL to send LDR value to gateway(read Node-RED)
        char url[256];
        sprintf (url, "http://192.168.1.13:1880/nodemcu?ldr=%f&temp=%f&humidity=%f", lux, t, h);

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin(url); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
}
