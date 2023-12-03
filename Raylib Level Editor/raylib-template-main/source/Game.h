#ifndef GAME_H
#define GAME_H

#define TILE_SIZE 56
#define GRID_SIZE 50

#define MIN_ZOOM 0.3f
#define MAX_ZOOM 1.0f
#define ZOOM_INCREMENT 0.1f

#define GRASS_PALETTE_SIZE 6
#define PATH_PALETTE_SIZE 14
#define OBSTACLE_PALETTE_SIZE 13

const int screenWidth = (TILE_SIZE * GRID_SIZE) / 2;
const int screenHeight = (TILE_SIZE * GRID_SIZE) / 3;

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h";

enum GrassType
{
    GRASS1, // 0
    GRASS2,
    MOUNTAINS,
    GRASS3,
    GRASS4,
    GRASS5,

    BRIDGE1, // 6
    BRIDGE2,
    BRIDGE3,
    BRIDGE4,
    PATH1,
    PATH2,
    PATH3,
    PATH4,
    PATH5,
    PATH6,
    PATH7,
    PATH8,
    PATH9,
    PATH10,

    WATER1, // 20
    WATER2,
    WATER3,
    WATER4,
    WATER5,
    WATER6,
    WATER7,
    WATER8,
    WATER9,
    WATER10,
    WATER11,
    WATER12,
    WATER13,
};

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

    void KeyPresses();

    void PlacingTiles();
    void SelectPaletteTile();
    void CheckGrassTiles(int t_rows, int t_cols);
    //void CheckObstacleTiles(int t_rows, int t_cols);
    void Zoom();
    void MoveCamera();



   // TileType tileType = NONE;
    GrassType grassType = GRASS1;
   // ObstacleType obstacleType;

    Texture2D spriteSheet = LoadTexture("source/tiles.png"); // Load your sprite sheet

    Rectangle sourceRect;

    float zoomLevel = 1;
    Vector2 mouseWorldPos;

    Camera2D cam = { 0 };



    int tileIds[GRID_SIZE][GRID_SIZE]; // Array to store the texture ID of each tile
    Rectangle grassPaletteRects[GRASS_PALETTE_SIZE];
    Rectangle pathPaletteRects[PATH_PALETTE_SIZE];
    Rectangle obstaclePaletteRects[OBSTACLE_PALETTE_SIZE];

private:
    // Add your game-specific variables and functions here
};

#endif // GAME_H
