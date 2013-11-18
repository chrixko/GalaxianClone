#include <math.h>
#include "game.h"
#include "Invader.h"
#include "InvaderSwarm.h"

#include "GoHomeState.h"


GoHomeState::GoHomeState(Invader* parent) : InvaderState(parent) {
}


GoHomeState::~GoHomeState(void) {
}

void GoHomeState::Init() {
    Parent->PosY = -Parent->SizeY;
}

void GoHomeState::Update(float deltaTime) {
    float posX = Parent->MainGame->Swarm->PosX + (Parent->SwarmX * (Parent->SizeX + 20));
    float posY = Parent->MainGame->Swarm->PosY + (Parent->SwarmY * (Parent->SizeY + 15));

    Parent->MoveTo(posX, posY, 3, 3);

    //Snap the invaders into the slots if they are near
    if(abs(Parent->PosX - posX) < 3 && abs(Parent->PosY - posY) < 3) {
        Parent->PosX = posX;
        Parent->PosY = posY;
    }

    if(Parent->PosX == posX && Parent->PosY == posY) {
        Parent->SwitchState(Parent->Idle);
        Parent->MainGame->Swarm->AddInvader(Parent);
    }
}
