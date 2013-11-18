#include "Invader.h"
#include "AttackState.h"

#include "FollowCommanderState.h"


FollowCommanderState::FollowCommanderState(Invader* parent) : InvaderState(parent) {
    this->Commander = 0;
}

FollowCommanderState::~FollowCommanderState(void) {
}

void FollowCommanderState::Init() {
    positionOffsetX = Parent->PosX - this->Commander->PosX;
    positionOffsetY = Parent->PosY - this->Commander->PosY;
}

void FollowCommanderState::Update(float deltaTime) {
    if(Commander->CurrentState == Commander->Explode) {
        Parent->SwitchState(Parent->Attack);

        return;
    } else if(Commander->CurrentState == Commander->GoHome) {
        Parent->SwitchState(Parent->GoHome);

        return;
    }

    if(Commander->CurrentState == Commander->Attack) {
        AttackState* attack = (AttackState*)Commander->Attack;

        if(attack->Shooting) {
            Parent->Fire(attack->TargetX, attack->TargetY);
        }
    }


    Parent->PosX = Commander->PosX + positionOffsetX;
    Parent->PosY = Commander->PosY + positionOffsetY;
}