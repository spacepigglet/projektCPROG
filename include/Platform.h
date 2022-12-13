#ifndef PLATFORM_H
#define PLATFORM_H
#include "Component.h"
#include "Constants.h"
#include "System.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower{
    class Platform : public Component{
    public:
    static Platform* getInstance(int x, int y, int w, int h, std::string image);
    void draw() const;
    void collisionDetection(const Component*);
    ~Platform();

    protected:
    Platform(int x, int y, int w, int h, std::string image);
    // int leftSide = x + h;
    // int rightSide = (w - x) + h;
    // int topSide = x + w;
    // int bottomSide = (h-y) + w;
    
    private:
    SDL_Texture* texture;
    std::string image;
    int leftX;
    int upperY;
    int rightX;
    int lowerY;
    bool collider = true;
    };
}
#endif