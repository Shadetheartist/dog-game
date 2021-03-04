#include "dog/dogGraphics.h"
#include "../graphics/bodies.h"

void DogGraphics::getBodyGraphic(BodyType type, uint16_t buffer[]) 
{
  uint16_t bytesToCopy = FRAME_HEIGHT * FRAME_WIDTH * sizeof(uint16_t);

  uint16_t frame = 0;
  switch(type){
    case BodyType_Base: 
      frame = 0;
      break;
    case BodyType_Fluffer: 
      frame = 1;
      break;
  }

  uint16_t startingPoint = bytesToCopy * frame / sizeof(uint16_t);
  
  memcpy(buffer, GRAPHICS_DOG_BODIES + startingPoint, bytesToCopy);
}
