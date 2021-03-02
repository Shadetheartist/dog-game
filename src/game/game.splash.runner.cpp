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
	//game->display->tft->pushImage(0, 0, GRAPHIC_SPLASH_IMG.width, GRAPHIC_SPLASH_IMG.height, GRAPHIC_SPLASH_IMG.data);
	game->display->tft->fillScreen(0xddd);
	game->display->tft->fillRect(SCREEN_WIDTH-50, SCREEN_HEIGHT-20,50,20, 0x111);
	
	game->display->tft->setCursor(1, 1, 4);
	game->display->tft->setTextColor(TFT_WHITE, TFT_BLACK);

	
	Serial.print("free heap");
	Serial.println(ESP.getFreeHeap());
	
	//this print seems to be causing an exception loop on occasion.
	game->display->tft->print("Play");

}

void SplashStageRunner::run()
{
	Serial.println("running splash stage runner");
	fadeIn += 0.005;
	game->display->backlightDutyCycle = min(0.5f, fadeIn);
	delay(32);
}

void SplashStageRunner::end()
{
	Serial.println("ending splash stage runner");
}
