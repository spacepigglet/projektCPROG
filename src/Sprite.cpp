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

int Sprite::getX() {return gx;}

int Sprite::getY() {return gy;}