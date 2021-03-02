#include "game/stageRunner.h"
#include <Arduino.h>

MainMenuStageRunner::MainMenuStageRunner(Game* game) : StageRunner(game)
{
	
}

MainMenuStageRunner::~MainMenuStageRunner() 
{
	
}

void MainMenuStageRunner::begin() 
{
	Serial.println("beginning main menu stage runner");
}

void MainMenuStageRunner::run() 
{
	Serial.println("running main menu stage runner");
}

void MainMenuStageRunner::end() 
{
	Serial.println("ending main menu stage runner");
}

