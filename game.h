#pragma once
#include "obstacle.h"
#include "Spaceship.h"

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
        std::vector<Obstacle> obstacles;
};