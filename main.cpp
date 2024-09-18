#include <raylib.h>
#include "Spaceship.cpp"
#include "game.cpp"
#include "obstacle.cpp"

int main()
{
    Color black = {0, 0, 0, 255};
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;
    Obstacle obstacle = Obstacle({100, 100});


    while (WindowShouldClose() == false)
    {   
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(black);
        game.Draw();

        obstacle.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}