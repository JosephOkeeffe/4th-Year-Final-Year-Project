#include "game.h"
#include <iostream>

Game::Game()
{
    Init();
}

Game::~Game()
{
    // Cleanup resources here
}

void Game::Init()
{
    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            tileIds[rows][cols] = 0;
        }
    }
}

void Game::Update()
{
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && mouseX >= 0 && mouseY >= 0 &&
        mouseX < screenWidth && mouseY < screenHeight)
    {
        // Calculate the tile indices
        int i = mouseX / TILE_SIZE;
        int j = mouseY / TILE_SIZE;

        // Change the texture ID of the clicked tile
        tileIds[i][j] = 1;


        std::cout << "X: " << i << " Y: " << j << "\n";
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            int x = rows * TILE_SIZE;
            int y = cols * TILE_SIZE;
            Vector2 position = { x,y };

            CheckTiles(rows, cols);

            DrawTextureRec(spriteSheet, sourceRect, position, WHITE);

            DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, GRAY);
        }
    }

    EndDrawing();
}

void Game::CheckTiles(int t_rows, int t_cols)
{
    if (tileIds[t_rows][t_cols] == 0)
    {
        sourceRect.x = 0;
        sourceRect.y = 200;
        sourceRect.width = 200;
        sourceRect.height = 200;

    }
    if (tileIds[t_rows][t_cols] == 1)
    {
        sourceRect.x = 200;
        sourceRect.y = 200;
        sourceRect.width = 200;
        sourceRect.height = 200;
              
    }
       
}
