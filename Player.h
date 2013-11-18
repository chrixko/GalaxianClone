#pragma once

#include "surface.h"
#include "Entity.h"
#include "Missile.h"

class Player : public Entity {
	public:
		Player(void);		
        ~Player();

		Surface* LifeGraphic;
        Surface* FlagGraphic;
        Animation* ExplodeAnimation;
        
        int Score;
        int Lives;

        Missile* LoadedMissile;

        void LoadMissile();

        void Init();
		void Update(float deltaTime);
		void Draw(float deltaTime);
        void Destroy();            
};