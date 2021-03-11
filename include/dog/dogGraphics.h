#ifndef __DOGGRAPHICS_H__
#define __DOGGRAPHICS_H__

#include "dog/dog.h"

#define NUM_DOG_TYPES 2
#define FRAME_WIDTH 56
#define FRAME_HEIGHT 40

class DogGraphics
{
	public:
	static uint16_t* getGraphic(BodyType type);
	//static void getTailGraphic(TailType type, uint16_t buffer[]);
	//static void getHeadGraphic(HeadType type, uint16_t buffer[]);
	//static void getSnoutGraphic(SnoutType type, uint16_t buffer[]);
	//static void getNoseGraphic(NoseType type, uint16_t buffer[]);
	//static void getEyesGraphic(EyeType type, uint16_t buffer[]);
	//static void getEarsGraphic(EarType type, uint16_t buffer[]);
};

#endif // __DOGGRAPHICS_H__