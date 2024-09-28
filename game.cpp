#include "game.h"
#include <iostream>
#include "obstacle.cpp"
#include <fstream>


Game::Game() 
{

    GameInit();
};

Game::~Game() 
{
    Alien::UnloadImages();
};

void Game::Draw() {
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) {
        laser.Draw();
    }

    for(auto& obstacle : obstacles) {
        obstacle.Draw();
    }
    
    for(auto& alien : aliens) {
        alien.Draw();
    }

    for(auto& laser: alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update() {
    if(run) {
        double CurrentTime = GetTime();
        if(CurrentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for(auto& laser: spaceship.lasers) {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();
        
        for(auto& laser: alienLasers) {
            laser.Update();
        }

        DeleteInactiveLasers();
        mysteryship.Update();

        CheckCollisions();
    }
    else {
        if(IsKeyDown(KEY_ENTER)) {
            Reset();
            GameInit();
        };
    }
}

void Game::HandleInput() {
    if(run) {
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
    }

        for(auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if(!it->active) {
            it = alienLasers.erase(it);
        }
        else {
            it++;
        }
    }

}

std::vector<Obstacle> Game::CreateObstacles()
{
    int ObstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * ObstacleWidth)) / 5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * ObstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;

    for(int row = 0; row < 5; row++){
        for(int column = 0; column < 15; column++) {

            int alienType;
            if(row == 0) {
                alienType = 3;
            }
            else if(row == 1 || row == 2) {
                alienType = 2;
            }
            else {
                alienType = 1;
            }

            float x = 200 + column * 55;
            float y = 100 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for(auto& alien : aliens) {
        if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            AliensDirection = - 1;
            MoveDownAliens(4);
        }
        if(alien.position.x < 0) {
            AliensDirection = 1;
            MoveDownAliens(4); 
        }
        alien.Update(AliensDirection);
    } 
}  

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double CurrentTime = GetTime();
    if(CurrentTime - timeLastAlienFired >= AlienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2,
                                alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckCollisions()
{
    // Spaceship laser
    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it != aliens.end()) {
            if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                if(it -> type == 1) {
                    score += 100;
                } else if(it -> type == 2) {
                    score += 200;
                }else if(it -> type == 3) {
                    score += 300;
                }
                CheckForHighScore();
                
                it = aliens.erase(it);
                laser.active = false;
            } else {
                it++;
            }
        }

        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
               if(CheckCollisionRecs(it -> getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
               } else {
                    it++;
               }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.Alive = false;
            laser.active = false;
            score += 500;
            CheckForHighScore();
        }
    }

    // Alien Lasers

    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if(lives == 0) {
                GameOver();
            }
        }
            for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
               if(CheckCollisionRecs(it -> getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
               } else {
                    it++;
               }
            }
        }
    }

    // Alien Collision with Obstacle

    for(auto& alien : aliens) {
        for(auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }
        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    run = false;
}


void Game::GameInit()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    AliensDirection = 1;
    timeLastAlienFired = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    run = true;
    lives = 3;
    HighScore = 0;
    score = 0;
}

void Game::CheckForHighScore()
{
    if(score > HighScore) {
        HighScore = score;
        SaveHighScoreToFile(HighScore);
    }
}

void Game::SaveHighScoreToFile(int HighScore)
{
    std::ofstream HighScorefile("highscore.txt");
    if(HighScorefile.is_open()) {
        HighScorefile << HighScore;
        HighScorefile.close();
    } else {
        std::cerr << "Failed to save" << std::endl; 
    }
}

int Game::loadHighScoreFromFile()
{
    int LoadedHighScore = 0;
    std::ifstream HighScorefile("highscore.txt");
    if(HighScorefile.is_open()) {
        HighScorefile >> LoadedHighScore;
        HighScorefile.close();
    } else {
        std::cerr << "Failed to load highscore file" << std::endl;
    }
    return LoadedHighScore;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}