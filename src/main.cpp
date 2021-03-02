#include <Arduino.h>
#include "game/game.h"

Game game;

void setup(void)
{
	Serial.begin(115200);
	game.init();
}

void loop()
{
	game.run();
}