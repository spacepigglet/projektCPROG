#ifndef ENEMY_H
#define ENEMY_H

#include "Collision.h"
#include "Component.h"
#include "Platform.h"

namespace tower {
class Enemy : public Component {
  public:
    ~Enemy();
    static Enemy* getInstance(int x, int y, int w, int h, std::string image, Platform*);
    static Enemy* getInstance(int x, int y, int w, int h, std::string image, Platform*, bool scrollable);
    void update();
    void draw() const;
    void addOnPlatform(Platform*);
    void die();
    bool isAlive() {return alive;}

  protected:
    Enemy(int x, int y, int w, int h, std::string image, Platform*);
    Enemy(int x, int y, int w, int h, std::string image, Platform*, bool scrollable);

  private:
    void dying();
    Platform* platform;
    SDL_Texture* texture;
    int enemySpeed = 1;
    int enemyDirection = 1;
    bool alive = true;
    bool isDying = false;
};

}
#endif