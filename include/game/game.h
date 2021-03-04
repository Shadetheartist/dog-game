#ifndef INCLUDE_GAME_GAME
#define INCLUDE_GAME_GAME
#include "display.h"

enum GameState
{
	Paused,
	Running
};

enum GameStage
{
	None,
	SplashScreen,
	MainMenu,
	Doghouse,
	ViewDog,
};

class StageRunner;
class StageRunnerArg;

class Game
{
public:
	GameState state;
	GameStage stage;
	Display *display;

	StageRunner *stageRunner;
	StageRunnerArg *stageRunnerArg;

	GameStage previousStage;
	StageRunnerArg *previousStageRunnerArg;
	
	Game();
	~Game();
	void init();
	void run();
	void changeStage(GameStage newStage, StageRunnerArg *arg = NULL);
	void returnToPreviousStage();
};

#endif /* INCLUDE_GAME_GAME */
