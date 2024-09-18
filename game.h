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
        Spaceship spaceship;
};