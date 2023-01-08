#ifndef ENEMY_H
#define ENEMY_H

#include "Collision.h"
#include "MobileComponent.h"
#include "Platform.h"

namespace tower {
class Enemy : public MobileComponent {
  public:
  ~Enemy();
  static Enemy* getInstance(int x, int y, int w, int h, std::string image, Platform*);
  void update();
  void draw() const;
  void addOnPlatform(Platform*);
  void die();
  void getsInvincible();

  bool isAlive() {return alive;}
 // void handleCollision(MobileComponent*);
  
  //void collisionWithPlayer(Actor*);

  protected:
  Enemy(int x, int y, int w, int h, std::string image, Platform*);

  private:
  void dying();
  Platform* platform;
  SDL_Texture* texture;
  int enemySpeed = 1;
  int enemyDirection = 1;
  bool alive = true;
  bool isDying = false;
  bool isInvincible = false;
  int timer = 0;
  bool canGetHurt = true;
  const int INVINCIBLE_DURATION = 2000;
};

}
#endif