#ifndef GUBBE_H
#define GUBBE_H
#include "Sprite.h"

class Gubbe:public Sprite {
  public:
  using Sprite::Sprite;
  void jump(int hight);
  
  private:

};

#endif