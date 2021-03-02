#ifndef __STAGERUNNER_H__
#define __STAGERUNNER_H__

#include "game.h"

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
};





#endif // __STAGERUNNER_H__