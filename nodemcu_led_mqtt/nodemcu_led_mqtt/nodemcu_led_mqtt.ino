/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

/*
 LED blink using MQTT (Document from Jigsaw)

Preparing the circuit

▪ Place NodeMCU board on the breadboard.
▪ Connect a 100 Ω resistor to 3V3 pin of NodeMCU board.
▪ Connect anode pin of LED to other end of resistor.
▪ Connect cathode pin of LED to pin D1 (GPIO5) of NodeMCU board.
▪ Place the push-button switch module on breadboard.
▪ Connect one pin of the push-button switch (K1) to pin D5 (GPIO14) of NodeMCU board.
▪ Connect GND pin of push-button switch to GND pin of NodeMCU board.

Installing Pub-Sub client libraries for Arduino IDE

▪ Visit https://github.com/knolleary/pubsubclient
▪ Download a zip package of the project:

▪ Unpack the library package under your Arduino/libraries folder. For Windows, it is
generally found under your Documents folder.
▪ Restart the Arduino IDE if it is already running.

Remote monitoring & control using MQTTlens
▪ Install MQTTlens from following URL. It is a Chrome packaged application, so use Google
Chrome browser:
https://chrome.google.com/webstore/detail/mqttlens/hemojaaeigabkbcookmlgmdigohjobjm
▪ Launch the application from apps page of chrome: chrome://apps
▪ Add a new connection with this configuration:
o Name: Eclipse
o Hostname: iot.eclipse.org
o Port: 1883
▪ Subscribe to the topic: esp<your_randon_number>/fromDevice
▪ Toggle the LED a couple of times by pressing the push-button switch and observe how
corresponding messages appear on MQTTlens. Every change in state of LED will be
received on MQTTlens.
▪ Keep the LED in OFF state using push-button switch.
▪ Open Publish settings in MQTTlens and set topic to: esp<your_randon_number>
/toDevice
▪ Set message as 1 and publish it. Notice that the LED turns ON and we also receive a
message over MQTT indicating its new state.
▪ Set message as 0 and publish it. Notice that the LED turns OFF and we also receive a
message over MQTT indicating its new state.
▪ Now we are able to monitor the state of LED remotely over MQTT and also able to
control it.
▪ Open Serial Monitor, press the push-button switch a few times and notice state of LED
and well as serial output.
 
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Dilip Dindorkar";
const char* password = "Tinkya12@#";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

#define PIN_LED 5
#define PIN_SWITCH 14

int LED = 0; // Current state of LED

void setLED (int val) {
  LED = val;
  digitalWrite(PIN_LED, 1 - LED); // Active Low
  
  // if nodemcu is connected to internet, 
  // it can publish its message to MQTT server configured
  if (client.connected()) {
    char str[8];
    sprintf (str, "LED: %d", LED);
    Serial.println(str);
    client.publish("esp9340875665/fromDevice", str);
  }
}

void toggleLED() {
  setLED(1 - LED);
}

volatile int keyFlag = 0;
//ICACHE_RAM_ATTR: I followed tutorial but I was getting junk messages on serial monitor
// After googling I found this solution - https://stackoverflow.com/questions/58113937/esp8266-arduino-why-is-it-necessary-to-add-the-icache-ram-attr-macro-to-isrs-an 
ICACHE_RAM_ATTR void keyPressed() {
  keyFlag = 1;
  toggleLED();
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if 1 was received as first character
  if ((char)payload[0] == '1') {
    setLED(1);
  } else {
    setLED(0);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client9340875665")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("esp9340875665/fromDevice", "hello world");
      // ... and resubscribe
      client.subscribe("esp9340875665/toDevice");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // Initializing of pins on nodemcu board
  pinMode(PIN_LED, OUTPUT);
  setLED(0);
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH), keyPressed, FALLING);
  
  Serial.begin(115200);

  // connecting nodemcu board to wifi network 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  
  // check if switch is pressed.
  // if yes, value of flag will be 1
  if (keyFlag == 1) {
    toggleLED();
    keyFlag = 0;
  }
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
