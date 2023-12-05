#include "game.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <filesystem>

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
            randomNumber = GetRandomValue(0, 30);

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


    RenderMap();
    RenderDragRect();

    EndMode2D();


    RenderPalettes();
    RenderText();




    EndDrawing();
}


void Game::KeyPresses()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        SaveGame();
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        LoadGame();
    }
}

void Game::PlacingTiles()
{


    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !IsMouseOverPalette())
    {
        if (!isDragging)
        {
            startDragPos = GetMousePosition();
            startDragPosWorld = GetScreenToWorld2D(startDragPos, cam); // Transform to world coordinates
            isDragging = true;
        }

        endDragPos = GetMousePosition();
        endDragPosWorld = GetScreenToWorld2D(endDragPos, cam); // Transform to world coordinates
    }
    else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON) && isDragging)
    {
        isDragging = false;

        // Determine the min and max coordinates for iteration
        int minX = std::min(static_cast<int>(startDragPosWorld.x / TILE_SIZE), static_cast<int>(endDragPosWorld.x / TILE_SIZE));
        int minY = std::min(static_cast<int>(startDragPosWorld.y / TILE_SIZE), static_cast<int>(endDragPosWorld.y / TILE_SIZE));
        int maxX = std::max(static_cast<int>(startDragPosWorld.x / TILE_SIZE), static_cast<int>(endDragPosWorld.x / TILE_SIZE));
        int maxY = std::max(static_cast<int>(startDragPosWorld.y / TILE_SIZE), static_cast<int>(endDragPosWorld.y / TILE_SIZE));

        for (int i = minX; i <= maxX; ++i)
        {
            for (int j = minY; j <= maxY; ++j)
            {
                if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE)
                {
                    tileIds[i][j] = grassType;

                    std::cout << "X: " << i << " Y: " << j << "\n";
                }
            }
        }
    }
    else
    {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)
            && mouseWorldPos.x >= 0 && mouseWorldPos.x <= (TILE_SIZE * GRID_SIZE)
            && mouseWorldPos.y >= 0 && mouseWorldPos.y <= (TILE_SIZE * GRID_SIZE)
            && !IsMouseOverPalette())
        {
            int i = static_cast<int>(mouseWorldPos.x / TILE_SIZE);
            int j = static_cast<int>(mouseWorldPos.y / TILE_SIZE);

            tileIds[i][j] = grassType;

            std::cout << "X: " << i << " Y: " << j << "\n";
        }
    }
}


void Game::SelectPaletteTile()
{
    for (int i = 0; i < GRASS_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), grassPaletteRects[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            grassType = static_cast<GrassType>(i);

        }
    }

    for (int i = 0; i < PATH_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), pathPaletteRects[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + 6);
        }
    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), obstaclePaletteRects[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + 20);

        }
    }

    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON)
        && mouseWorldPos.x >= 0 && mouseWorldPos.x <= (TILE_SIZE * GRID_SIZE)
        && mouseWorldPos.y >= 0 && mouseWorldPos.y <= (TILE_SIZE * GRID_SIZE)
        && !IsMouseOverPalette())
    {
        int i = mouseWorldPos.x / TILE_SIZE;
        int j = mouseWorldPos.y / TILE_SIZE;

        grassType = static_cast<GrassType>(tileIds[i][j]);

        std::cout << "X: " << i << " Y: " << j << "\n";
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
        sourceRect.x = size * 1;
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
        sourceRect.x = size * 0;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER2:
        sourceRect.x = size * 1;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER3:
        sourceRect.x = size * 2;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER4:
        sourceRect.x = size * 3;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER5:
        sourceRect.x = size * 4;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER6:
        sourceRect.x = size * 5;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER7:
        sourceRect.x = size * 6;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER8:
        sourceRect.x = size * 7;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER9:
        sourceRect.x = size * 8;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER10:
        sourceRect.x = size * 9;
        sourceRect.y = size * 2;
        sourceRect.width = 56;
        sourceRect.height = 56;
        break;
    case WATER11:
        sourceRect.x = size * 10;
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

bool Game::IsMouseOverPalette()
{
    return (GetMouseY() >= 0 && GetMouseY() <= 250);
}


void Game::SaveGame()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string saveFilePath = (currentPath / "../Saves/SaveGrassFiles.json").string();
    nlohmann::json jsonData;

    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            int x = tileIds[rows][cols];
            jsonData["GrassType"][rows][cols] = tileIds[rows][cols];
        }
    }

    std::ofstream outFile(saveFilePath);
    outFile << std::setw(4) << jsonData;
    outFile.close();
}

void Game::LoadGame()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string loadFilePath = (currentPath / "../Saves/SaveGrassFiles.json").string();

    if (std::filesystem::exists(loadFilePath))
    {
        std::ifstream inFile(loadFilePath);
        nlohmann::json jsonData;
        inFile >> jsonData;
        inFile.close();

        for (int rows = 0; rows < GRID_SIZE; rows++)
        {
            for (int cols = 0; cols < GRID_SIZE; cols++)
            {
                tileIds[rows][cols] = jsonData["GrassType"][rows][cols];
            }
        }
    }
    else
    {
        std::cout << "Can't load file \n";
    }
}

void Game::RenderText()
{
    DrawText("Use Mouse wheel to zoom in and out", 10, 10, 20, BLACK);
    DrawText("Hold right click to move camera", 10, 40, 20, BLACK);
    DrawText("Left click on these palettes to select them", 500, 10, 20, BLACK);
    DrawText("Left click on the map to place the tiles", 500, 40, 20, BLACK);
    DrawText("Middle mouse click on the map to select that tile", 500, 70, 20, BLACK);
    DrawText("Press the space bar to save the level", 500, 100, 20, BLACK);
}

void Game::RenderMap()
{
    for (int rows = 0; rows < GRID_SIZE; rows++)
    {
        for (int cols = 0; cols < GRID_SIZE; cols++)
        {
            int x = rows * TILE_SIZE;
            int y = cols * TILE_SIZE;
            Vector2 position = { x, y };

            CheckGrassTiles(rows, cols);

            DrawTextureRec(spriteSheet, sourceRect, position, WHITE);

            DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, GRAY);
        }
    }
}

void Game::RenderPalettes()
{
    DrawRectangle(0, 0, screenWidth, ENTIRE_PALETTE_HEIGHT, { 255,0,0,100 });

    for (int i = 0; i < GRASS_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);
        sourceRect.y = 0;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        DrawTextureRec(spriteSheet, sourceRect, { grassPaletteRects[i].x,  grassPaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(grassPaletteRects[i], 2, BLACK);
    }

    for (int i = 0; i < PATH_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);
        sourceRect.y = 57;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        DrawTextureRec(spriteSheet, sourceRect, { pathPaletteRects[i].x,  pathPaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(pathPaletteRects[i], 2, BLACK);
    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);
        sourceRect.y = 114;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        DrawTextureRec(spriteSheet, sourceRect, { obstaclePaletteRects[i].x,  obstaclePaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(obstaclePaletteRects[i], 2, BLACK);
    }
}

void Game::RenderDragRect()
{
    if (isDragging)
    {
        float startX = startDragPos.x;
        float startY = startDragPos.y;
        float endX = endDragPos.x;
        float endY = endDragPos.y;

        Vector2 transformedStart = GetScreenToWorld2D({ startX, startY }, cam);
        Vector2 transformedEnd = GetScreenToWorld2D({ endX, endY }, cam);

        float width = transformedEnd.x - transformedStart.x;
        float height = transformedEnd.y - transformedStart.y;

        DrawRectangle(static_cast<int>(transformedStart.x), static_cast<int>(transformedStart.y),static_cast<int>(width), static_cast<int>(height), {0,0,255,100});
    }
}





