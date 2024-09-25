#include "MysteryShip.h"

MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    Alive = false;
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if(side == 0) {
        position.x = 0;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width;
        speed -= 3;
    }
    Alive = true;
}