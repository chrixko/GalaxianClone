#include "game.h"

#include "ScorePopup.h"


ScorePopup::ScorePopup(float posX, float posY, int value) {
    this->PosX = posX;
    this->PosY = posY;
    
    this->Value = value;
    this->displayTimer = 0;
}

ScorePopup::~ScorePopup(void){
}

void ScorePopup::Update(float deltaTime) {
    this->PosX -= 0.8f;
    this->PosY -= 0.6f;

    displayTimer += deltaTime;
    if(displayTimer >= 0.5f) {
        MainGame->RemoveEntity(this);
    }
}

void ScorePopup::Draw(float deltaTime) {
    MainGame->Screen->Print(&std::to_string(Value)[0], PosX, PosY, 0xFFFFFF);
}