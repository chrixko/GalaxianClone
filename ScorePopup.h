#pragma once

#include "Entity.h"

class ScorePopup : public Entity {
    public:
        ScorePopup(float posX, float posY, int value);
        ~ScorePopup(void);

        int Value;

        void Update(float deltaTime);
        void Draw(float deltaTime);
    private:
        float displayTimer;

};