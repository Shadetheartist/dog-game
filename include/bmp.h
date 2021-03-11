#ifndef __BMP_H__
#define __BMP_H__
#include "stdint.h"

#define BMP_TRANSPARENCY_INDEX 0x20

typedef struct _BMPHeader
{
  char id[2];
  uint32_t filesize;
  char reserved[4];
  uint32_t dataOffset;

  uint32_t dibSize;
  uint32_t width;
  uint32_t height;
  uint16_t colorPlanes;
  uint16_t bitsPerPixel;
  uint32_t compressionMethod;
  uint32_t imageSize;
  uint32_t hozRes;
  uint32_t vertRes;
  uint32_t numPaletteColors;
  uint32_t numImportantColors;


} BMPHeader;

typedef struct _BMP 
{
  BMPHeader header;
  uint32_t* palette;
  uint16_t* rgb565Palette;
  uint8_t* data;
} BMP;

BMP* bmp_new_from_file(const char* filename);
void bmp_free(BMP* bmp);
uint16_t* bmp_convert_palette_to_image(BMP* bmp);

#endif // __BMP_H__