//#include "Sprite.h"
#include "Actor.h"

using namespace std;

namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image) : MobileComponent(x,y,w,h) { //(x+10), (y+10), (x+w-10), (y+h)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
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
                //old_dxVel = dxVel;
                movingRight = false;
            case SDLK_LEFT: 
                //old_dxVel = dxVel;
                movingLeft = false;


        }
    }

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    void Actor::collisionWithPlatform(Platform* p, char collisionCode) {
        
        //cout << "Det funkar!" << endl;
        if(collisionCode == 't') { //moving down on top of platform
            isOnTopOfPlatform = true;  //står på plattform, kan nu hoppa
            movingDown = false;
            dyVel = 0;
            isJumping = false;
            setPosition(getLeftX(), p->getUpperY() - getHeight());
        }
        else if(collisionCode == 'l') { //moving right into left side of platform
            // cout << "UpperY innan " << getUpperY() << endl;
            // cout << "UpperY platform innan " << p->getUpperY() << endl;

            setPosition(p->getLeftX() - getWidth(), getUpperY());

            // cout << "UpperY efter " << getUpperY() << endl;
            // cout << "UpperY platform efter " << p->getUpperY() << endl;
        }
        else if(collisionCode == 'r') { //moving left into right side of platform
            setPosition(p->getRightX(), getUpperY());
        }
        
        // else if(dyVel < 0) {//moving up under platform
        //     setPosition(getLeftX(), (p->getLowerY()));
        // }
        

        //this->setPosition(0,0);
        //x, y
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
        else if (movingLeft){
            dxVel = -speed;                                  //dyVel = 0;
            moveX(-speed);
        }else if (!movingRight || !movingLeft){
            dxVel = 0;
        }

            
            dyVel += GRAVITY; //gravity
            if(dyVel > 10) //limits how fast actor can fall - terminal velocity
                dyVel = 10;
            moveY(dyVel); //moving down no matter what, but as update is called before collision check this will be corrected if standing on platform
             
            if(isJumping){
                //dxVel = old_dxVel;
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
    }


    void Actor:: draw() const {
        // if (isFacingRight)
		// 	SDL_RenderCopy(sys.get_ren(), downIcon, NULL, &getRect());
		// else
		// 	SDL_RenderCopy(sys.get_ren(), upIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

}