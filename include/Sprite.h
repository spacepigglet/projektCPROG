#ifndef SPRITE_H
#define SPRITE_H
#include <string>

class Sprite {
  
  public:
  Sprite(int x, int y, std::string image); //ta in sökvägen till bild
  void moveUp(int steg = 1);
  void moveDown(int steg = 1);
  void moveRight(int steg = 1);
  void moveLeft(int steg = 1);
  int getX();
  int getY();

  private:
  std::string image;
  int gx;
  int gy;

};

#endif