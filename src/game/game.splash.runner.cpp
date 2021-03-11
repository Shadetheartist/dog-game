#include "game/stageRunner.h"
#include <Arduino.h>

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
