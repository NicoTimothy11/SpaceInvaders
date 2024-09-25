#pragma once
#include "obstacle.h"
#include "Spaceship.h"
#include "alien.cpp"

class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
    private:
        void DeleteInactiveLasers();
        Spaceship spaceship;
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int AliensDirection;
};