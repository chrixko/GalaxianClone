#pragma once

#include "Entity.h"

class Missile : public Entity {
    public:
        Missile(float posX, float posY, bool isPlayerMissile);
        ~Missile(void);

        bool IsPlayerMissile;

        void Update(float deltaTime);
        void Destroy();

        void Fire(void);        
};