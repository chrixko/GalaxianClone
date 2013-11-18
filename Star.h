#pragma once

#include "Entity.h"

enum StarColor {
    White = 0,
    Red = 1,
    Green = 2,
    Purple = 3,
    Yellow = 4
};

class Star : public Entity {
	public:        
		Star(int posX, int posY);
		~Star(void);

        StarColor Color;

		void Update(float deltaTime);
};

