#ifndef INCLUDE_DOG_DOG
#define INCLUDE_DOG_DOG

#include <string>
#include "TFT_eSPI.h"
#include "geometry.h"

enum BodyType {
  BodyType_Base,
  BodyType_Fluffer,
};

enum TailType {
  TailType_Base,
  TailType_Fluffer,
};

enum HeadType {
  HeadType_Base,
  HeadType_Fluffer,
};

enum EyeType {
  EyeType_Base,
  EyeType_Anime,
};

enum SnoutType {
  SnoutType_Base,
  SnoutType_Thick,
};

enum EarType {
  EarType_Base,
  EarType_Flop,
};

enum NoseType {
  NoseType_Base,
};

struct Ear {
  EarType type;
};

struct Eye {
  EyeType type;
};

struct Nose {
  NoseType type;
};

struct Snout {
  SnoutType type;
  Point<uint8_t> nosePos;
  Nose nose;
};

struct Head {
  HeadType type;

  Ear ear;
  Point<uint8_t> earPos;

  Snout snout;
  Point<uint8_t> snoutPos;

  Eye eye;
  Point<uint8_t> eyePos;
};

struct Tail {
  TailType type;
};

struct Body {
  BodyType type;
  Point<uint8_t> headPos;
  Point<uint8_t> tailPos;

  Head head;
  Tail tail;
};

struct DogAttributes {
  uint16_t color;
  uint16_t patternColor;
  uint8_t size;
  Body body;
};

class Dog
{
public:
  std::string name;
  DogAttributes *attributes;
  uint32_t seed;
  ~Dog();

  static Dog *createDog(uint32_t seed = 0);
  void renderToSprite(TFT_eSprite *sprite);
};


#endif /* INCLUDE_DOG_DOG */
