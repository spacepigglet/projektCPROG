#ifndef ENEMY_H
#define ENEMY_H

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
  void getsHurt();

  protected:
  Enemy(int x, int y, int w, int h, std::string image, Platform*);
  private:

  private:
  Platform* platform;
  SDL_Texture* texture;
  int enemySpeed = 1;
  int enemyDirection = 1;
  bool isAlive = true;
};

}
#endif