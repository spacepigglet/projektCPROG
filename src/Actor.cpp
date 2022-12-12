//#include "Sprite.h"
#include "Actor.h"
#include <iostream>
#include <string>
#include "Component.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include <vector>
#include "Platform.h"
#include "Session.h"
#include "Collision.h"
using namespace std;

namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image) : Component(x,y,w,h) { //(x+10), (y+10), (x+w-10), (y+h)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    void Actor::keyDown(const SDL_Event& event) {
        //if(!isOnTopOfPlatform) {
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT: 
                dxVel = speed;                               //dyVel = 0;
                moveX(speed); break;
            case SDLK_LEFT: 
                dxVel = -speed;                                  //dyVel = 0;
                moveX(-speed);
                break;
            case SDLK_UP: 
                moveUp(speed); 
                dyVel = -1; 
                dxVel = 0;
                break;
            case SDLK_DOWN:
                moveDown(speed); 
                dyVel = 1; 
                dxVel = 0;
                break;

            case SDLK_SPACE:  jump();  break;                 //jump(); break; dxVel = 0;dyVel = 0;
        }
        //}

    //collisionDetection(getComps());
}

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    void Actor::collisionWithPlatform(Platform* p) {
        
        //cout << "Det funkar!" << endl;
        if(dyVel > 0) { //moving down on top of platform
            //isOnTopOfPlatform = true; 
            dyVel = 0;
            isJumping = false;
            setPosition(getLeftX(), p->getUpperY() - getHight());
        }
        else if(dxVel > 0) { //moving right into left side of platform
            cout << "UpperY innan " << getUpperY() << endl;
            cout << "UpperY platform innan " << p->getUpperY() << endl;

            setPosition(p->getLeftX() - getWidth(), getUpperY());

            cout << "UpperY efter " << getUpperY() << endl;
            cout << "UpperY platform efter " << p->getUpperY() << endl;
        }
        else if(dxVel < 0) { //moving left into right side of platform
            setPosition(p->getRightX(), getUpperY());
        }
        
        else if(dyVel < 0) {//moving up under platform
            setPosition(getLeftX(), (p->getLowerY()));
        }
        

        
        //this->setPosition(0,0);
        //x, y
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }

    bool Actor::handleCollisionWithPlatform(Platform* other)const{ //, char c
        cout << "Collision" << endl;
        // switch(c){
        //     case 'l': //check left
        //     case 'r': //check right

        // }
        return false;
    }


    void Actor::collisionDetection(Component* other) {
        if(other == this) {
            return;
        }
        if(leftX < other->getRightX() && rightX > other->getLeftX() 
        && upperY < other-> getLowerY() && lowerY > other->getUpperY()){
        //collision happened
            if(Platform *p = dynamic_cast <Platform*>(other)) {
                handleCollisionWithPlatform(p);
            }
        }
    }


    // void Actor::jump(){
    //     isJumping = true;
    //     //SDL_Rect rect = getRect();
    //     int originalheight = getRect().y;
    //     int targetHeight = originalheight - 100;
    //     //while (isJumping){
    //         while(getRect().y > targetHeight){
    //         moveUp(10);
    //         SDL_RenderClear(sys.get_ren());
	// 		SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
    //         draw();
    //         SDL_RenderPresent(sys.get_ren());
    //         }

    //         while(getRect().y < originalheight){
    //         moveDown(10);
    //         SDL_RenderClear(sys.get_ren());
	// 		SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
    //         draw();
    //         SDL_RenderPresent(sys.get_ren());
    //         }
    //     //}
    //     isJumping = false;
    // }

    void Actor::jump(){
        if (!isJumping){
            dyVel = -20;
            isJumping = true;
        }
        
    }

    void Actor:: update(){
        //if (isJumping){
                //jump();
            //     dyVel += GRAVITY; //gravity

            //     //move jumper
            //     moveY(dyVel);
        //} 
        //if(!isOnTopOfPlatform){
            
            dyVel += GRAVITY; //gravity
            if(dyVel > 10) //limits how fast actor can fall
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
        //}
        //isOnTopOfPlatform = false; //reset
    }


    void Actor:: draw() const {
        // if (isFacingRight)
		// 	SDL_RenderCopy(sys.get_ren(), downIcon, NULL, &getRect());
		// else
		// 	SDL_RenderCopy(sys.get_ren(), upIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

}