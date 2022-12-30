//#include "Sprite.h"
#include "Actor.h"
#include "Enemy.h"

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

    void Actor::collisionWithPlatform(Platform* p) {
        //cout << "Det funkar!" << endl;
        if(getLowerY() > p->getUpperY() && 
        getLowerY() < p->getLowerY()  && 
        getLeftX() < p->getRightX() &&  
        getRightX() > p->getLeftX()) {

            if(dyVel > 0) { //moving down on top of platform
                isOnTopOfPlatform = true;  //står på plattform, kan nu hoppa
                movingDown = false;
                dyVel = 0;
                isJumping = false;
                setPosition(getLeftX(), p->getUpperY() - getHeight());
            }
        }
    }

    void Actor::collisionWithEnemy(Enemy* e) {
        if(dyVel > 0) {
            e->getsHurt(); //delete enemy from enemie-list when hurt (temporär lista!) -> inte implementerat ännu!
            //setPosition(getLeftX(), e->getUpperY() - getHeight());
        }
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }


    void Actor::jump(){
        if (!isJumping && isOnTopOfPlatform){ //gör att vi inte kan hoppa i luften
            dyVel = -20;
            isJumping = true;
        }
    }

    void Actor:: update(){

        if(movingRight){
            dxVel = speed;                               //dyVel = 0;
            moveX(speed);
            //movingRight = false;
        }
        if (movingLeft){
            dxVel = -speed;                                  //dyVel = 0;
            moveX(-speed);
        }else if (!movingRight && !movingLeft){
            dxVel = 0;
        }

            
            dyVel += GRAVITY; //gravity
            if(dyVel > 10) //limits how fast actor can fall - terminal velocity
                dyVel = 10;
            moveY(dyVel); //moving down no matter what, but as update is called before collision check this will be corrected if standing on platform

            if(isJumping){
    
                if (dxVel < 0 ){ //moving left
                    dxVel += GRAVITY;
                    moveX(dxVel);
                } 
                else if (dxVel > 0 ){ //moving right

                    dxVel -= GRAVITY;
                    moveX(dxVel);
                }
            
            } 
                 // resetting dxVel in between input, if not jumping. Other solution - keyup?? Probably better...?
        //}
        isOnTopOfPlatform = false; //reset
        movingDown = true;
        if (health <= 0){
            dead = true;
        }
    }

    void Actor:: reset(){
        setPosition(startX, startY);
        dxVel = 0;
        dyVel = 0;
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