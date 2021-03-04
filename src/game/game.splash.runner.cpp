#include "game/stageRunner.h"
#include <Arduino.h>
#include "graphics.h"


static float fadeIn;

SplashStageRunner::SplashStageRunner(Game* game) : StageRunner(game)
{
	
}

SplashStageRunner::~SplashStageRunner() 
{
	
}

void SplashStageRunner::begin()
{
	Serial.println("beginning splash stage runner");
	fadeIn = 0;
	game->display->backlightDutyCycle = fadeIn;
	game->display->tft->pushImage(0, 0, GRAPHIC_SPLASH_IMG.width, GRAPHIC_SPLASH_IMG.height, GRAPHIC_SPLASH_IMG.data);
}

void SplashStageRunner::run()
{
	fadeIn += 0.005;
	game->display->backlightDutyCycle = min(0.5f, fadeIn);
	delay(32);
	if(fadeIn > 0.5){
		game->changeStage(MainMenu);
	}
}

void SplashStageRunner::end()
{
	Serial.println("ending splash stage runner");
}
