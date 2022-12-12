#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include "Platform.h"

namespace tower {

	class Session
	{
	public:
		Session();
		void add(Component* c);
		void run();
		~Session();
		const std::vector<Component*> getComps() const {return comps;}
		void processInput();
		void updateGame();
		void generateOutput();
		void scroll();

	private:
		std::vector<Component*> comps;
		std::vector<Platform*> platforms;
		void collisionDetection();
		bool quit;
		int scrollSpeed = 10;
	};

	//extern Session ses;
}
#endif