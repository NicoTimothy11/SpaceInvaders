#include <raylib.h>
#include "Spaceship.cpp"
#include "game.cpp"
#include "alien.cpp"


int main()
{
    Color black = {0, 0, 0, 255};
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Space Invaders");
    SetTargetFPS(60);

    Game game;
    Alien alien = Alien({3, {100, 100}});
    Alien alien2 = Alien({2, {200, 200}});
    Alien alien3 = Alien({1, {300, 300}});


    while (WindowShouldClose() == false)
    {   
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(black);
        game.Draw();
        alien.Draw();
        alien2.Draw();
        alien3.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}