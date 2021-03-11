#include "bmp.h"
#include "SPIFFS.h"

uint16_t rgb888torgb565(uint8_t *rgb888Pixel)
{
    uint8_t red   = rgb888Pixel[0];
    uint8_t green = rgb888Pixel[1];
    uint8_t blue  = rgb888Pixel[2];

    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;

    return (uint16_t) (r | g | b);
}


BMP* bmp_new_from_file(const char* filename) 
{
  File file = SPIFFS.open(filename, FILE_READ);
  if(!file){
    Serial.printf("Failed to open file %s for reading", filename);
    return NULL;
  }

  BMP* bmp = (BMP*)malloc(sizeof(BMP));
  
  file.readBytes(bmp->header.id, 2);
  file.readBytes((char*)&(bmp->header.filesize), 4);
  file.readBytes(bmp->header.reserved, 4);
  file.readBytes((char*)&(bmp->header.dataOffset), 4);
  file.readBytes((char*)&(bmp->header.dibSize), 4);
  file.readBytes((char*)&(bmp->header.width), 4);
  file.readBytes((char*)&(bmp->header.height), 4);
  file.readBytes((char*)&(bmp->header.colorPlanes), 2);
  file.readBytes((char*)&(bmp->header.bitsPerPixel), 2);
  file.readBytes((char*)&(bmp->header.compressionMethod), 4);
  file.readBytes((char*)&(bmp->header.imageSize), 4);
  file.readBytes((char*)&(bmp->header.hozRes), 4);
  file.readBytes((char*)&(bmp->header.vertRes), 4);
  file.readBytes((char*)&(bmp->header.numPaletteColors), 4);
  file.readBytes((char*)&(bmp->header.numImportantColors), 4);

  bmp->palette = (uint32_t*)malloc(bmp->header.numPaletteColors * sizeof(uint32_t));
  file.readBytes((char*)bmp->palette, bmp->header.numPaletteColors * sizeof(uint32_t));

  bmp->rgb565Palette = (uint16_t*)malloc(bmp->header.numPaletteColors * sizeof(uint16_t));
  for(uint16_t c = 0; c < bmp->header.numPaletteColors; c++){
    bmp->rgb565Palette[c] = rgb888torgb565((uint8_t*)&bmp->palette[c]);
  }

  bmp->data = (uint8_t*)malloc(bmp->header.imageSize);
  file.seek(bmp->header.dataOffset);
  //int rowsize = ((bmp->header.bitsPerPixel * bmp->header.width + 31) / 32) * 4;
  
  file.readBytes((char*)bmp->data, bmp->header.imageSize);

  Serial.print("File Size: "); Serial.println(bmp->header.filesize);
  Serial.print("File Offset: "); Serial.println(bmp->header.dataOffset);
  Serial.print("BPP: "); Serial.println(bmp->header.bitsPerPixel);
  Serial.print("DIB Size: "); Serial.println(bmp->header.dibSize);
  Serial.print("CM: "); Serial.println(bmp->header.compressionMethod);
  Serial.print("image Size: "); Serial.println(bmp->header.imageSize);
  Serial.print("# Pal Colors: "); Serial.println(bmp->header.numPaletteColors);
  Serial.print("#! Pal Colors: "); Serial.println(bmp->header.numImportantColors);
  //Serial.print("# Row Size: "); Serial.println(rowsize);

  file.close();

  return bmp;
}

void bmp_free(BMP* bmp) 
{
  if(bmp != NULL){
    free(bmp->rgb565Palette);
    free(bmp->palette);
    free(bmp->data);
  }
  
  free(bmp);
}

uint16_t* bmp_convert_palette_to_image(BMP* bmp) 
{
  uint16_t* buffer = (uint16_t*)malloc(sizeof(uint16_t) * bmp->header.imageSize);
  for(uint16_t c = 0; c < bmp->header.imageSize; c++){
     buffer[c] = bmp->rgb565Palette[bmp->data[c]];
  }
  return buffer;
}
