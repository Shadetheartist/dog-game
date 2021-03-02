#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>
#include "graphics.h"

class Display
{
public:
	Display();
	~Display();
	TFT_eSPI *tft;
	void init();

	/* Can be set to change the brightness of the backlight.*/
	float backlightDutyCycle;
	TaskHandle_t backlightTaskHandle;
	static void backlightRunner(void *);
};

#endif
