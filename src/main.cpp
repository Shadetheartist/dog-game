#include <Arduino.h>

#include "display.h"

Display d = Display();

void setup(void)
{
    Serial.begin(115200);
    d.init();
}
float r = 0;
void loop()
{
    r += 0.01f;
    float dc = fabs(sin(r));
    Serial.println(dc);
    d.backlightDutyCycle = dc;
    delay(10);
}
