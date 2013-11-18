#include "Invader.h"
#include "game.h"
#include "Assets.h"
#include "ExplodingState.h"


ExplodingState::ExplodingState(Invader* parent) : InvaderState(parent) {
}


ExplodingState::~ExplodingState(void) {
}

void ExplodingState::Init() {
 	Parent->Type = "";
	Parent->CurrentAnimation = Parent->ExplodeAnimation;
	Parent->CurrentAnimation->Play(false);	
    Parent->MainGame->Swarm->RemoveInvader(Parent);

    Mix_PlayChannel(-1, Assets::Sounds["invader_explode"], 0);
}

void ExplodingState::Update(float deltaTime) {
	if(Parent->CurrentAnimation->Finished) {
		Parent->MainGame->RemoveEntity(Parent);    
        Parent->MainGame->KilledInvaders++;
        
        if(Parent->Class == INVADER_COMMANDER) {
            Mix_PlayChannel(-1, Assets::Sounds["invader_commander_shot"], 0);
        }
	}
}