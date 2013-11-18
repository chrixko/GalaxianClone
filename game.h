#pragma once

#include <vector>

#include "surface.h"

#include "InvaderSwarm.h"

class Entity;
class Player;

class Game
{ 
	public:
		void SetTarget( Surface* a_Surface ) { Screen = a_Surface; }
		void Init();
		void Tick( float deltaTime );
		void KeyDown( unsigned int code );
		void KeyUp( unsigned int code );
		void MouseMove( unsigned int x, unsigned int y ) {}
		void MouseUp( unsigned int button ) {}
		void MouseDown( unsigned int button ) {}

		Surface* Screen;

		bool LeftPressed;
		bool RightPressed;
		bool SpacePressed;
		bool RPressed;

		std::vector<Entity*> Entities;
        std::vector<Entity*> ToDeleteEntities;

        Player* CurrentPlayer;
        InvaderSwarm* Swarm;
        int KilledInvaders;
        int Level;

		Entity* Colliding(Entity* entA, char* type);
		bool Colliding(Entity* entA, Entity* entB);
		
		void AddEntity(Entity* ent);
		void RemoveEntity(Entity* ent);		

		bool ExitGame;
    private:
        void freeEntities();
        void nextLevel();
};