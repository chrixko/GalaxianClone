#include "surface.h"
#include "template.h"
#include "game.h"

#include "Entity.h"

Entity::Entity(void) {
	Graphic = 0;
	CurrentAnimation = 0;

	PosX = 0;
	PosY = 0;
	VelocityX = 0;
	VelocityY = 0;
	SizeX = 26;
	SizeY = 26;

	Hidden = false;
	ZOrder = 0;

	Type = "";
}

Entity::~Entity(void) {	
}

void Entity::Draw(float deltaTime) {
	if(CurrentAnimation == 0) {
		if(!Hidden && Graphic != 0) {
			Graphic->CopyTo(MainGame->Screen, PosX, PosY);
		}
	} else {
		CurrentAnimation->Update(deltaTime);
		CurrentAnimation->GetCurrentSurface()->CopyTo(MainGame->Screen, PosX, PosY);
	}
	
}

Entity* Entity::CollidesWith(char* type) {
	return MainGame->Colliding(this, type);	
}

void Entity::MoveTo(float posX, float posY, float velocityX, float velocityY) {   
	if(PosX < posX) PosX += velocityX;
	if(PosX > posX) PosX -= velocityX;

	if(PosY > posY) PosY -= velocityY;
	if(PosY < posY) PosY += velocityY;  
}

SDL_Rect Entity::GetHitbox() {
	SDL_Rect hitbox;

	hitbox.x = PosX;
	hitbox.y = PosY;
	hitbox.w = SizeX;
	hitbox.h = SizeY;

	return hitbox;
}

bool Entity::CompareByZOrder(const Entity* a, const Entity* b) {
	return a->ZOrder < b->ZOrder;
}