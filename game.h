#pragma once
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
};