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
    void draw() const;
    void update();
    void collisionDetection(const Component*);
    ~Platform();
    static int getPlatformMinWidth() {return platformMinWidth;}
	static int getPlatformMaxWidth() {return platformMaxWidth;}
	static int getPlatformHeight() {return platformHeight;}

    protected:
    Platform(int x, int y, int w, int h, std::string image);
    
    private:
    SDL_Texture* texture;
    std::string image;
    int leftX;
    int upperY;
    int rightX;
    int lowerY;
    bool collider = true;
    const static int platformMinWidth = 80;
	const static int platformMaxWidth = 150;
	const static int platformHeight = 10;
    
    };
}
#endif