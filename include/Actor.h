#ifndef ACTOR_H
#define ACTOR_H

#include "Sprite.h"

class Actor:public Sprite {
  public:
  Actor(int x, int y, std::string image) ;
  //using Sprite::Sprite;
  void jump(int hight);
  
  private:
  //bool canBeControlledByPlayer;
};

#endif