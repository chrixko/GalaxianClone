#include <math.h>
#include "Helper.h"
#include "game.h"
#include "Assets.h"
#include "Invader.h"
#include "ArcState.h"

ArcState::ArcState(Invader* parent, int direction) : InvaderState(parent) {
	Direction = direction;	
}

ArcState::~ArcState(void) {
}

void ArcState::Init() {
	angle = 180.0f;
	stepCount = 30;
	anglePerStep = (180.0f / stepCount);

	radius = 40.0f * Direction;

	pivotX = (int)(Parent->PosX + radius);
	pivotY = (int)(Parent->PosY);
	
	Parent->MainGame->Swarm->RemoveInvader(Parent);

	Parent->FlySoundChannel = Mix_PlayChannel(-1, Assets::Sounds["invader_fly"], 0);   
}

void ArcState::Update(float deltaTime) {	
	angle += anglePerStep;

	float x = cos(Helper::DegreesToRadians(angle)) * radius;
	float y = sin(Helper::DegreesToRadians(angle)) * radius * Direction;

	Parent->PosX = x + pivotX;
	Parent->PosY = y + pivotY;	

	if(angle >= 370) {
		Parent->SwitchState(Parent->Attack);
	}
}
