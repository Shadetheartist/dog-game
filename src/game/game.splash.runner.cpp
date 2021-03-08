#include "game/stageRunner.h"
#include <Arduino.h>
#include "dog/dogGraphics.h"

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
	
	uint16_t *outputBuffer = NULL;
	DogGraphics::decodePNGData(&outputBuffer, "/splash-screen.png");

	if(outputBuffer == NULL){
    Serial.println("failed to decode png data");
    return;
  }
	
	game->display->tft->pushImage(0, 0, 240, 135, outputBuffer);
	
	free(outputBuffer);
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
