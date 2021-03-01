#include "display.h"
#include "graphics.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 135

Display::Display(){
    tft = new TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
    backlightDutyCycle = 0.1f;
}

void Display::init(){
    tft->init();
    tft->setRotation(3);
    tft->setSwapBytes(true);
    xTaskCreatePinnedToCore(this->backlightRunner, "backlightRunner", 1000, this, 0, &this->backlightTaskHandle, 0);
}


void Display::displayFrame(){
    tft->pushImage(0,0,240,135, GRAPHICS_SPLASH_IMG);
}

void Display::backlightRunner(void* display){
    Display* d = static_cast<Display*>(display);
    const short base = 10000;
    for(;;){
        short high = base * d->backlightDutyCycle;
        short low = base - high;

        digitalWrite(4, LOW);
        delayMicroseconds(low);
        digitalWrite(4, HIGH);
        delayMicroseconds(high);
    }
}