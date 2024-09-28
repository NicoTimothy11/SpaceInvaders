#pragma once
#include "obstacle.h"
#include "Spaceship.h"
#include "alien.cpp"
#include "MysteryShip.cpp"

class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int HighScore;
        Music music;
    private:
        void DeleteInactiveLasers();
        Spaceship spaceship;
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AlienShootLaser();
        void CheckCollisions();
        void GameOver();
        void Reset();
        void GameInit();
        void CheckForHighScore();
        void SaveHighScoreToFile(int HighScore);
        int loadHighScoreFromFile();
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int AliensDirection;
        std::vector<Laser> alienLasers;
        constexpr static float AlienLaserShootInterval = 0.35;
        float timeLastAlienFired;
        MysteryShip mysteryship;
        float mysteryShipSpawnInterval;
        float timeLastSpawn;
        Sound explosionSound;
};