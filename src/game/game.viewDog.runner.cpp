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

	sprite = new TFT_eSprite(game->display->tft);
	sprite->createSprite(56, 40);
	arg->dog->renderToSprite(sprite);

}
int x = 0, y = 0;
void ViewDogStageRunner::run()
{
	delay(100);
	sprite->pushSprite(x, y, TFT_TRANSPARENT);
	x++;
	yield();
}

void ViewDogStageRunner::end() 
{
	Serial.println("ending view dog stage runner");
}

