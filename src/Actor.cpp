#include "Actor.h"
//#include "Sprite.h"
#include <string>
#include "Component.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"

namespace tower{
    Actor::Actor(int x, int y, int w, int h, std::string image) : Component(x,y,w,h) {
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    void Actor::keyDown(const SDL_Event& event) {
        
        switch(event.key.keysym.sym) {
            // case SDLK_RIGHT: getRect().x+=10; break;
            // case SDLK_LEFT: getRect().x-=10; break;
            // case SDLK_UP:getRect().y-=10; break;
            // case SDLK_DOWN:getRect().y+=10; break;
            // case SDLK_SPACE: jump(); break;
        }
        //getRect().x = x;
    }

    Actor* Actor::getInstance(int x, int y, int w, int h, std::string image){
        return new Actor(x, y, w, h, image);
    }

    Actor:: ~Actor(){
        SDL_DestroyTexture(texture);
    }

    void Actor::jump(){
        isJumping = true;
        SDL_Rect rect = getRect();
        int originalheight = rect.y;
        int targetHeight = originalheight - 100;
        //while (isJumping){
            while(rect.y > targetHeight){
            rect.y-=10;
            SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
            draw();
            SDL_RenderPresent(sys.get_ren());
            }

            while(rect.y < targetHeight){
            rect.y+=10;
            SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
            draw();
            SDL_RenderPresent(sys.get_ren());
            }
        //}
        isJumping = false;
    }

    void Actor:: draw() const {
        // if (isRFacingRight)
		// 	SDL_RenderCopy(sys.get_ren(), downIcon, NULL, &getRect());
		// else
		// 	SDL_RenderCopy(sys.get_ren(), upIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

}