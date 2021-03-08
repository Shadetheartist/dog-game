#include "dog/dogGraphics.h"
#include "SPIFFS.h"
#include "SD.h"
#include "upng.h"

void DogGraphics::getBodyGraphic(BodyType type, uint16_t buffer[]) 
{
  uint16_t *outputBuffer = NULL;
  DogGraphics::decodePNGData(&outputBuffer, "/bodies.png");

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

  uint16_t startingPoint = (bytesToCopy * frame) / sizeof(uint16_t);
  Serial.print("Starting Point: "); Serial.println(startingPoint);
  Serial.print("Bytes To Copy: "); Serial.println(bytesToCopy);
  
  memcpy(buffer, outputBuffer + startingPoint, bytesToCopy);

  free(outputBuffer);
}

void DogGraphics::decodePNGData(uint16_t **outputBuffer, const char* path) 
{
  Serial.print("Decoding PNG: "); Serial.println(path);

  //decompressing a png takes a FAT STACK, so here i made one for it
  TaskHandle_t taskHandle;
  upng_t* upng = NULL;

  std::pair<const char*, upng_t**> pair = std::pair<const char*, upng_t**>(path, &upng);
  xTaskCreate(upngDecodeTask, "upngDecodeTask", 12000, &pair, 1, &taskHandle);
  
  while(eTaskGetState(taskHandle) != eTaskState::eSuspended){
    vTaskDelay(10);
  }

  vTaskDelete(taskHandle);

  if(upng != NULL){

    if (upng_get_error(upng) == UPNG_EOK) {

      upng_s_rgba32b sourcePixel;
      upng_s_rgb16b destPixel;
      uint16_t conversionPixel;

      unsigned int imageWidth = upng_get_width(upng);
      unsigned int imageHeight = upng_get_height(upng);

      *outputBuffer = (uint16_t*)malloc(sizeof(uint16_t) * imageWidth * imageHeight);

      for(unsigned int y = 0; y < imageHeight; y++){
        for(unsigned int x = 0; x < imageWidth; x++){
          upng_GetPixel(&sourcePixel, upng, x, y);
          upng_rgb24bto16b(&destPixel, &sourcePixel.rgb);
          memcpy(&conversionPixel, &destPixel, sizeof(uint16_t));
          (*outputBuffer)[imageWidth * y + x] = conversionPixel;
        }
      }
    }
    else{
      Serial.print("Decode Failure Code: "); Serial.println(upng_get_error(upng));
      Serial.print("Line: "); Serial.println(upng_get_error_line(upng));
    }

    upng_free(upng);
  }
}

void DogGraphics::upngDecodeTask(void* _pair) 
{
  std::pair<const char*, upng_t**> *pair = (std::pair<const char*, upng_t**>*)_pair;

  upng_t** upng = pair->second;
  *upng = upng_new_from_file(pair->first);
  
  if (upng != NULL) {
    upng_decode(*upng);
  }
  Serial.print("UPNG 1: "); Serial.println(*upng == NULL); 

  vTaskSuspend(NULL);
}
