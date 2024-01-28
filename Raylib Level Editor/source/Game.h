#ifndef GAME_H
#define GAME_H

#define TILE_SIZE 56
#define GRID_SIZE 50

#define MIN_ZOOM 0.3f
#define MAX_ZOOM 1.0f
#define ZOOM_INCREMENT 0.1f

#define GRASS_PALETTE_SIZE 6
#define PATH_PALETTE_SIZE 18
#define OBSTACLE_PALETTE_SIZE 13
#define RESOURCE_PALETTE_SIZE 3
#define ENTIRE_PALETTE_HEIGHT 320

const int screenWidth = (TILE_SIZE * GRID_SIZE) / 2;
const int screenHeight = (TILE_SIZE * GRID_SIZE) / 3; // THESE CAN BREAK THE GAME IF CHANGED

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h";
#include <iostream>
#include <filesystem>

enum GrassType
{
    GRASS1, // 0
    GRASS2,
    MOUNTAINS,
    GRASS3,
    GRASS4,
    GRASS5, // 5

    BRIDGE1, // 6
    BRIDGE2,
    BRIDGE3,
    BRIDGE4,
    BRIDGE5,
    BRIDGE6,
    BRIDGE7,
    BRIDGE8,
    PATH1,
    PATH2,
    PATH3,
    PATH4,
    PATH5,
    PATH6,
    PATH7,
    PATH8,
    PATH9,
    PATH10, // 23

    WATER1, // 24
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

    GOLD_ORE,
    TOXIC_WASTE,
    OIL,

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

    void SelectPaletteTile();

    void PlacingTiles();
    void CheckGrassTiles(int t_rows, int t_cols);
    //void CheckObstacleTiles(int t_rows, int t_cols);
    void Zoom();
    void MoveCamera();
    bool IsMouseOverPalette();

    void SaveGame();
    void LoadGame();

    void RenderText();
    void RenderMap();
    void RenderPalettes();
    void RenderDragRect();
    void RenderSaveButton();
    void RenderLoadButton();
    //void SaveGameWorldAsPNG(const char* filename);
    void RenderSaveMenu();
    void RenderLoadMenu();
    void CloseSaveAndLoadMenuAfterDelay(float delay);
    float delayTimer = 0.0f;
    
     bool isDragging = false;
     Vector2 startDragPos;
     Vector2 endDragPos;   
     Vector2 startDragPosWorld;
     Vector2 endDragPosWorld;


   // TileType tileType = NONE;
    GrassType grassType = GRASS1;
   // ObstacleType obstacleType;



    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string tileFileString = (currentPath / "../tiles.png").string();

    const char* tileFileCString = tileFileString.c_str();

    Texture2D spriteSheet = LoadTexture(tileFileCString);



    Rectangle sourceRect;

    float zoomLevel = 1;
    Vector2 mouseWorldPos;

    Camera2D cam = { 0 };

    bool saveMenuOpen = false;
    bool loadMenuOpen = false;

    int selectedSlot = 0;

    int randomNumber = 0;
    int tileIds[GRID_SIZE][GRID_SIZE]; // Array to store the texture ID of each tile
    Rectangle grassPaletteRects[GRASS_PALETTE_SIZE];
    Rectangle pathPaletteRects[PATH_PALETTE_SIZE];
    Rectangle obstaclePaletteRects[OBSTACLE_PALETTE_SIZE];
    Rectangle resourcePaletteRects[RESOURCE_PALETTE_SIZE];

private:
    std::string tileData1 = { "Tile_Data_1.json" };
    std::string tileData2 = { "Tile_Data_2.json" };
    std::string tileData3 = { "Tile_Data_3.json" };
};

#endif 
