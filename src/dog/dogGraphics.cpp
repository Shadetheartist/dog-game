#include "dog/dogGraphics.h"
#include "SD.h"
#include "bmp.h"

uint16_t* DogGraphics::getGraphic(BodyType type) 
{
  BMP* bmp = bmp_new_from_file("/test-dog2.bmp");  
  
  uint16_t *buffer = bmp_convert_palette_to_image(bmp);

  if(bmp != NULL){
    bmp_free(bmp);
  }

  return buffer;
}
