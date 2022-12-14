#include "Enemy.h"
namespace tower {

Enemy::Enemy(int x, int y, int w, int h, std::string image, Platform* p) : MobileComponent(x,y,w,h) { // x, y, (x+w), (y+h+1)
texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
platform = p;
}

Enemy* Enemy::getInstance(int x, int y, int w, int h, std::string image, Platform* p){
    return new Enemy(x, y, w, h, image, p);
}

void Enemy::draw() const{
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

  if(getRightX() < 0 || getUpperY() > WINDOW_HEIGHT - getHeight()) { //Om enemy = utanför skärm
    alive = false;
  }
}

void Enemy::die() {
  //std::vector<Enemy*> 
  //rect.h--; rect.w--; //impoderar
  isDying = true;
}

void Enemy::dying() {
  rect.h -= 5;
  setPosition(getLeftX(), getUpperY() + 5);
  if(rect.h == 0 || rect.w == 0) {
    alive = false;
  }
}

/*void Enemy::handleCollision(MobileComponent* mc) {
  if(Actor* a = dynamic_cast<Actor*>(mc)) {
    collisionWithPlayer(a);
  }
}

void Enemy::collisionWithPlayer(Actor* a) {
  if(a->isMovingDown()) {
    rect.h--; rect.w--;
  }
  if(rect.h == 0 || rect.w == 0) {
    alive = false;
  }

}*/


void Enemy::addOnPlatform(Platform* p) {
  setPosition(p->getLeftX(), p->getUpperY());
}


Enemy:: ~Enemy(){
    SDL_DestroyTexture(texture);
}

}
