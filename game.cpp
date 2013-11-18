// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009

#include <iostream>
#include <algorithm>
#include <vector>

#include "stdlib.h"
#include "SDL.h"

#include "Assets.h"
#include "Helper.h"
#include "Entity.h"
#include "Player.h"
#include "StarField.h"

#include "game.h"

using namespace std;

void Game::Init() {
	ExitGame = false;

	LeftPressed = RightPressed = SpacePressed = RPressed = false;

	Assets::Load();

	StarField* starField = new StarField();
	AddEntity(starField);

	this->Swarm = new InvaderSwarm();
	AddEntity(Swarm);

	this->CurrentPlayer = new Player();
	AddEntity(CurrentPlayer);    

	KilledInvaders = 0;
	Level = 1;
}

Entity* Game::Colliding(Entity* entA, char* type) {
	if(strlen(entA->Type) != 0) {
		for(unsigned int i = 0; i < Entities.size(); i++) {
			Entity* ent = Entities[i];
			if(strcmp(ent->Type, type) == 0 && Colliding(entA, ent)) {
				return ent;
			}
		}
	}

	return 0;
}

bool Game::Colliding(Entity* entA, Entity* entB) {
	SDL_Rect intersection;
	return Helper::SDL_IntersectRect(&entA->GetHitbox(), &entB->GetHitbox(), &intersection);
}

void Game::Tick( float deltaTime ) {    
	float secondsDeltaTime = deltaTime / 1000;

	for (int i = 0; i < 8 ; i++) {
		Screen->Clear( 0 );
	}				
	
	if(Entities.size() > 0) {
		for(int i = Entities.size() - 1; i >= 0; i--) {
			Entities[i]->Update(secondsDeltaTime);			
		}

		for(unsigned int i = 0; i < Entities.size(); i++) {
			Entities[i]->Draw(secondsDeltaTime);
		}
	}

	if(RPressed && CurrentPlayer->Lives <= 0) {
		RemoveEntity(CurrentPlayer);
		CurrentPlayer = new Player();
		AddEntity(CurrentPlayer);

        int inv_Count = 0;

		for(int i = Entities.size() - 1; i >= 0; i--) {		    
            Entity* ent = Entities[i];
			if(strcmp(ent->Type, "invader") == 0) {
				RemoveEntity(ent);
                inv_Count++;
			}
		}

		RemoveEntity(Swarm);
		Swarm = new InvaderSwarm();
		AddEntity(Swarm);

		KilledInvaders = 0;
		Level = 0;
	}

	freeEntities();

	//yeah.. sorry but it is simple and does the job right now
	if(KilledInvaders >= 46) {
		nextLevel();
	}
}

void Game::nextLevel() {
	Level++;
	KilledInvaders = 0;

	RemoveEntity(Swarm);

	Swarm = new InvaderSwarm();
	AddEntity(Swarm);
}

void Game::freeEntities() {
	int size = ToDeleteEntities.size();
	if(size > 0) {
		for(int i = size -1; i >= 0; i--) {
			Entity* ent = ToDeleteEntities[i];
												   
			ToDeleteEntities.erase(ToDeleteEntities.begin() + i);            

			delete ent;            
		}        
	}
}

void Game::KeyDown( unsigned int code ) {
	if(code == SDLK_LEFT) {
		LeftPressed = true;
	}

	if(code == SDLK_RIGHT) {
		RightPressed = true;
	}

	if(code == SDLK_SPACE) {
		SpacePressed = true;
	}

	if(code == SDLK_ESCAPE) {
		this->ExitGame = true;
	}

	if(code == SDLK_r) {
		RPressed = true;
	}
}

void Game::KeyUp( unsigned int code ) {
	if(code == SDLK_LEFT) {
		LeftPressed = false;
	}

	if(code == SDLK_RIGHT) {
		RightPressed = false;
	}

	if(code == SDLK_SPACE) {
		SpacePressed = false;
	}

	if(code == SDLK_r) {
		RPressed = false;
	}
}

void Game::AddEntity( Entity* ent ) {
	ent->MainGame = this;
	ent->Init();

	Entities.push_back(ent);

	sort(Entities.begin(), Entities.end(), Entity::CompareByZOrder);
}

void Game::RemoveEntity( Entity* ent ) {
	ent->Destroy();
	Entities.erase(std::remove(Entities.begin(), Entities.end(), ent), Entities.end());
	ToDeleteEntities.push_back(ent);
}