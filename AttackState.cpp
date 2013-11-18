#include <math.h>

#include "template.h"
#include "game.h"
#include "Helper.h"
#include "Assets.h"

#include "Player.h"
#include "Invader.h"
#include "Missile.h"

#include "AttackState.h"


AttackState::AttackState(Invader* parent) : InvaderState(parent) {
    this->TargetX = this->TargetY = 0;    
}


AttackState::~AttackState(void) {
}

void AttackState::Init() {
    this->VelocityX = this->VelocityY = 2;
    if(Parent->PosX > Parent->MainGame->CurrentPlayer->PosX) {
        this->VelocityX = -2;
    }
    
    this->shootTime = 1;
    this->shootTimer = 1;
    this->shootCount = 0;
    this->Shooting = false;
}

void AttackState::Update(float deltaTime) {
    Player* player = Parent->MainGame->CurrentPlayer;

	if(Parent->PosY < (player->PosY - 5)) {
                
        TargetX = player->PosX + (player->VelocityX * 5); //predict movement a bit
        TargetY = SCRHEIGHT + Parent->SizeY;
    }
    
    shootTime += deltaTime;
    Shooting = false;

    if(shootCount < 2) {
        if(shootTime >= shootTimer) {
            shootCount++;
            shootTimer -= 0.7f;
            shootTime = 0;
            
            Parent->Fire(TargetX, TargetY);

            Shooting = true;
        }
    }

    int modifier = Helper::Sign(TargetX - Parent->PosX);

    this->VelocityX += 0.08f * modifier;
    this->VelocityX = min(2, VelocityX);
    this->VelocityX = max(-2, VelocityX);    

    Parent->PosX += VelocityX;
    Parent->PosY += VelocityY;

    if(Parent->PosY >= SCRHEIGHT + Parent->SizeY) Parent->SwitchState(Parent->GoHome);
}