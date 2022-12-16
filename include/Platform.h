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
    void update();
    void collisionDetection(const Component*);
    static void setPlatformWidthRange(int min, int max) {minPlatformWidth = min; maxPlatformWidth = max;}
    ~Platform();
    static int getPlatformMinWidth() {return minPlatformWidth;}
    static int getPlatformMaxWidth() {return maxPlatformWidth;}

    protected:
    Platform(int x, int y, int w, int h, std::string image);
    // int leftSide = x + h;
    // int rightSide = (w - x) + h;
    // int topSide = x + w;
    // int bottomSide = (h-y) + w;
    
    private:
    static int minPlatformWidth;
    static int maxPlatformWidth;
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