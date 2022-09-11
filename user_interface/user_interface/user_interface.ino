#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  Serial.begin(9600);

  // Push-button switch
  pinMode(2, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(2), keyPressed, FALLING);

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  // Hello, world!
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.display();
}

//void keyPressed() {
//  digitalWrite(2, 0);
//}

void loop() {
  delay(1000);

  int l = analogRead(A1);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Light: ");
  display.println(l);

  display.drawRect(0, 16, 128, 4, WHITE);
  display.fillRect(0, 16, l * 128.0 / 1024, 4, WHITE);

  Serial.println(digitalRead(2));
  if (digitalRead(2) == 0) {
    display.setCursor(0, 24);
    display.println("SWITCH PRESSED");
  }
  
  display.display();
}
