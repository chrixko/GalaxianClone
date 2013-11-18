
#include "template.h"
#include "Helper.h"
#include "game.h"

#include "StarField.h"

StarField::StarField(void) {
    for(int i = 0; i < 200; i++) {
       int posX = Helper::GetRandomInt(0, SCRWIDTH);
       int posY = Helper::GetRandomInt(0, SCRHEIGHT);

       Stars.push_back(new Star(posX, posY));
    }
}

StarField::~StarField(void) {
}

void StarField::Init() {
    for(unsigned int i = 0; i < Stars.size(); i++) {
        MainGame->AddEntity(Stars[i]);
    }
}

void StarField::Update(float deltaTime) {

}

void StarField::Destroy() {
    for(unsigned int i = 0; i < Stars.size(); i++) {
        MainGame->RemoveEntity(Stars[i]);
    }
}