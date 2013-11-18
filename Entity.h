#pragma once

#include <string>
#include <vector>

#include "SDL.h"
#include "Animation.h"

class Surface;
class Game;	

class Entity {
	public:
		Entity(void);
		~Entity(void);

		Surface* Graphic;
        Animation* CurrentAnimation;

		Game* MainGame;
		float PosX;
		float PosY;
		float VelocityX;
		float VelocityY;
		int SizeX;
		int SizeY;
			
        bool Hidden;
		int ZOrder;

		char* Type;			
		Entity* CollidesWith(char* type);

        void MoveTo(float posX, float posY, float velocityX, float velocityY);

		//Init -> Entity gets added to the game
		virtual void Init() {};
		virtual void Update(float deltaTime) {};
		virtual void Draw(float deltaTime);
		//Destroy -> Entity gets removed from the game
		virtual void Destroy() {};

		virtual SDL_Rect GetHitbox();

		static bool CompareByZOrder(const Entity* a, const Entity* b);
};