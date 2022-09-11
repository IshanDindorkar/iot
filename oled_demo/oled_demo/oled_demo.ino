# include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello World");
  display.display();

}

void loop() {
  delay(1000);

  int l = analogRead(A1);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Light: ");
  display.println(l); 
  display.drawRect(0, 16, 128, 4, WHITE);
  display.fillRect(0, 16, (l*128 / 1024), 4, WHITE);
  display.display();
}
