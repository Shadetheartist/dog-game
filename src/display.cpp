#include "display.h"
#include "graphics.h"

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 135

Display::Display()
{
	tft = new TFT_eSPI(SCREEN_WIDTH, SCREEN_HEIGHT);
	backlightDutyCycle = 0.1f;
}

Display::~Display()
{
	delete tft;
}

void Display::init()
{
	tft->init();
	tft->setRotation(3);
	tft->setSwapBytes(true);
	tft->fillScreen(0x0);

	xTaskCreatePinnedToCore(this->backlightRunner, "backlightRunner", 1000, this, 0, &this->backlightTaskHandle, 0);
}

void Display::backlightRunner(void *display)
{
	Display *d = static_cast<Display *>(display);

	//the base determines the actual slice of time that the delay is off and on.
	const long base = 7500;
	for (;;)
	{
		long high = base * d->backlightDutyCycle;
		long low = base - high;

		digitalWrite(4, LOW);
		delayMicroseconds(low);
		digitalWrite(4, HIGH);
		delayMicroseconds(high);
	}
}