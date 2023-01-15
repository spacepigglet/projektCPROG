#include "Sprite.h"
#include <string>
using namespace std;

Sprite::Sprite(int x, int y, string imagePath) { //width, height for scaling
  gx = x;
  gy = y;
  image = imagePath;
}

void Sprite::moveUp(int steg) {
}

void Sprite::moveDown(int steg) {
}

void Sprite::moveRight(int steg) {
}

void Sprite::moveLeft(int steg) {
}

const int Sprite::getX() const {return gx;}

const int Sprite::getY() const {return gy;}