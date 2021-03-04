#include "dog/dog.h"
#include <random>
#include "esp_system.h"
#include "dog/dogGraphics.h"

extern "C" {
  #include "bootloader_random.h"
}



Dog::~Dog() 
{
  delete attributes;
}


static std::string generateRandomName(){
  uint8_t r = esp_random() % 4;

  switch (r)
  {
    case 0: return "Lil Jef";
    case 1: return "Big Jef";
    case 3: return "Namejef";
    default: return "Jef";
  }
}

Dog *Dog::createDog(uint32_t seed) 
{
  Dog* dog = new Dog();

  //if seed is not specified, create a new one using the base entroy source.
  if(seed == 0){
    bootloader_random_enable();
    seed = esp_random();
    bootloader_random_disable(); 
  }

  srand(seed);

  dog->seed = seed;
  dog->name = generateRandomName();
  dog->attributes = new DogAttributes();
  dog->attributes->body = Body();
  dog->attributes->body.type = BodyType_Base;

  dog->attributes->body.head = Head();
  dog->attributes->body.head.type = HeadType_Base;
  
  dog->attributes->body.tail = Tail();

  return dog;
}

void Dog::renderToSprite(TFT_eSprite *sprite) 
{
  sprite->fillSprite(TFT_WHITE);
	sprite->setCursor(1, 1, 1);
	sprite->setTextColor(TFT_BLACK);
  sprite->drawString(name.c_str(), 0, 0, 2);

  uint16_t buffer[FRAME_HEIGHT * FRAME_WIDTH];
  DogGraphics::getBodyGraphic(BodyType_Fluffer, buffer);

  sprite->pushImage(0, 0, FRAME_WIDTH, FRAME_HEIGHT, buffer);
}

