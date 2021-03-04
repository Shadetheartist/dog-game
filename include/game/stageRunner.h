#ifndef __STAGERUNNER_H__
#define __STAGERUNNER_H__

#include "game.h"
#include "menu.h"
#include "dog/dog.h"


class StageRunnerArg {
	public:
		~StageRunnerArg() {};
};

class StageRunner {
	public:
		Game* game;
		StageRunner(Game* game);
		virtual ~StageRunner() {};
		virtual void begin() = 0;
		virtual void run() = 0;
		virtual void end() = 0;
};


class SplashStageRunner : public StageRunner {
	public:
		SplashStageRunner(Game* game);
		~SplashStageRunner();
		void begin();
		void run();
		void end();
};


class MainMenuStageRunner : public StageRunner {
	public:
		MainMenuStageRunner(Game* game);
		~MainMenuStageRunner();
		void begin();
		void run();
		void end();

		Menu* menu;
};


class ViewDogStageRunnerArg : public StageRunnerArg {
	public: 
		Dog* dog;
};


class ViewDogStageRunner : public StageRunner {
	public:
		ViewDogStageRunner(Game* game, ViewDogStageRunnerArg *arg);
		~ViewDogStageRunner();
		void begin();
		void run();
		void end();
		ViewDogStageRunnerArg *arg;
};



#endif // __STAGERUNNER_H__