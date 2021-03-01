#include <Arduino.h>
#include <TFT_eSPI.h>
#include "nice-boys.h"

TFT_eSPI tft = TFT_eSPI(135, 240);

void setup(void) {
  
  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.pushImage(0,0,240,135, niceboys);
}

int x = 0, y = 0;

void loop() {
  //this sets the backlight duty cycle
  digitalWrite(4, LOW);
  delay(9);
  digitalWrite(4, HIGH);
  delay(1);
}

