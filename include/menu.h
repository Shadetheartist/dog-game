#ifndef __MENU_H__
#define __MENU_H__

#include <list>
#include "game/game.h"

typedef void (*MenuCb)(Game*);

class Menu
{
protected:
	unsigned int selectedMenuItem;

public:
	std::list<std::pair<std::string, MenuCb>> menuItems;
	void renderToSprite(TFT_eSprite *sprite);
	void nextItem();
	void previousItem();
};



#endif // __MENU_H__