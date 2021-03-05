#ifndef __DOGGRAPHICS_H__
#define __DOGGRAPHICS_H__

#include "dog/dog.h"
#include "graphics.h"

#define NUM_DOG_TYPES 2
#define FRAME_WIDTH 54
#define FRAME_HEIGHT 40

class DogGraphics
{
	protected:
	static void upngDecodeTask(void*);
	static void decodePNGData(uint16_t **outputBuffer);
	public:
	static void getBodyGraphic(BodyType type, uint16_t buffer[]);
	static void getTailGraphic(TailType type, uint16_t buffer[]);
	static void getHeadGraphic(HeadType type, uint16_t buffer[]);
	static void getSnoutGraphic(SnoutType type, uint16_t buffer[]);
	static void getNoseGraphic(NoseType type, uint16_t buffer[]);
	static void getEyesGraphic(EyeType type, uint16_t buffer[]);
	static void getEarsGraphic(EarType type, uint16_t buffer[]);
};

#endif // __DOGGRAPHICS_H__