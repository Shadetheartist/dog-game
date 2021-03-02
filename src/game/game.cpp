#include "game/game.h"
#include "game/stageRunner.h"

Game::Game()
{
	display = new Display();
}

Game::~Game()
{
	delete display;
}

void Game::init()
{
	display->init();
	state = Running;
	changeStage(SplashScreen);
}

void Game::run()
{
	switch (state)
	{
	case GameState::Paused:
		break;

	case GameState::Running:
		stageRunner->run();
		break;
	}
}

void Game::changeStage(GameStage newStage) 
{
	stage = newStage;

	//this may be null on first use
	if(stageRunner != NULL){
		stageRunner->end();
		delete stageRunner;
	}

	switch (stage)
	{
		case GameStage::SplashScreen:
			stageRunner = new SplashStageRunner(this);
			break;

		case GameStage::MainMenu:
			stageRunner = new MainMenuStageRunner(this);
			break;
	
		default:
			//backup to stop errors while developing
			stageRunner = new SplashStageRunner(this);
			break;
	}

	stageRunner->begin();
}
