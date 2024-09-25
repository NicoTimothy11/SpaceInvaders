#include "laser.h"
#include <iostream>

Color pink = {255, 192, 203, 255};

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Laser::Draw() {
    if(active) {
        DrawRectangle(position.x, position.y, 4, 15, pink);
    }
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {
    position.y += speed;
    if(active) {
        if(position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}