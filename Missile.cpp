#include <string>

#include "template.h"
#include "Assets.h"
#include "game.h"
#include "Player.h"

#include "Missile.h"

Missile::Missile(float posX, float posY, bool isPlayerMissile) {
    this->PosX = posX;
    this->PosY = posY;
    this->SizeX = 3;
    this->SizeY = 8;

    this->VelocityX = 0;
    this->VelocityY = 0;

    this->ZOrder = 1;

    this->IsPlayerMissile = isPlayerMissile;

    if(isPlayerMissile) {
        this->Type = "missile_player";
        this->Graphic = Assets::Graphics["player_missile"];       
    } else {
        this->Type = "missile_invader";
        this->Graphic = Assets::Graphics["invader_missile"];
    }
}

Missile::~Missile(void){
}

void Missile::Update(float deltaTime) {
    PosX += VelocityX;
    PosY += VelocityY;

    if(PosY > (SCRHEIGHT) || PosY < (0 - SizeY)) {
        MainGame->RemoveEntity(this);
    }
}

void Missile::Destroy() {
    if(IsPlayerMissile) {
        MainGame->CurrentPlayer->LoadMissile();
    }
}

void Missile::Fire(void) {
    this->VelocityY = IsPlayerMissile ? -6.0f : 6.0f;
}
