#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2021-03-20 00:57:39

#include "Arduino.h"
extern unsigned long now;
#define PIN_PIR 16
extern int pir;
#define MOTION_TIMEOUT      10*1000
#define BREAK_PROMPT      5*60*1000
#define BREAK_PROMPT_REPEAT 10*1000
extern unsigned long lastSeen;
extern int isUserPresent;
#include "DHT.h"
extern DHT dht;
extern float h;
#define DHT_READ_INTERVAL 5*1000;
extern unsigned long dhtReadTime;
extern unsigned int ldr;
extern unsigned int bars;
#include <Wire.h>
#include "OLED.h"
extern OLED display;
#define MSG_PERIOD 5*1000;
extern unsigned int msgClearTime;
extern char message[];
extern int LED;
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() ;
void loop() ;

#include "workplace_buddy.ino"


#endif
