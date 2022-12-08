#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

namespace tower {
	class Component
	{
	public:
		virtual ~Component();
		virtual void mouseDown(const SDL_Event&) {}
		virtual void mouseUp(const SDL_Event&) {}
		virtual void keyDown(const SDL_Event&) {}
		virtual void keyUp(const SDL_Event&) {}
		virtual void update() {}
		virtual void draw() const = 0;
		virtual void collisionDetection(Component*) {};
		const SDL_Rect& getRect() const { return rect; }
		//SDL_Rect& changeRect() { return rect; }
		void setPosition(int, int);
		void moveRight(int toAdd){rect.x+=toAdd;}
		void moveLeft(int toSub){rect.x-=toSub;}
		void moveDown(int toAdd){rect.y+=toAdd;}
		void moveUp(int toSub){rect.y-=toSub;}
		void moveY(int toMove){rect.y += toMove;}
		void moveX(int toMove){rect.x += toMove;}
		int getLeftX() {return rect.x;}
		int getUpperY() {return rect.y;}
		int getRightX() {return rect.x + rect.w;}
		int getLowerY() {return rect.y + rect.h;}
		int getWidth() {return rect.w;}
		int getHight() {return rect.h;}

	protected:
		Component(int x, int y, int w, int h); //int leftX, int upperY, int rightX , int lowerY
		int leftX;
    int upperY;
    int rightX;
    int lowerY;
	private:
		SDL_Rect rect;
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;
	
	};
}
#endif
