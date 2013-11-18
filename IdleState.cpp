#include "template.h"

#include "Invader.h"

#include "IdleState.h"


IdleState::IdleState(Invader* parent) : InvaderState(parent) {	
}


IdleState::~IdleState(void) {
}

void IdleState::Update(float deltaTime) {
	Parent->PosX += Parent->VelocityX;
}