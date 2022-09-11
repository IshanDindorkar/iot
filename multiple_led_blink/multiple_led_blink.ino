// Sketch to blink multiple LEDs in tandem

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  // initialize P0 to P4 as outputs
//  for (int i = 2; i < 8; i++) {
//    pinMode(i, OUTPUT);
//  }
    
}

unsigned char pattern[] = {
  17, 30, 16, 0, 17, 31, 17, 0, 14, 17, 19, 10, 0, 8, 21, 21, 2, 0, 1, 6, 26, 6, 1, 0, 28, 3, 12, 3, 28, 0, 0, 0, 0, 0, 0
};

void loop() {
//  for (int i = 0; i < sizeof(pattern); i++) {
//    int c = pattern[i];
//    digitalWrite(3, (c&(1u<<3)?HIGH:LOW));
//    digitalWrite(4, (c&(1u<<4)?HIGH:LOW));
//    digitalWrite(5, (c&(1u<<5)?HIGH:LOW));
//    digitalWrite(6, (c&(1u<<6)?HIGH:LOW));
//    digitalWrite(7, (c&(1u<<7)?HIGH:LOW));
//    for (int j = 2; j <  8; j++) {
//      digitalWrite(j, (c&(1u<<j)?HIGH:LOW));
//    }
//    delay(3);
//  }

  digitalWrite(3, HIGH);
  delay(5);
  digitalWrite(3, LOW);
  delay(5);
  digitalWrite(4, HIGH);
  delay(5);
  digitalWrite(4, LOW);
  delay(5);
  digitalWrite(5, HIGH);
  delay(5);
  digitalWrite(5, LOW);
  delay(5);
  digitalWrite(6, HIGH);
  delay(5);
  digitalWrite(6, LOW);
  delay(5);
  digitalWrite(7, HIGH);
  delay(5);
  digitalWrite(7, LOW);
  delay(5);
}
