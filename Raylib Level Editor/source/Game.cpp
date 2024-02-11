#include "game.h"
#include <fstream>
#include "json.hpp"


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
            // Makes the map look natural to start
            randomNumber = GetRandomValue(0, 30);

            if (randomNumber <= 7)
            {
                tileIds[rows][cols] = 0;
            }
            else if (randomNumber >= 8 && randomNumber <= 14)
            {
                tileIds[rows][cols] = 1;
            }
            else if (randomNumber >= 15 && randomNumber <= 20)
            {
                tileIds[rows][cols] = 3;
            }
            else if (randomNumber >= 21 && randomNumber <= 24)
            {
                tileIds[rows][cols] = 4;
            }
            else if (randomNumber >= 25 && randomNumber <= 29)
            {
                tileIds[rows][cols] = 5;
            }
            else if (randomNumber == 30)
            {
                tileIds[rows][cols] = 2;
            }
            
            // Makes the map look blank to start
            /*tileIds[rows][cols] = 0;*/

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

    for (int i = 0; i < RESOURCE_PALETTE_SIZE; i++)
    {
        resourcePaletteRects[i] = { static_cast<float>(10 + i * (TILE_SIZE + 10)), 250, TILE_SIZE, TILE_SIZE };
    }


}

void Game::Update()
{
    mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

    KeyPresses();

    if (!saveMenuOpen || !loadMenuOpen) 
    {
        SelectPaletteTile();

        PlacingTiles();

        MoveCamera();
        Zoom();

        PlacingTiles();
    }
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
    RenderSaveButton();
    RenderLoadButton();

    if (saveMenuOpen){RenderSaveMenu();}
    if (loadMenuOpen){RenderLoadMenu();}

    if (delayTimer > 0.0f)
    {
        delayTimer -= GetFrameTime();

        if (delayTimer <= 0.0f)
        {
            saveMenuOpen = false; 
            loadMenuOpen = false;
        }
    }



    EndDrawing();
}


void Game::KeyPresses()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        SaveGame();
    }

    if (IsKeyPressed(KEY_Q))
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string saveFilePath;

        saveFilePath = (currentPath / "../Saves/" / defaultData).string();

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

    if (IsKeyPressed(KEY_W))
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string loadFilePath;


        loadFilePath = (currentPath / "../Saves/" / defaultData).string();

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

    if (IsKeyPressed(KEY_ENTER))
    {
        LoadGame();
    }
}

void Game::PlacingTiles()
{

    if (saveMenuOpen || loadMenuOpen) { return; }

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
            grassType = static_cast<GrassType>(i + BRIDGE1);
        }
    }

    for (int i = 0; i < OBSTACLE_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), obstaclePaletteRects[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + WATER1);

        }
    }

    for (int i = 0; i < RESOURCE_PALETTE_SIZE; i++)
    {
        if (CheckCollisionPointRec(GetMousePosition(), resourcePaletteRects[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            grassType = static_cast<GrassType>(i + GOLD_ORE);

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
    }
}

void Game::CheckGrassTiles(int t_rows, int t_cols)
{
    int size = TILE_SIZE + 1;
    int offset = 0;

    if (tileIds[t_rows][t_cols] >= GRASS1 && tileIds[t_rows][t_cols] < BRIDGE1)
    {
        offset = 0;
        sourceRect.y = size * 0;
    }
    else if (tileIds[t_rows][t_cols] >= BRIDGE1 && tileIds[t_rows][t_cols] < WATER1)
    {
        offset = BRIDGE1;
        sourceRect.y = size * 1;
    }
    else if (tileIds[t_rows][t_cols] >= WATER1 && tileIds[t_rows][t_cols] <= WATER13)
    {
        offset = WATER1;
        sourceRect.y = size * 2;
    }
    else if (tileIds[t_rows][t_cols] >= GOLD_ORE && tileIds[t_rows][t_cols] <= OIL)
    {
        offset = GOLD_ORE;
        sourceRect.y = size * 3;
    }

    sourceRect.x = size * (tileIds[t_rows][t_cols] - offset);
    sourceRect.width = 56;
    sourceRect.height = 56;

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
    return (GetMouseY() >= 0 && GetMouseY() <= ENTIRE_PALETTE_HEIGHT);
}


void Game::SaveGame()
{
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string saveFilePath;
    if (selectedSlot == 0)
    {
        saveFilePath = (currentPath / "../Saves/" / tileData1).string();
    }
    else if (selectedSlot == 1)
    {
        saveFilePath = (currentPath / "../Saves/" / tileData2).string();
    }
    else if (selectedSlot == 2)
    {
        saveFilePath = (currentPath / "../Saves/" / tileData3).string();
    }
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
    std::string loadFilePath;

    if (selectedSlot == 0)
    {
        loadFilePath = (currentPath / "../Saves/" / tileData1).string();
    }
    else if (selectedSlot == 1)
    {
        loadFilePath = (currentPath / "../Saves/" / tileData2).string();
    }
    else if (selectedSlot == 2)
    {
        loadFilePath = (currentPath / "../Saves/" / tileData3).string();
    }

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

    for (int i = 0; i < RESOURCE_PALETTE_SIZE ; i++)
    {
        sourceRect.x = i * (TILE_SIZE + 1);
        sourceRect.y = 171;
        sourceRect.width = TILE_SIZE;
        sourceRect.height = TILE_SIZE;

        DrawTextureRec(spriteSheet, sourceRect, { resourcePaletteRects[i].x,  resourcePaletteRects[i].y }, WHITE);
        DrawRectangleLinesEx(resourcePaletteRects[i], 2, BLACK);
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

void Game::RenderSaveButton()
{
    const int x = screenWidth * 0.8;
    const int y = screenHeight * 0.01;
    const int width = 250;
    const int height = 50;

    Rectangle saveRect = { x, y, width, height };
    DrawRectangleRec(saveRect, LIGHTGRAY);
    DrawRectangleLines(x, y, width, height, DARKGRAY);
    DrawText("Save Map", x + 22, y + 5, 40, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), saveRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        saveMenuOpen = !saveMenuOpen;
        loadMenuOpen = false;
    }
}

void Game::RenderLoadButton()
{
    const int x = screenWidth * 0.8;
    const int y = screenHeight * 0.07;
    const int width = 250;
    const int height = 50;

    Rectangle saveRect = { x, y, width, height };
    DrawRectangleRec(saveRect, LIGHTGRAY);
    DrawRectangleLines(x, y, width, height, DARKGRAY);
    DrawText("Load Map", x + 22, y + 5, 40, BLACK);

    if (CheckCollisionPointRec(GetMousePosition(), saveRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        loadMenuOpen = !loadMenuOpen;
        saveMenuOpen = false;
    }
}

//void Game::SaveGameWorldAsPNG(const char* filename)
//{
//    // Specify the desired path
//    const char* savePath = "../Saves/";
//
//    // Concatenate the path and filename
//    char fullPath[256];
//    snprintf(fullPath, sizeof(fullPath), "%s%s", savePath, filename);
//
//    // Take a screenshot of the current render
//    TakeScreenshot(fullPath);
//
//    // Print a message indicating successful save
//    printf("Game world saved as %s\n", fullPath);
//}

void Game::RenderSaveMenu()
{
    const int width = 300;
    const int height = 180;
    const int menuX = (screenWidth / 2) - (width / 2);
    const int menuY = (screenHeight / 2);
    const int buttonHeight = 40;
    const int buttonSpacing = 10;

    DrawRectangle(menuX, menuY, width, height, GRAY);
    DrawRectangleLines(menuX, menuY, width, height, DARKGRAY);
    DrawText("Save Menu", menuX + 70, menuY + 5, 25, BLACK);

    for (int i = 0; i < 3; i++)
    {
        Rectangle buttonRect = { 
            menuX + buttonSpacing, 
            menuY + 30 + i * (buttonHeight + buttonSpacing),
            width - (buttonSpacing * 2),
            buttonHeight };
        DrawRectangleRec(buttonRect, LIGHTGRAY);
        DrawRectangleLinesEx(buttonRect, 2, BLACK);
        DrawText(TextFormat("Save %d", i + 1), buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selectedSlot = i;
            SaveGame();
            CloseSaveAndLoadMenuAfterDelay(0.5);
        }
    }
}

void Game::RenderLoadMenu()
{
    const int width = 300;
    const int height = 180;
    const int menuX = (screenWidth / 2) - (width / 2);
    const int menuY = (screenHeight / 2);
    const int buttonHeight = 40;
    const int buttonSpacing = 10;

    DrawRectangle(menuX, menuY, width, height, GRAY);
    DrawRectangleLines(menuX, menuY, width, height, DARKGRAY);
    DrawText("Load Menu", menuX + 70, menuY + 5, 25, BLACK);

    for (int i = 0; i < 3; i++)
    {
        Rectangle buttonRect = {
            menuX + buttonSpacing,
            menuY + 30 + i * (buttonHeight + buttonSpacing),
            width - (buttonSpacing * 2),
            buttonHeight };
        DrawRectangleRec(buttonRect, LIGHTGRAY);
        DrawRectangleLinesEx(buttonRect, 2, BLACK);
        DrawText(TextFormat("Load %d", i + 1), buttonRect.x + 10, buttonRect.y + 10, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), buttonRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            selectedSlot = i;
            LoadGame();
            CloseSaveAndLoadMenuAfterDelay(0.5);
        }
    }
}

void Game::CloseSaveAndLoadMenuAfterDelay(float delay)
{
    delayTimer = delay;
}


