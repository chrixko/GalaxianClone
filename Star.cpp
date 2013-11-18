#include "surface.h"
#include "template.h"

#include "Assets.h"
#include "Helper.h"

#include "Star.h"

Star::Star(int posX, int posY) {
    this->PosX = posX;
    this->PosY = posY;

    this->Color = (StarColor)Helper::GetRandomInt(0, 5);

    switch (this->Color) {
        case White:
            this->Graphic = Assets::Graphics["star_white"];
            break;
        case Red:
            this->Graphic = Assets::Graphics["star_red"];
            break;
        case Yellow:
            this->Graphic = Assets::Graphics["star_yellow"];
            break;
        case Purple:
            this->Graphic = Assets::Graphics["star_purple"];
            break;
        default:
            this->Graphic = new Surface("assets/star_white.tga");
            break;
    }

    this->ZOrder = -10;

    this->VelocityX = 0;
    this->VelocityY = 1;
}

Star::~Star(void) {
}

void Star::Update(float deltaTime) {
    this->PosX += this->VelocityX;
    this->PosY += this->VelocityY;

    if(this->PosY >= SCRHEIGHT + 3) {
        this->PosY = -3;
    }

    Hidden = (bool)Helper::GetRandomInt(0, 2);
}