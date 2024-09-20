#include "game.h"
#include <iostream>
#include "obstacle.cpp"


Game::Game() 
{
    obstacles = CreateObstacles();
};

Game::~Game() 
{

};

void Game::Draw() {
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) {
        laser.Draw();
    }

    for(auto& obstacle : obstacles) {
        obstacle.Draw();
    }
}

void Game::Update() {
    for(auto& laser: spaceship.lasers) {
        laser.Update();
    }

    DeleteInactiveLasers();
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

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it->active) {
            it = spaceship.lasers.erase(it);
        }
        else {
            it++;
        }
    };
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int ObstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * ObstacleWidth)) / 5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * ObstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}
