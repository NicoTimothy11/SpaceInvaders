#include <raylib.h>
#include "Spaceship.cpp"
#include "game.cpp"



int main()
{
    Color black = {0, 0, 0, 255};
    Color pink = {255, 192, 203, 255};
    int offset = 50;
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {   
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(black);
        DrawRectangleRoundedLines({10, 10, 1310, 800}, 0.18f, 20, 2, pink);
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}