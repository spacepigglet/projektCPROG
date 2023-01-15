#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

namespace tower {
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void mouseDown(const SDL_Event&) {}
		virtual void mouseUp(const SDL_Event&) {}
		virtual void keyDown(const SDL_Event&) {}
		virtual void keyUp(const SDL_Event&) {}
		virtual void update() {}
		virtual void draw() const = 0;
		const SDL_Rect& getRect() const {return rect;}
		int getLeftX() const {return rect.x;}
		int getUpperY() const {return rect.y;}
		int getRightX() const {return rect.x + rect.w;}
		int getLowerY() const {return rect.y + rect.h;}
		int getWidth() const {return rect.w;}
		int getHeight() const {return rect.h;}
		void changeHeight(int value) {rect.h += value;}
		void scroll(const bool, const int); 
		void setPosition(int, int);
  	void moveY(const int toMove){rect.y += toMove;}
		void moveX(const int toMove){rect.x += toMove;}
  	virtual void handleCollision(Component*) {}
		
	protected:
		Component(int x, int y, int w, int h);
		Component(int x, int y, int w, int h, bool scrollable);
	
	private:
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;
		virtual void verticalScroll(int);
  	virtual void horizontalScroll(int);
		SDL_Texture* texture;
		SDL_Rect rect;
		bool isScrollable;
	
	};
}
#endif
