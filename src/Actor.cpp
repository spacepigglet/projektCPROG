#include "Actor.h"
#include <vector>

using namespace std;
namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image, int no_lives) : Component(x,y,w,h, true), startHealth(no_lives), startX(x), startY(y) { //(x+10), (y+10), (x+w-10), (y+h)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + image).c_str() );
        health = startHealth;
    }

    Actor::Actor(int x, int y, int w, int h, std::string image, int no_lives, bool scrollable) : Component(x,y,w,h, scrollable), startHealth(no_lives), startX(x), startY(y) { //(x+10), (y+10), (x+w-10), (y+h)
        texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + image).c_str() );
        health = startHealth;
    }

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image, int no_lives) {
        return new Actor(x, y, w, h, image, no_lives, true);
    }

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image, int no_lives, bool scrollable) {
        return new Actor(x, y, w, h, image, scrollable);
    }

    void Actor::keyDown(const SDL_Event& event) {
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT: 
                movingRight = true;
                break;
            case SDLK_LEFT:             
                movingLeft = true;             
                break;
            case SDLK_SPACE:   
                jump();  
                break;
        }
    }

    void Actor::keyUp(const SDL_Event& event) {
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT: 
                movingRight = false;
            case SDLK_LEFT: 
                movingLeft = false;
        }
    }

    void Actor::handleCollision(Component* c) {
        if(Enemy* e = dynamic_cast<Enemy*>(c)){
            collisionWithEnemy(e);
        }
        if(Platform* p = dynamic_cast<Platform*>(c)) {
            collisionWithPlatform(p);
        }
    }

    void Actor::collisionWithPlatform(Platform* p) {
        if(getLowerY() > p->getUpperY() && getLowerY() < p->getLowerY()  && 
        getLeftX() < p->getRightX() && getRightX() > p->getLeftX()) {
            if(dy > 0) { //moving down on top of platform
                isOnTopOfPlatform = true;  //standing on platform, can jump now
                movingDown = false;
                dy = 0;
                isJumping = false;
                setPosition(getLeftX(), p->getUpperY() - getHeight());
            }
        }
    }

    void Actor::collisionWithEnemy(Enemy* e) {
         if(movingUp) {
            hurting();
        } else if(movingDown && (getLowerY() > e->getUpperY()) && (getLowerY() < e->getLowerY())) { //coming from above
            e->die();
            dy = -7;
        } else if((getRightX() > e->getLeftX()) && (getRightX() < e->getRightX())){ //collision with enemy left side
            hurting();
            setPosition(e->getLeftX() - getWidth(), getUpperY());
        } else if ((getLeftX() < e->getRightX() && (getLeftX() > e->getLeftX()))) {
            hurting();
            setPosition(e->getRightX(), getUpperY());
        } 
    }

    void Actor::hurting() {
        if(invincibility == 0) {
            health--;
            invincibility = 60; //can't get hur again for another 60 ticks
        }
    }

    void Actor::jump(){
        if (!isJumping && isOnTopOfPlatform){ //can't jump when in air
            dy = -20;
            isJumping = true;
        }
    }

    void Actor:: update(){
        if(movingRight){
            dx = speed; 
            moveX(speed);
        }
        if (movingLeft){
            dx = -speed;
            moveX(-speed);
        }else if (!movingRight && !movingLeft){
            dx = 0;
        }
            
        dy += GRAVITY; //gravity
        if(dy > 10) { //limits how fast actor can fall - terminal velocity
            dy = 10;
        }
            moveY(dy); //moving down no matter what, but as update is called before collision check this will be corrected if standing on platform

        isOnTopOfPlatform = false; //reset
        movingDown = true;
        
        if (health <= 0){
            dead = true;
        }

        if(invincibility > 0) {
            invincibility--;
        }
    }

    void Actor:: reset() {
        setPosition(startX, startY);
        speed = 8;
        dx = 0;
        dy = 0;
        dead = false;
        health = startHealth;
    }


    void Actor:: draw() const {
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }

}