#include "dog/dogGraphics.h"
#include "../graphics/bodies.h"
#include "SPIFFS.h"
#include "SD.h"
#include "upng.h"

void DogGraphics::getBodyGraphic(BodyType type, uint16_t buffer[]) 
{
  uint16_t *outputBuffer = NULL;
  DogGraphics::decodePNGData(&outputBuffer);

  if(outputBuffer == NULL){
    Serial.println("failed to decode png data");
    return;
  }

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
  
  memcpy(buffer, outputBuffer, bytesToCopy);

  free(outputBuffer);
}

void DogGraphics::decodePNGData(uint16_t **outputBuffer) 
{
  //decompressing a png takes a FAT STACK, so here i made one for it
  TaskHandle_t taskHandle;
  upng_t* upng = NULL;
  xTaskCreate(upngDecodeTask, "upngDecodeTask", 20000, &upng, 1, &taskHandle);
  
  while(eTaskGetState(taskHandle) != eTaskState::eSuspended){
    vTaskDelay(10);
  }

  vTaskDelete(taskHandle);
  
  Serial.print("UPNG 2: "); Serial.println(upng == NULL); 

  if(upng != NULL){

    if (upng_get_error(upng) == UPNG_EOK) {

      upng_s_rgba32b sourcePixel;
      upng_s_rgb16b destPixel;
      uint16_t conversionPixel;

      unsigned int imageWidth = FRAME_WIDTH;
      unsigned int imageHeight = FRAME_HEIGHT;

      *outputBuffer = (uint16_t*)malloc(sizeof(uint16_t) * imageWidth * imageHeight);
      
      Serial.println("Pixel Size: "); Serial.println(upng_get_pixelsize(upng));

      for(unsigned int y = 0; y < imageHeight; y++){
        for(unsigned int x = 0; x < imageWidth; x++){
          upng_GetPixel(&sourcePixel, upng, x, y);
          upng_rgb24bto16b(&destPixel, &sourcePixel.rgb);
          memcpy(&conversionPixel, &destPixel, sizeof(uint16_t));
          (*outputBuffer)[imageWidth * y + x] = conversionPixel;
        }
      }
    }

    upng_free(upng);
  }

}

void DogGraphics::upngDecodeTask(void* _upng) 
{
  upng_t** upng = (upng_t**)_upng;

  *upng = upng_new_from_file("/bodies.png");
  
  if (upng != NULL) {
    upng_decode(*upng);
  }
  Serial.print("UPNG 1: "); Serial.println(*upng == NULL); 

  vTaskSuspend(NULL);
}
