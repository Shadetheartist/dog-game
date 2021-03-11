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
	Serial.print("viewing dog: ");
	Serial.println(arg->dog->name.c_str());

	game->display->tft->fillScreen(TFT_LIGHTGREY);
	sprite = new TFT_eSprite(game->display->tft);
	sprite->createSprite(110, 110);

	arg->dog->renderToSprite(sprite);
	sprite->pushSprite(SCREEN_WIDTH/2-60, SCREEN_HEIGHT/2-40);

}

void ViewDogStageRunner::run()
{
	delay(100);
	yield();
}

void ViewDogStageRunner::end() 
{
	Serial.println("ending view dog stage runner");
}

