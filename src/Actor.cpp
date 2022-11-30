#include "Actor.h"
//#include "Sprite.h"
#include <string>
#include "Component.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include <vector>
#include "Platform.h"
using namespace std;

namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image) : Component(x,y,w,h), upperLeftX(x+10), upperLeftY(y+10),lowerRightX(x+w-10) , lowerRightY(y+h) {
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    void Actor::keyDown(const SDL_Event& event) {
        
        switch(event.key.keysym.sym) {
            case SDLK_RIGHT: 
            moveRight(10); ; break;
            case SDLK_LEFT: moveLeft(10); break;
            case SDLK_UP: moveUp(10); break;
            case SDLK_DOWN:moveDown(10); break;
            case SDLK_SPACE: jump(); break;
        }

    //collisionDetection(getComps());
}

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }

    bool Actor::collisionCheckPlatform(const Platform* other)const{ //, char c
        // switch(c){
        //     case 'l': //check left
        //     case 'r': //check right

        // }
        return false;
    }

    Component* Actor::collisionDetection(const vector<Component*> comps){
        //std::vector<Component*> comp = ses.getComps();
        for (Component* c : comps){
            if(dynamic_cast<Platform*>(c)){
                const Platform* p = static_cast<Platform*>(c);
                if(collisionCheckPlatform(p)){
                    return c;
                }
                
            }
        }
        return nullptr;
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