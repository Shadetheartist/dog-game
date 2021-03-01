#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include "graphics.h"


class Display 
{
public: 
    Display();
    TFT_eSPI* tft;
    void displayFrame();
    void init();

    float backlightDutyCycle;
    TaskHandle_t backlightTaskHandle;
    static void backlightRunner(void*);
};

#endif
