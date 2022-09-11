/**
▪ Place the NodeMCU on the breadboard
▪ Connect the anode (longer leg) of the LED to the pin marked D2 on the
NodeMCU
▪ Use a dupont connect to connect the other end of the LED (cathode; the
shorter leg) to one of the pins marked GND to complete the circuit.
▪ Connect the NodeMCU to your PC using the supplied USB Mini cable
▪ Install the Arduino libraries for ESP8266
• Open the Arduino IDE on your PC
• Go to File->Preferences
• Add “http://arduino.esp8266.com/stable/package_esp8266com_
index.json”
to the “Additional Board Managers URL” field
• Click “OK” to close
• Open Tools->Boards:.. and select “Boards Manager”
• Scroll down to look for ESP8266 and click “Install”
▪ Go to Tools -> Board:... and select “NodeMCU 1.0 (ESP-12E Module)”
▪ Open sketch named “one_led.ino”
▪ Change the LED pre-processor symbol to 4
▪ Upload the sketch
▪ You should observe the LED blinking
 *
 */

//int LED = 4;
int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println("LED ON");
  digitalWrite(LED, LOW);
  Serial.println("LED OFF");

  delay(1000);
}
