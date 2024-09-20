#include <raylib.h>
#include "Spaceship.cpp"
#include "game.cpp"


int main()
{
    Color black = {0, 0, 0, 255};
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;


    while (WindowShouldClose() == false)
    {   
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(black);
        game.Draw();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}