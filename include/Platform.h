#ifndef PLATFORM_H
#define PLATFORM_H
#include "Constants.h"
#include "MobileComponent.h"
#include "System.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower{
    class Platform : public MobileComponent{
    public:
        static Platform* getInstance(int x, int y, int w, int h, std::string image);
        static Platform* getInstance(int x, int y, int w, int h, std::string image, bool);
        void draw() const;
        void update();
        void collisionDetection(const Component*);
        ~Platform();
        bool shouldBeRemoved() {return toBeRemoved;}

    protected:
        Platform(int x, int y, int w, int h, std::string image);
        Platform(int x, int y, int w, int h, std::string image, bool);

    private:
        SDL_Texture* texture;
        std::string image;
        int newX, newY;
        bool toBeRemoved;
    };
}
#endif