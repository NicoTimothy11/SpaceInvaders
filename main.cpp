#include <raylib.h>
#include "Spaceship.cpp"
#include "game.cpp"
#include <string>

std::string FormatWithLeadingZeros(int num, int width) {
    std::string NumberText = std::to_string(num);
    int LeadingZeros = width - NumberText.length();
    return NumberText = std::string(leadingZeros, '0') + NumberText;
}

int main()
{
    Color black = {0, 0, 0, 255};
    Color pink = {255, 192, 203, 255};
    int offset = 50;
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "Space Invaders");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {   
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(black);
        DrawRectangleRoundedLines({10, 10, 1310, 800}, 0.18f, 20, 2, pink);
        DrawLineEx({25, 730}, {1310, 730}, 3, pink);
        if(game.run) {
        DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, pink);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, pink);
        }

        float x = 50.0;
        for(int i = 0; i < game.lives; i++){
            DrawTextureV(spaceshipImage, {x, 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, pink);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, pink);

        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}