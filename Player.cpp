#include <string>

#include "template.h"
#include "Assets.h"
#include "game.h"
#include "Animation.h"

#include "Player.h"

Player::Player(void) {
	this->Graphic = Assets::Graphics["player"];
	this->LifeGraphic = Assets::Graphics["player_life"];
	this->FlagGraphic = Assets::Graphics["player_flag"];
	this->ExplodeAnimation = new Animation(*Assets::Animations["player_explode"]);    
	
	this->SizeX = 28;
	this->SizeY = 33;
	this->ZOrder = 10;

	this->Type = "player";
   
	this->Lives = 3;

	this->VelocityX = 5;

	this->LoadedMissile = 0; 
	this->Score = 0;
}

Player::~Player(void) {
	delete ExplodeAnimation;
}

void Player::LoadMissile() {
	if(this->LoadedMissile == 0) {
		//TODO delete missiles somewhere
		this->LoadedMissile = new Missile(this->PosX, this->PosY, true);
		this->LoadedMissile->Type = "";

		MainGame->AddEntity(this->LoadedMissile);
	}
}

void Player::Init() {
	this->PosX = SCRWIDTH / 2;
	this->PosY = SCRHEIGHT - 100;

	LoadMissile();
}

void Player::Update(float deltaTime) {
	if(Lives <= 0) return; 

	if(CurrentAnimation == ExplodeAnimation) {
		if(CurrentAnimation->Finished) {
			CurrentAnimation = 0;
			
			Lives--;

			if(this->LoadedMissile != 0) {
				MainGame->RemoveEntity(LoadedMissile);
				this->LoadedMissile = 0;
			}
					   
			Player::Init();
		}
		
		return;
	}
	
	VelocityX = 0;
	if(MainGame->LeftPressed) {
		VelocityX = -5;    
	}

	if(MainGame->RightPressed) {
		VelocityX = 5;
	}

	PosX += VelocityX;
	PosX = min(SCRWIDTH - SizeX, PosX);
	PosX = max(0, PosX);

	if(MainGame->SpacePressed) {
		if(LoadedMissile != 0) {
			LoadedMissile->Type = "missile_player";
			LoadedMissile->Fire();
			LoadedMissile = 0;

			Mix_PlayChannel(-1, Assets::Sounds["player_shoot"], 0);
		}
	}

	if(CollidesWith("missile_invader") || CollidesWith("invader")) {
		Mix_PlayChannel(-1, Assets::Sounds["player_explode"], 0);

		CurrentAnimation = ExplodeAnimation;
		CurrentAnimation->Play(false);
	}

	if(LoadedMissile != 0) {
		LoadedMissile->PosX = PosX + (Graphic->GetWidth() / 2) - LoadedMissile->Graphic->GetWidth() / 2;
		LoadedMissile->PosY = PosY - 8;
	}
}

void Player::Draw(float deltaTime) {
	Entity::Draw(deltaTime);

	int x = 30;
	int y = SCRHEIGHT - 50;

	for(int i = 0; i < Lives; i++) {
		LifeGraphic->CopyTo(MainGame->Screen, x + (i * (LifeGraphic->GetWidth() + 10)), y);		
	}

	x = SCRWIDTH - 30;
	for(int i = 0; i < MainGame->Level; i++) {
		FlagGraphic->CopyTo(MainGame->Screen, x - (i * (FlagGraphic->GetWidth() + 2)), y);
	}

	MainGame->Screen->Print("HIGHSCORE", SCRWIDTH / 2, 5, 0xFF0000);
	MainGame->Screen->Print(&std::to_string(Score)[0], (SCRWIDTH / 2) + 25, 15, 0xFFFFFF);  
	
	if(Lives <= 0) {
		MainGame->Screen->Print("GAME OVER", (SCRWIDTH / 2) - 10, SCRHEIGHT / 2, 0xFF0000);
		MainGame->Screen->Print("PRESS R TO RESTART", (SCRWIDTH / 2) - 25, (SCRHEIGHT / 2) + 20, 0xFFFFFF);
	}
}

void Player::Destroy() {
	if(LoadedMissile != 0) {
		MainGame->RemoveEntity(LoadedMissile);
	}
}