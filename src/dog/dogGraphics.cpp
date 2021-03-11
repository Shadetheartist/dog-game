#include "dog/dogGraphics.h"
#include "SPIFFS.h"
#include "SD.h"

void DogGraphics::getGraphic(BodyType type, uint16_t buffer[]) 
{
  File file = SPIFFS.open("/bodies.bmp", FILE_READ);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }


}
