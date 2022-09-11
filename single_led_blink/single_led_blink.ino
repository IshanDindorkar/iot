// the setup routine runs once when you press reset
void setup() {
  // initialize the digital oin as an output
  pinMode(7, OUTPUT);

}

// the loop routine runs over and over again forever
void loop() {
  digitalWrite(7, HIGH); // Arduino
  delay(5000);
  digitalWrite(7, LOW); // Arduino
  delay(5000);
}
