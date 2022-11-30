#include "Platform.h"
#include "Constants.h"
#include "System.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower{
    
    Platform::Platform(int x, int y, int w, int h, std::string image) : Component(x,y,w,h) , upperLeftX(x), upperLeftY(y),lowerRightX(x+w) , lowerRightY(y+h) {
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image){
        return new Platform(x, y, w, h, image);
    }

     void Platform:: draw() const {
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

    Platform:: ~Platform(){
        SDL_DestroyTexture(texture);
    }

    void Platform::collision(const Component* other){
        
    }

}