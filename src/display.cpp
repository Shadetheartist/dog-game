#include "display.h"
#include "graphics.h"

TFT_eSPI _tft = TFT_eSPI();

Display::Display()
{
	backlightDutyCycle = 0;
	this->tft = &_tft;
}

Display::~Display()
{
	
}

void Display::init()
{
	Serial.println("init display");
	tft->init();
	tft->setRotation(3);
	tft->setSwapBytes(true);
	tft->fillScreen(0x0);

	//xTaskCreatePinnedToCore(this->backlightRunner, "backlightRunner", 1000, this, 0, &this->backlightTaskHandle, 0);
}

void Display::backlightRunner(void *display)
{
	Display *d = static_cast<Display *>(display);

	//the base determines the actual slice of time that the delay is off and on.
	const long base = 7;
	for (;;)
	{
		long high = base * d->backlightDutyCycle;
		long low = base - high;

		digitalWrite(4, LOW);
		delay(low);
		digitalWrite(4, HIGH);
		delay(high);
		yield();
	}
}