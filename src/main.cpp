#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(135, 240);

void setup(void) {
  tft.init();
  tft.setRotation(3);
}

int x = 0, y = 0;

void loop() {
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(x++, y++, 4, 4, 0xfff);
  delay(32);
}

