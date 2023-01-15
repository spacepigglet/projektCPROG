#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <string>

namespace tower {
	class Button : public Component
	{
	public:
		static Button* getInstance(int x, int y, int w, int h, std::string txt);
		static Button* getInstance(int x, int y, int w, int h, std::string txt, std::string image);
		static Button* getInstance(int x, int y, int w, int h, std::string txt, std::string image, bool scrollable);
		static Button* getInstance(int x, int y, int w, int h, std::string txt, bool scrollable);
		
		void mouseDown(const SDL_Event&);
		void mouseUp(const SDL_Event&);
		void draw() const;
		virtual void perform(Button* source) {}
		virtual ~Button();
	protected:
		Button(int x, int y, int w, int h, std::string txt);
		Button(int x, int y, int w, int h, std::string txt, std::string image);
		Button(int x, int y, int w, int h, std::string txt, bool scrollable);
		Button(int x, int y, int w, int h, std::string txt, std::string image, bool scrollable);
	private:
		std::string text;
		SDL_Texture* text_texture;
		SDL_Texture* buttonIcon_texture ; 
		bool isDown = false;
	};
}

#endif