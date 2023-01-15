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
		const SDL_Rect& getRect() const { return rect; }
		int getLeftX() {return rect.x;}
		int getUpperY() {return rect.y;}
		int getRightX() {return rect.x + rect.w;}
		int getLowerY() {return rect.y + rect.h;}
		int getWidth() {return rect.w;}
		int getHeight() {return rect.h;}

		void scroll(bool, int); 
		void setPosition(int, int);
  	void moveY(int toMove){rect.y += toMove;}
		void moveX(int toMove){rect.x += toMove;}
  	virtual void handleCollision(Component*) {}
		
	protected:
		Component(int x, int y, int w, int h);
		Component(int x, int y, int w, int h, bool scrollable);
		
	 	SDL_Texture* texture;
		SDL_Rect rect;
		int leftX;
		int upperY;
		int rightX;
		int lowerY;
	
	private:
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;

		virtual void verticalScroll(int);
  	virtual void horizontalScroll(int);
		bool isScrollable = true;
	
	};
}
#endif
