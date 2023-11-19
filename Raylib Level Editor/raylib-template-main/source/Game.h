#ifndef GAME_H
#define GAME_H

#define TILE_SIZE 100
#define GRID_SIZE 10

#include "raylib.h"

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

    void CheckTiles(int t_rows, int t_cols);

    const int screenWidth = TILE_SIZE * GRID_SIZE;
    const int screenHeight = TILE_SIZE * GRID_SIZE;

    Texture2D spriteSheet = LoadTexture("source/tiles.png"); // Load your sprite sheet

    Rectangle sourceRect;


    int tileIds[GRID_SIZE][GRID_SIZE]; // Array to store the texture ID of each tile


private:
    // Add your game-specific variables and functions here
};

#endif // GAME_H
