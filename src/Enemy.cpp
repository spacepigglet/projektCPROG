#include "Enemy.h"
#include "Collision.h"
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
  rect.x += enemySpeed * enemyDirection;

  if (rect.x < platform->getLeftX() || (rect.x + rect.w) > platform->getRightX()) {
    enemyDirection *= -1;
  }

  if(getRightX() < 0 || getUpperY() > WINDOW_HEIGHT - getHeight()) { //Om enemy = utanför skärm
    isAlive = false;
  }
}

void Enemy::getsHurt() {
  //std::vector<Enemy*> 
  //rect.h--; rect.w--; //impoderar
  isAlive = false; //lägger till Enemy i removedComps i Session! //Enemy borde inte ha tillgång till Session... 
  //Kan lösa ex genom en bool isDead. I Session kan listan av enemies gås igenom och om isDead så remove.
  //std::cout << "Lägger till i remove" << std::endl; -> FUNKAR!
}

void Enemy::addOnPlatform(Platform* p) {
  setPosition(p->getLeftX(), p->getUpperY());
}

}

Enemy:: ~Enemy(){
    SDL_DestroyTexture(texture);
}
