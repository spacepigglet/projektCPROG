#include "Actor.h"
//#include "Sprite.h"
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
    Actor::Actor(int x, int y, int w, int h, std::string image) : Component(x,y,w,h, (x+10), (y+10), (x+w-10), (y+h)) {
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    void Actor::keyDown(const SDL_Event& event) {
        
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT:
            moveRight(speed); ; break;
            case SDLK_LEFT: moveLeft(speed); 
            break;
            case SDLK_UP: moveUp(speed); break;
            case SDLK_DOWN:moveDown(speed); 
            break;
            case SDLK_SPACE: jump(); break;
        }

    //collisionDetection(getComps());
}

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    void Actor::collisionWithPlatform(Platform* p) {
        this->setPosition(0,0);
        //x, y
    }

    //Ugly solution... changed getRect() från const -> not const... 
    void Actor::setPosition(int x, int y) {
        this->changeRect().x = x;
        this->changeRect().y = y;
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


    void Actor::jump(){
        isJumping = true;
        //SDL_Rect rect = getRect();
        int originalheight = getRect().y;
        int targetHeight = originalheight - 100;
        //while (isJumping){
            while(getRect().y > targetHeight){
            moveUp(10);
            SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
            draw();
            SDL_RenderPresent(sys.get_ren());
            }

            while(getRect().y < originalheight){
            moveDown(10);
            SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
            draw();
            SDL_RenderPresent(sys.get_ren());
            }
        //}
        isJumping = false;
    }

    void Actor:: draw() const {
        // if (isFacingRight)
		// 	SDL_RenderCopy(sys.get_ren(), downIcon, NULL, &getRect());
		// else
		// 	SDL_RenderCopy(sys.get_ren(), upIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

}