//#include "Sprite.h"
#include "Actor.h"
#include "Enemy.h"
#include "Collision.h"
#include <vector>

#define FPS 60
using namespace std;

namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image) : MobileComponent(x,y,w,h), startHealth(3), startX(x), startY(y) { //(x+10), (y+10), (x+w-10), (y+h)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
        health = startHealth;
    }

    void Actor::keyDown(const SDL_Event& event) {
        //if(!isOnTopOfPlatform) {
    
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT: 
                movingRight = true;
                break;
            
            case SDLK_LEFT:             
                movingLeft = true;             
                break;

            case SDLK_SPACE:   jump();  break;        
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

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    void Actor::handleCollision(MobileComponent* mc) {
        if(Enemy* e = dynamic_cast<Enemy*>(mc)){
            collisionWithEnemy(e);
        }
        if(Platform* p = dynamic_cast<Platform*>(mc)) {
            collisionWithPlatform(p);
        }
    }

    void Actor::collisionWithPlatform(Platform* p) {
        //cout << "Det funkar!" << endl;
        if(getLowerY() > p->getUpperY() && 
        getLowerY() < p->getLowerY()  && 
        getLeftX() < p->getRightX() &&  
        getRightX() > p->getLeftX()) {

            if(dy > 0) { //moving down on top of platform
                isOnTopOfPlatform = true;  //står på plattform, kan nu hoppa
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
            e->getsInvincible();
        } else if(movingDown && (getLowerY() > e->getUpperY()) && (getLowerY() < e->getLowerY())) { // Kommer ovanifrån
            e->die(); //delete enemy from enemie-list when hurt (temporär lista!) -> inte implementerat ännu!
            dy = -7;
            //setPosition(getLeftX(), e->getUpperY() - getHeight());
        } else if((getRightX() > e->getLeftX()) && (getRightX() < e->getRightX())){ //Om kollision sker med Enemy vänstersida
            hurting();
            setPosition(e->getLeftX() - getWidth(), getUpperY());
            e->getsInvincible();
            hurtByEnemy = true;
        } else if ((getLeftX() < e->getRightX() && (getLeftX() > e->getLeftX()))) {
            hurting();
            setPosition(e->getRightX(), getUpperY());
            e->getsInvincible();
            hurtByEnemy = true;
        } 
    }

    void Actor::hurting() {
        if(invincibility == 0) {
            health--;
            invincibility = 60;
        }
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }


    void Actor::jump(){
        if (!isJumping && isOnTopOfPlatform){ //gör att vi inte kan hoppa i luften
            dy = -20;
            isJumping = true;
            movingUp = true;
        }
    }

    void Actor::handleShake() {
        if (hurtByEnemy)
        {
        timer += FPS;
        if (timer < SHAKE_DURATION)
        {
            int value = 7;
            int randX = (rand() % (value- (-value) + 1)) + (-value);
            int randY = (rand() % (value- (-value) + 1)) + (-value);
            setPosition(getLeftX() + randX, getUpperY() + randY);
        }
        else
        {
            hurtByEnemy = false;
            timer = 0;
        }
        }
    }

    void Actor:: update(){

        if(movingRight){
            dx = xSpeed;                               //dy = 0;
            moveX(xSpeed);
            //movingRight = false;
        }
        if (movingLeft){
            dx = -xSpeed;                                  //dy = 0;
            moveX(-xSpeed);
        }else if (!movingRight && !movingLeft){
            dx = 0;
        }

            
        dy += GRAVITY; //gravity
        if(dy > 10) //limits how fast actor can fall - terminal velocity
            dy = 10;
        moveY(dy); //moving down no matter what, but as update is called before collision check this will be corrected if standing on platform

        if(isJumping){
            if (dx < 0 ){ //moving left
                dx += GRAVITY;
                moveX(dx);
            } 
            else if (dx > 0 ){ //moving right

                dx -= GRAVITY;
                moveX(dx);
            }
        
        } 
                 // resetting dx in between input, if not jumping. Other solution - keyup?? Probably better...?
        //}
        isOnTopOfPlatform = false; //reset
        movingUp = false;
        movingDown = true;
        if (health <= 0){
            dead = true;
        }
        if(invincibility > 0) {
            invincibility--;
        }

        handleShake();

    }

    

    void Actor:: reset(){
        setPosition(startX, startY);
        dx = 0;
        dy = 0;
        dead = false;
        health = startHealth;
    }


    void Actor:: draw() const {
        // if (isFacingRight)
		// 	SDL_RenderCopy(sys.get_ren(), downIcon, NULL, &getRect());
		// else
		// 	SDL_RenderCopy(sys.get_ren(), upIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

}