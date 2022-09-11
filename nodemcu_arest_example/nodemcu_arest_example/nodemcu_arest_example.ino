#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest_api = aREST();

// WiFi parameters
const char* ssid = "Dilip Dindorkar";
const char* password = "Tinkya12@#";

// Create an instance of the server
// Port 80 is used for HTTP connections
WiFiServer server(80);

void setup() {
  // Start serial
  Serial.begin(115200);

  // Pin 16 is used to denote LED on NodeMCU board
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);

  // Function to be exposed
  rest_api.function("led", ledControl);

  // Give name and id to the NodeMCU device
  rest_api.set_id("1");
  rest_api.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  while(!client.available()) {
    delay(1);
  }
  rest_api.handle(client);
}

// Function hooked for invocation when REST API is called for controlling 
// LED light on NodeMCU board
int ledControl(String command) {

  int state = command.toInt();
  Serial.println("Changing LED state");
  Serial.println(state);

  if (state == 0) {
    digitalWrite(16, HIGH);
  } else {
    digitalWrite(16, LOW);
  }

  return state;
}
