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
		virtual void draw() const = 0;
		virtual void collision(const Component*) {};
		const SDL_Rect& getRect() const { return rect; }
		void moveRight(int toAdd){rect.x+=toAdd;}
		void moveLeft(int toSub){rect.x-=toSub;}
		void moveDown(int toAdd){rect.y+=toAdd;}
		void moveUp(int toSub){rect.y-=toSub;}
	protected:
		Component(int x, int y, int w, int h);
	private:
		SDL_Rect rect;
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;
	};
}
#endif
