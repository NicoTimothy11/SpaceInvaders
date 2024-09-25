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
    position.y = 70;
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

Rectangle MysteryShip::getRect()
{
    if(Alive) {
        return {position.x , position.y, float(image.width), float(image.height)};
    }
    else {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update() {
    if(Alive) {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width || position.x < 0) {
            Alive = false; 
        }
    } 
}

void MysteryShip::Draw() {
    if(Alive) {
        DrawTextureV(image, position, WHITE);
    }
}