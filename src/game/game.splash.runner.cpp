#include "game/stageRunner.h"
#include <Arduino.h>
#include "graphics.h"

SplashStageRunner::SplashStageRunner(Game* game) : StageRunner(game)
{
	
}

SplashStageRunner::~SplashStageRunner() 
{
	
}

void SplashStageRunner::begin()
{
	Serial.println("beginning splash stage runner");
	game->display->tft->pushImage(0, 0, GRAPHIC_SPLASH_IMG.width, GRAPHIC_SPLASH_IMG.height, GRAPHIC_SPLASH_IMG.data);
}

void SplashStageRunner::run()
{
	Serial.println("running splash stage runner");
	delay(1000);
}

void SplashStageRunner::end()
{
	Serial.println("ending splash stage runner");
}
