#include "game.h"
#include <iostream>

// got some help from https://github.com/raylib-extras/examples-c/blob/main/mouse_zoom/mouse_zoom.c

Game::Game()
{
    Init();
}

Game::~Game()
{
}

void Game::Init()
{
    cam.zoom = 1;

    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            tileIds[rows][cols] = 0;
        }
    }

    for (int i = 0; i < GRASS_PALETTE_SIZE; i++)
    {
        grassPaletteRects[i] = { static_cast<float>(10 + i * (TILE_SIZE + 10)), 70, TILE_SIZE, TILE_SIZE };

    }

    for (int i = 0; i < PATH_PALETTE_SIZE; i++)
    {
        pathPaletteRects[i] = { static_cast<float>(10 + i * (TILE_SIZE + 10)), 130, TILE_SIZE, TILE_SIZE };

    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        obstaclePaletteRects[i] = { static_cast<float>(10 + i * (TILE_SIZE + 10)), 190, TILE_SIZE, TILE_SIZE };

    }
}

void Game::Update()
{
    mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

    KeyPresses();
    SelectPaletteTile();

    PlacingTiles();

    MoveCamera();
    Zoom();

    PlacingTiles();
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(cam);

    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            int x = rows * TILE_SIZE;
            int y = cols * TILE_SIZE;
            Vector2 position = { x, y };

            CheckGrassTiles(rows, cols);
          //  CheckObstacleTiles(rows, cols);

            DrawTextureRec(spriteSheet, sourceRect, position, WHITE);

            DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, GRAY);
        }
    }

  

    EndMode2D();



    DrawText("Use Mouse wheel to zoom in and out", 10, 10, 20, BLACK);
    DrawText("Hold right click to move camera", 10, 40, 20, BLACK);

    for (int i = 0; i < GRASS_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);  // Assuming each palette tile has the same width as TILE_SIZE
        sourceRect.y = 0;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        // Draw the palette tile with the sprite sheet and selected source rectangle
        DrawTextureRec(spriteSheet, sourceRect, { grassPaletteRects[i].x,  grassPaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(grassPaletteRects[i], 2, BLACK);
    }

    for (int i = 0; i < PATH_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);  // Assuming each palette tile has the same width as TILE_SIZE
        sourceRect.y = 57;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        // Draw the palette tile with the sprite sheet and selected source rectangle
        DrawTextureRec(spriteSheet, sourceRect, { pathPaletteRects[i].x,  pathPaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(pathPaletteRects[i], 2, BLACK);
    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);  // Assuming each palette tile has the same width as TILE_SIZE
        sourceRect.y = 114;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        // Draw the palette tile with the sprite sheet and selected source rectangle
        DrawTextureRec(spriteSheet, sourceRect, { obstaclePaletteRects[i].x,  obstaclePaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(obstaclePaletteRects[i], 2, BLACK);
    }


    EndDrawing();
}

void Game::KeyPresses()
{

}

void Game::PlacingTiles()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)
        && mouseWorldPos.x >= 0 && mouseWorldPos.x <= (TILE_SIZE * GRID_SIZE)
        && mouseWorldPos.y >= 0 && mouseWorldPos.y <= (TILE_SIZE * GRID_SIZE))
    {
        int i = mouseWorldPos.x / TILE_SIZE;
        int j = mouseWorldPos.y / TILE_SIZE;

        tileIds[i][j] = grassType;

        std::cout << "X: " << i << " Y: " << j << "\n";
    }
}

void Game::SelectPaletteTile()
{
    for (int i = 0; i < GRASS_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), grassPaletteRects[i]) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            grassType = static_cast<GrassType>(i);
  
        }
    }

    for (int i = 0; i < PATH_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), pathPaletteRects[i]) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + 6);
        }
    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), obstaclePaletteRects[i]) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + 20);

        }
    }
}

void Game::CheckGrassTiles(int t_rows, int t_cols)
{
    int size = TILE_SIZE + 1;
    switch (tileIds[t_rows][t_cols])
    {
    case GRASS1:
        sourceRect.x = size * 0;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case GRASS2:
        sourceRect.x = size * 1;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case MOUNTAINS:
        sourceRect.x = size * 2;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case GRASS3:
        sourceRect.x = size * 3;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case GRASS4:
        sourceRect.x = size * 4;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case GRASS5:
        sourceRect.x = size * 5;
        sourceRect.y = 0;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case BRIDGE1:
        sourceRect.x = size * 0;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case BRIDGE2:
        sourceRect.x = size* 1;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case BRIDGE3:
        sourceRect.x = size * 2;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case BRIDGE4:
        sourceRect.x = size * 3;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH1:
        sourceRect.x = size * 4;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH2:
        sourceRect.x = size * 5;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH3:
        sourceRect.x = size * 6;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH4:
        sourceRect.x = size * 7;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH5:
        sourceRect.x = size * 8;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH6:
        sourceRect.x = size * 9;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH7:
        sourceRect.x = size * 10;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH8:
        sourceRect.x = size * 11;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH9:
        sourceRect.x = size * 12;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case PATH10:
        sourceRect.x = size * 13;
        sourceRect.y = size;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER1:
        sourceRect.x = size* 0;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER2:
        sourceRect.x = size* 1;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER3:
        sourceRect.x = size* 2;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER4:
        sourceRect.x = size* 3;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER5:
        sourceRect.x = size* 4;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER6:
        sourceRect.x = size* 5;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER7:
        sourceRect.x = size* 6;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER8:
        sourceRect.x = size* 7;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER9:
        sourceRect.x = size* 8;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER10:
        sourceRect.x = size* 9;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER11:
        sourceRect.x = size* 10;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER12:
        sourceRect.x = size * 11;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER13:
        sourceRect.x = size * 12;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    default:
        break;
    }
 
}
//void Game::CheckObstacleTiles(int t_rows, int t_cols)
//{
//    switch (tileIds[t_rows][t_cols])
//    {
//    case WATER1:
//        sourceRect.x = 0;
//        sourceRect.y = 57;
//        sourceRect.width = 56;
//        sourceRect.height = 56;
//        break;
//    case WATER2:
//        break;
//    case WATER3:
//        break;
//    case WATER4:
//        break;
//    case WATER5:
//        break;
//    case WATER6:
//        break;
//    case WATER7:
//        break;
//    case WATER8:
//        break;
//    case WATER9:
//        break;
//    case WATER10:
//        break;
//    case WATER11:
//        break;
//    default:
//        break;
//    }
//}
void Game::Zoom()
{
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        cam.offset = GetMousePosition();
        cam.target = mouseWorldPos;
        cam.zoom += wheel * 0.125f;

        if (cam.zoom < 0.125f)
        {
            cam.zoom = 0.125f;
        }
    }
}

void Game::MoveCamera()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / cam.zoom);

        cam.target = Vector2Add(cam.target, delta);
    }
}


