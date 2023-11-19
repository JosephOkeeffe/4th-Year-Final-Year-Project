#include "raylib.h"
#include "Game.h"

int main()
{
    InitWindow(800, 600, "Raylib Game Template");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
    }

    CloseWindow();

    return 0;
}

