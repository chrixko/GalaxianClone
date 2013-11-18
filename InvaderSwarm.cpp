#include "template.h"
#include "game.h"
#include "Helper.h"
#include "Assets.h"

#include "Animation.h"
#include "Player.h"

#include "Invader.h"
#include "FollowCommanderState.h"

#include "InvaderSwarm.h"

InvaderSwarm::InvaderSwarm(void) {
	this->PosX = 180;
	this->PosY = 200;

	this->VelocityX = 1;

	this->attackTime = this->totalTime = 0;
	this->attackTimer = 3;

	this->idleSoundChannel = -1;
}

InvaderSwarm::~InvaderSwarm(void) {
}

void InvaderSwarm::Init() {
	int startFrame = 0;
	for(int x = 0; x < 10; x++) {
		
		//iterate through frames for the 'wave' effect
		startFrame++;
		if(startFrame > 5) {
			startFrame = 0;
		}

		for(int y = 0; y < 6; y++) {      
			InvaderFormation[x][y] = 0;

			//seems a bit messy but well it works
			InvaderClass invClass;
			if(y > 2) {
				invClass = INVADER_BLUE;
			} else if(y == 2) {
				invClass = INVADER_PURPLE;
				if(x == 0 || x == 9) continue;
			} else if(y == 1) {
				invClass = INVADER_RED;
				if(x < 2 || x > 7) continue;
			} else if(y == 0) {
				invClass = INVADER_COMMANDER;
				if(!(x == 3 || x == 6)) continue;
			}

			Invader* inv = new Invader(invClass);
			InvaderFormation[x][y] = inv;
			inv->PosX = PosX + (x * (inv->SizeX + 20));
			inv->PosY = PosY + (y * (inv->SizeY + 15));

			inv->CurrentAnimation->SetCurrentFrame(startFrame);

			inv->SwarmX = x;
			inv->SwarmY = y;			

			MainGame->AddEntity(inv);
		}
	}

	idleSoundChannel = Mix_PlayChannel(-1, Assets::Sounds["invader_idle"], -1);
}

bool InvaderSwarm::invadersHitWall() {

	bool hasInvaders = false;
	for(int x = 0; x < 10; x++) {
		for(int y = 0; y < 6; y++) {
			Invader* inv = InvaderFormation[x][y];
			if(inv != 0) {
				hasInvaders = true;
				if(inv->PosX < 100 || (inv->PosX + inv->SizeX) > (SCRWIDTH - 100)) {
					return true;
				}
			}
		}
	}
	
	//stop moving if every invader is out
	if(!hasInvaders) return true;

	return false;
}

void InvaderSwarm::Update(float deltaTime) {   
	totalTime += deltaTime;
	attackTime += deltaTime;

	if(attackTime >= attackTimer) {
		InitiateAttack();
		attackTime = 0;
	}   

	if(totalTime <= 30) {
		attackTimer = 3;
	} else if(totalTime <= 60) {
		attackTimer = 2.5f;
	} else if(totalTime <= 90) {
		attackTimer = 2;
	} else if(totalTime <= 120) {
		attackTimer = 1.5f;
	}

	if(invadersHitWall()) {        
		
		for(int x = 0; x < 10; x++) {
			for(int y = 0; y < 6; y++) {
				Invader* inv = InvaderFormation[x][y];
				if(inv != 0) {
					//Snap into limits and flip velocity
					inv->RestrainPosition();
					inv->VelocityX *= -1;
				}
			}
		}        
		VelocityX *= -1;		
	}    

	PosX += VelocityX;
}

void InvaderSwarm::Destroy() {
	if(idleSoundChannel != -1) {
		Mix_HaltChannel(idleSoundChannel);
	}    
}

void InvaderSwarm::AddInvader(Invader* invader) {
	InvaderFormation[invader->SwarmX][invader->SwarmY] = invader;
	invader->VelocityX = VelocityX;
}

void InvaderSwarm::RemoveInvader(Invader* invader) {
	InvaderFormation[invader->SwarmX][invader->SwarmY] = 0;
}

void InvaderSwarm::InitiateAttack() {
	Invader* attacker;
	if(MainGame->CurrentPlayer->PosX < SCRWIDTH / 2) {
		attacker = getLeftInvader();
	} else {
		attacker = getRightInvader();
	}

	

	if(attacker != 0) {        
		attacker->SwitchState(attacker->Arc);
		if(attacker->Class == INVADER_COMMANDER) {
			collectAllies(attacker);
		}
	}
}

void InvaderSwarm::collectAllies(Invader* commander) {
	for(int i = 0; i < 3; i++) {
		Invader* allie = InvaderFormation[commander->SwarmX - 1 + i][commander->SwarmY + 1];
		if(allie != 0) {
			((FollowCommanderState*)allie->FollowCommander)->Commander = commander;            
			allie->SwitchState(allie->FollowCommander);
		}
	}
}

InvaderClass InvaderSwarm::randomClass() {
	InvaderClass invClass = INVADER_BLUE;
	int rnd = Helper::GetRandomInt(0, 10);

	if(rnd > 6) invClass = INVADER_PURPLE;
	if(rnd > 8) invClass = INVADER_COMMANDER;

	return invClass;
}

Invader* InvaderSwarm::getLeftInvader() {   
	InvaderClass invClass = randomClass();

	Invader* left = getInvader(invClass, 0, 9);
	if(left != 0) return left;

	Invader* right = getInvader(invClass, 9, 0);
	if(right != 0) return right;

	return  getSubstitudeInvader();
}

Invader* InvaderSwarm::getRightInvader() {
	InvaderClass invClass = randomClass();

	Invader* right = getInvader(invClass, 9, 6);
	if(right != 0) return right;

	Invader* left = getInvader(invClass, 0, 9);
	if(left != 0) return left;
	
	return getSubstitudeInvader();
}

Invader* InvaderSwarm::getSubstitudeInvader() {

	//try to find any attacker from top to bottom
	Invader* attacker = getInvader(INVADER_BLUE, 0, 9);
	if(attacker == 0) attacker = getInvader(INVADER_PURPLE, 0, 9);
	if(attacker == 0) attacker = getInvader(INVADER_RED, 0, 9);
	if(attacker == 0) attacker = getInvader(INVADER_COMMANDER, 0, 9);

	return attacker;
}

Invader* InvaderSwarm::getInvader(InvaderClass invClass, int fromX, int toX) {
	int fromY, toY = 0;

	switch (invClass) {
		case INVADER_BLUE:
			fromY = 3;
			toY = 5;
			break;
		case INVADER_PURPLE:
			fromY = toY = 2;
			break;
		case INVADER_RED:
			fromY = toY = 1;
			break;
		case INVADER_COMMANDER:
			fromY = toY = 0;
			break;
		default:
			break;
	}

	//TODO: come up with a better solution than two redundant loops
	if(fromX < toX) {
		for(int x = fromX; x < toX + 1; x++) {            
			for(int y = fromY; y < toY + 1; y++) {
				Invader* attacker = InvaderFormation[x][y];
				if(attacker != 0) {
					return attacker;
				}
			}
		}
	} else {        
		for(int x = fromX; x >= toX; x--) {            
			for(int y = fromY; y < toY + 1; y++) {
				Invader* attacker = InvaderFormation[x][y];
				if(attacker != 0) {
					return attacker;
				}
			}
		}
	}

	return 0;
}