#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../graphics/splash-image.h"

struct Graphic
{
	int width, height;
	const unsigned short *data;
};

const Graphic GRAPHIC_SPLASH_IMG = Graphic{240, 135, GRAPHICS_SPLASH_IMG_DATA};

#endif