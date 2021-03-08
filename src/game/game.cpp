#include "game/game.h"
#include "game/stageRunner.h"
#include "dog/dog.h"
#include "dog/dogGraphics.h"
#include "SPIFFS.h"

Game::Game()
{
	display = new Display();
}

Game::~Game()
{
	Serial.println("destructing Game");
	delete display;
}

void Game::init()
{
	Serial.println("init Game");

	if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

	display->init();
	state = Running;
	previousStage = None;

	ViewDogStageRunnerArg *arg = new ViewDogStageRunnerArg();
	arg->dog = Dog::createDog();

	changeStage(SplashScreen, arg);
}

void Game::run()
{
	switch (state)
	{
		case GameState::Paused:
			break;

		case GameState::Running:
		if(stageRunner != NULL){
			stageRunner->run();
		}
		break;
	}
}

void Game::changeStage(GameStage newStage, StageRunnerArg *arg) 
{
	//this may be null on first use
	if(stageRunner != NULL){
		stageRunner->end();

		delete previousStageRunnerArg;

		previousStage = stage;
		previousStageRunnerArg = stageRunnerArg;
	}

	stage = newStage;

	switch (stage)
	{
		case GameStage::SplashScreen:
			stageRunner = new SplashStageRunner(this);
			break;

		case GameStage::MainMenu:
			stageRunner = new MainMenuStageRunner(this);
			break;

		case GameStage::ViewDog:
			stageRunner = new ViewDogStageRunner(this, (ViewDogStageRunnerArg*)arg);
			break;
	
		default:
			//backup to stop errors while developing
			stageRunner = new SplashStageRunner(this);
			break;
	}

	stageRunnerArg = arg;

	stageRunner->begin();
}

void Game::returnToPreviousStage() 
{
	if(previousStage == None){
		changeStage(SplashScreen);
	}
	else{
		changeStage(previousStage, previousStageRunnerArg);
	}
}
