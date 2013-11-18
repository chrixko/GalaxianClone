#include "template.h"
#include "game.h"
#include "Assets.h"
#include "Player.h"
#include "ScorePopup.h"

#include "IdleState.h"
#include "ExplodingState.h"
#include "ArcState.h"
#include "AttackState.h"
#include "GoHomeState.h"
#include "FollowCommanderState.h"

#include "Missile.h"
#include "Invader.h"

Invader::Invader(InvaderClass invaderClass) {
    this->Class = invaderClass;    

    switch (invaderClass) {
        case INVADER_BLUE:
            this->IdleAnimation = new Animation(*Assets::Animations["invader_blue_idle"]);
	        this->ExplodeAnimation = new Animation(*Assets::Animations["invader_blue_explode"]);

            break;
        case INVADER_PURPLE:
            this->IdleAnimation = new Animation(*Assets::Animations["invader_purple_idle"]);
	        this->ExplodeAnimation = new Animation(*Assets::Animations["invader_purple_explode"]);
            
            break;
        case INVADER_RED:
            this->IdleAnimation = new Animation(*Assets::Animations["invader_red_idle"]);
	        this->ExplodeAnimation = new Animation(*Assets::Animations["invader_red_explode"]);
            
            break;
        case INVADER_COMMANDER:
            this->IdleAnimation = new Animation(*Assets::Animations["invader_commander_idle"]);
	        this->ExplodeAnimation = new Animation(*Assets::Animations["invader_commander_explode"]);

            break;
        default:
            break;
    }

    this->Graphic = this->IdleAnimation->Sprites[0];

    this->CurrentAnimation = IdleAnimation;

    this->CurrentAnimation->Play(true);

    this->SizeX = 20;
    this->SizeY = 13;

    this->VelocityX = 1;
    this->VelocityY = 0;

	this->Type = "invader";

	this->SwarmX = this->SwarmY = 0;

    this->FlySoundChannel = -1;
}

Invader::~Invader(void) {
	//Delete Animations		
    delete IdleAnimation;
	delete ExplodeAnimation;

	//Delete States
	delete Idle;
	delete Explode;
	delete Arc;
	delete Attack;
    delete GoHome;
    delete FollowCommander;
    
}

void Invader::Init() {
	Idle = new IdleState(this);
	Explode = new ExplodingState(this);
	Arc = new ArcState(this, SwarmX < 6 ? -1 : 1);			
	Attack = new AttackState(this);
    GoHome = new GoHomeState(this);
    FollowCommander = new FollowCommanderState(this);

	CurrentState = Idle;
}

void Invader::Update(float deltaTime) {
	CurrentState->Update(deltaTime);

	Entity* mis = CollidesWith("missile_player");
	if(mis) {		
        ScorePoints();
		MainGame->RemoveEntity(mis);
		SwitchState(Explode);
	}
}

void Invader::ScorePoints() {
    int score = 0;

    switch (Class) {
        case INVADER_BLUE:
            score = 30;
            break;
        case INVADER_PURPLE:
            score = 40;
            break;
        case INVADER_RED:
            score = 50;
            break;
        case INVADER_COMMANDER:
            score = 60;
            break;
        default:
            break;
    }

    if(CurrentState == Attack || CurrentState == Arc || CurrentState == FollowCommander) {
        score *= 2;

        if(Class == INVADER_COMMANDER) score += 30;
    } 

    MainGame->CurrentPlayer->Score += score;

    MainGame->AddEntity(new ScorePopup(PosX, PosY, score));
}

void Invader::Destroy() {
    if(FlySoundChannel != -1) {
        Mix_HaltChannel(FlySoundChannel);        
    }
}

void Invader::RestrainPosition() {
    if(PosX < 100) PosX = 100;
    if((PosX + SizeX) > (SCRWIDTH - 100)) PosX = (SCRWIDTH - 100) - SizeX;
}

void Invader::Fire(float targetX, float targetY) {
    Missile* mis = new Missile(PosX, PosY, false);
    float disX = (targetX - mis->PosX);
    float disY = (targetY - mis->PosY);
    float length = sqrt((disX * disX) + (disY * disY));
    mis->VelocityX = (disX / length) * 4;
    mis->VelocityY = (disY / length) * 4;

    MainGame->AddEntity(mis);

    Mix_PlayChannel(-1, Assets::Sounds["invader_shoot"], 0);
}