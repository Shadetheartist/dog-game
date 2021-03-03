#include "game/stageRunner.h"
#include <Arduino.h>

static TFT_eSprite *sprite;

MainMenuStageRunner::MainMenuStageRunner(Game* game) : StageRunner(game)
{
	menu = new Menu();
	menu->menuItems.push_back(std::pair<char*, MenuCb>("Test Doggo Gen", NULL));
	menu->menuItems.push_back(std::pair<char*, MenuCb>("Menu Item 2", NULL));
	menu->menuItems.push_back(std::pair<char*, MenuCb>("Menu Item 3", NULL));
}

MainMenuStageRunner::~MainMenuStageRunner() 
{
	delete menu;
	delete sprite;
}

void MainMenuStageRunner::begin() 
{
	game->display->backlightDutyCycle = 1;

	Serial.println("beginning main menu stage runner");

	game->display->tft->fillScreen(TFT_BLUE);
	sprite = new TFT_eSprite(game->display->tft);
	sprite->createSprite(120, 80);
}

void MainMenuStageRunner::run()
{
	Serial.println("running main menu stage runner");
	delay(100);

	menu->nextItem();
	menu->renderToSprite(sprite);
	sprite->pushSprite(SCREEN_WIDTH/2-60, SCREEN_HEIGHT/2-40);

	yield();
}

void MainMenuStageRunner::end() 
{
	Serial.println("ending main menu stage runner");
}

