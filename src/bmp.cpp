#include "bmp.h"
#include "SPIFFS.h"
#include "TFT_eSPI.h"

uint16_t rgb888torgb565(uint8_t *rgb888Pixel)
{
    uint8_t r = rgb888Pixel[2];
    uint8_t g = rgb888Pixel[1];
    uint8_t b  = rgb888Pixel[0];
    uint8_t a  = rgb888Pixel[3];

    if(r+g+b > 0){
      Serial.print("R:");Serial.println(r);
      Serial.print("G:");Serial.println(g);
      Serial.print("B:");Serial.println(b);
      Serial.print("A:");Serial.println(a);
      Serial.println(a);
    }

    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);;
}

//flips the bmp data vertically, as i probably can't read the file image data from the bottom up easily. 
void flipImageData(BMP *bmp)
{
  Serial.println("flipping image data");

  uint32_t rowSize = bmp->header.width;
  uint16_t row1 = 0, row2 = bmp->header.height - 1;
  uint8_t swap;
  while(row2 - row1 > 1){
    uint32_t row1Offset = row1 * rowSize;
    uint32_t row2Offset = row2 * rowSize;

    for(uint16_t i = 0; i < rowSize; i++){
      swap = bmp->data[i + row1Offset];
      bmp->data[i + row1Offset] = bmp->data[i + row2Offset];
      bmp->data[i + row2Offset] = swap;
    }
    
    row1++;
    row2--;
  }
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
  int rowsize = ((bmp->header.bitsPerPixel * bmp->header.width + 31) / 32) * 4;
  file.readBytes((char*)bmp->data, bmp->header.imageSize);

  flipImageData(bmp);

  Serial.print("File Size: "); Serial.println(bmp->header.filesize);
  Serial.print("File Offset: "); Serial.println(bmp->header.dataOffset);
  Serial.print("BPP: "); Serial.println(bmp->header.bitsPerPixel);
  Serial.print("DIB Size: "); Serial.println(bmp->header.dibSize);
  Serial.print("CM: "); Serial.println(bmp->header.compressionMethod);
  Serial.print("image Size: "); Serial.println(bmp->header.imageSize);
  Serial.print("width: "); Serial.println(bmp->header.width);
  Serial.print("height: "); Serial.println(bmp->header.height);
  Serial.print("# Pal Colors: "); Serial.println(bmp->header.numPaletteColors);
  Serial.print("#! Pal Colors: "); Serial.println(bmp->header.numImportantColors);
  Serial.print("Row Size: "); Serial.println(rowsize);

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
