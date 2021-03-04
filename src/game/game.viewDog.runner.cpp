#include "game/stageRunner.h"
#include <Arduino.h>

static TFT_eSprite *sprite;

ViewDogStageRunner::ViewDogStageRunner(Game* game, ViewDogStageRunnerArg *arg) : StageRunner(game)
{
	this->arg = arg;
}

ViewDogStageRunner::~ViewDogStageRunner() 
{
	delete sprite;
}

void ViewDogStageRunner::begin() 
{
	if(arg == NULL || arg->dog == NULL){
		Serial.println("no dog to view");
		game->returnToPreviousStage();
		return;
	}

	Serial.println("beginning view dog stage runner");

	game->display->tft->fillScreen(TFT_LIGHTGREY);
	sprite = new TFT_eSprite(game->display->tft);
	sprite->createSprite(64, 64);
}

void ViewDogStageRunner::run()
{
	arg->dog->renderToSprite(sprite);
	sprite->pushSprite(SCREEN_WIDTH/2-60, SCREEN_HEIGHT/2-40);

	delay(100);

	yield();
}

void ViewDogStageRunner::end() 
{
	Serial.println("ending view dog stage runner");
}

