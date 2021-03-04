#include "menu.h"

void Menu::renderToSprite(TFT_eSprite *sprite) 
{
	sprite->fillSprite(TFT_LIGHTGREY);
	sprite->setCursor(1, 1, 1);
	sprite->setTextColor(TFT_BLACK);

	int line = 0;
	int lineDist = 15;
	for(std::list<std::pair<std::string, MenuCb>>::iterator it = menuItems.begin(); it != menuItems.end(); it++){
		if(line == selectedMenuItem){
			sprite->drawCircle(5, lineDist/2 + 1 + lineDist*selectedMenuItem, 3, TFT_BLACK);
			sprite->fillCircle(5, lineDist/2 + 1 + lineDist*selectedMenuItem, 2, TFT_YELLOW);
		}
		sprite->drawString((*it).first.c_str(), 12, 1 + lineDist*line, 2);
		line++;
	}
}

void Menu::nextItem() 
{
	selectedMenuItem++;
	if(selectedMenuItem >= menuItems.size()){
		selectedMenuItem = 0;
	}
}

void Menu::previousItem() 
{
	selectedMenuItem--;
	if(selectedMenuItem < 0){
		selectedMenuItem = menuItems.size()-1;
	}
}
