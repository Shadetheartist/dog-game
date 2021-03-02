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
	SplashScreen,
	MainMenu,
	Doghouse
};

class StageRunner;

class Game
{
public:
	GameState state;
	GameStage stage;
	Display *display;
	StageRunner *stageRunner;

	Game();
	~Game();
	void init();
	void run();
	void changeStage(GameStage newStage);
};

#endif /* INCLUDE_GAME_GAME */
