#include "Enemy.h"
namespace tower {

Enemy::Enemy(int x, int y, int w, int h, std::string image, Platform* p, bool scrollable): Component(x,y,w,h, scrollable) { // x, y, (x+w), (y+h+1)
  texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
  platform = p;
}

Enemy::Enemy(int x, int y, int w, int h, std::string image, Platform* p) : Component(x,y,w,h) { // x, y, (x+w), (y+h+1)
  texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
  platform = p;
}

Enemy* Enemy::getInstance(int x, int y, int w, int h, std::string image, Platform* p, bool scrollable){
  return new Enemy(x, y, w, h, image, p, scrollable);
}

Enemy* Enemy::getInstance(int x, int y, int w, int h, std::string image, Platform* p){
  return new Enemy(x, y, w, h, image, p, true);
}

void Enemy::draw() const {
  SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
}

void Enemy::update() {
  if(isDying) {
    dying();
    return;
  } 
  rect.x += enemySpeed * enemyDirection;

  if (rect.x < platform->getLeftX() || (rect.x + rect.w) > platform->getRightX()) {
    enemyDirection *= -1;
  }

  if(getRightX() < 0 || getUpperY() > WINDOW_HEIGHT - getHeight()) { //if enemy is outside screen
    alive = false;
  }
}

void Enemy::die() {
  isDying = true;
}

void Enemy::dying() {
  rect.h -= 5;
  setPosition(getLeftX(), getUpperY() + 5);
  if(rect.h == 0 || rect.w == 0) {
    alive = false;
  }
}


Enemy:: ~Enemy(){
  SDL_DestroyTexture(texture);
}

}
