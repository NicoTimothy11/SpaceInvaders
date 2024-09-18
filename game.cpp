#include "game.h"


Game::Game() 
{

};

Game::~Game() 
{

};

void Game::Draw() {
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) {
        laser.Draw();
    }
}

void Game::Update() {
    for(auto& laser: spaceship.lasers) {
        laser.Update();
    }
}

void Game::HandleInput() {
    if(IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
    }
}