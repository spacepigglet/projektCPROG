#ifndef PLATFORM_H
#define PLATFORM_H
#include "Constants.h"
#include "Component.h"
#include "System.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower{
    class Platform : public Component{
    public:
        static Platform* getInstance(int x, int y, int w, int h, std::string image);
        static Platform* getInstance(int x, int y, int w, int h, std::string image, bool remove, bool scrollable);
        void draw() const;
        virtual void update();
        ~Platform();
        bool shouldBeRemoved() const {return isToBeRemoved;}

    protected:
        Platform(int x, int y, int w, int h, std::string image);
        Platform(int x, int y, int w, int h, std::string image, bool removable, bool scrollable);

    private:
        SDL_Texture* texture;
        std::string image;
        int newX, newY;
        bool isToBeRemoved;
    };
}
#endif