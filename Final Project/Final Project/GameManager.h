#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Tile.h"

class Buildings;
class Characters;
class Headquarters;
class GoldMine;
class Miner;
class Enemy;
class Formation;

class GameManager
{
public:
    static void SetWindow(sf::RenderWindow& _window) { window = &_window; }
    static void SetView(sf::View& _gameView) { gameView = &_gameView; }
    static void SetTiles(Tile** _tiles) { tiles = _tiles; }

    static sf::RenderWindow* GetWindow() { return window; }
    static sf::View* GetView() { return gameView; }

	static void InitTiles()
	{
        srand(time(nullptr));

        tiles = new Tile * [Global::ROWS_COLUMNS];

        for (int i = 0; i < Global::ROWS_COLUMNS; i++)
        {
            tiles[i] = new Tile[Global::ROWS_COLUMNS];
        }

        for (int row = 0; row < Global::ROWS_COLUMNS; row++)
        {
            for (int col = 0; col < Global::ROWS_COLUMNS; col++)
            {
                sf::Vector2f temp = { static_cast<float>(row * Global::CELL_SIZE), static_cast<float>(col * Global::CELL_SIZE) };
                tiles[row][col].Init(temp);
                tiles[row][col].cell = { row,col };
            }
        }
	}

    static std::vector<Tile*> FindPath(Tile* startTile, Tile* goalTile, bool isWorker)
    {
        std::vector<Tile*> openSet;
        std::vector<Tile*> closedSet;

        openSet.push_back(startTile);

        while (!openSet.empty()) 
        {
            Tile* currentTile = openSet[0];
            for (Tile* tile : openSet) 
            {
                if (tile->gCost + tile->hCost < currentTile->gCost + currentTile->hCost) 
                {
                    currentTile = tile;
                }
            }

            openSet.erase(std::remove(openSet.begin(), openSet.end(), currentTile), openSet.end());
            closedSet.push_back(currentTile);

            if (currentTile == goalTile) 
            {
                std::vector<Tile*> path;
                while (currentTile != startTile) 
                {
                    path.push_back(currentTile);
                    currentTile = currentTile->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (Tile* neighbor : GetNeighbors(currentTile, isWorker)) 
            {
                if (std::find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end()) 
                {
                    continue; 
                }

                float tentativeGCost = currentTile->gCost + CalculateMoveCost(currentTile, neighbor);

                if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end() || tentativeGCost < neighbor->gCost) 
                {
                    neighbor->gCost = tentativeGCost;
                    neighbor->hCost = CalculateHCost(neighbor, goalTile);
                    neighbor->parent = currentTile;

                    if (std::find(openSet.begin(), openSet.end(), neighbor) == openSet.end()) 
                    {
                        openSet.push_back(neighbor);
                    }
                }
            }
        }

        return std::vector<Tile*>();
    }

    static float CalculateHCost(Tile* tile, Tile* goalTile)
    {
        float xCost = std::abs(tile->tile.getPosition().x - goalTile->tile.getPosition().x);
        float yCost = std::abs(tile->tile.getPosition().y - goalTile->tile.getPosition().y);
        return xCost + yCost;
    }

    static std::vector<Tile*> GetNeighbors(Tile* tile, bool isWorker)
    {
        std::vector<Tile*> neighbors;

        sf::Vector2f currentPosition = tile->tile.getPosition();
        int tileSize = tile->tileSize;

        std::vector<sf::Vector2i> offsets = {
            {0, -1}, // Up
            {-1, 0}, // Left
            {1, 0},  // Right
            {0, 1},  // Down
            {-1, -1}, // Top left
            {1, -1},  // Top right
            {-1, 1},  // Bottom left
            {1, 1}    // Bottom right
        };

        for (const sf::Vector2i& offset : offsets)
        {
            sf::Vector2f neighborPosition = currentPosition + sf::Vector2f(offset.x * tileSize, offset.y * tileSize);

            if (neighborPosition.x >= 0 && neighborPosition.x < Global::ROWS_COLUMNS * tileSize &&
                neighborPosition.y >= 0 && neighborPosition.y < Global::ROWS_COLUMNS * tileSize)
            {
                int neighborRow = static_cast<int>(neighborPosition.x / tileSize);
                int neighborCol = static_cast<int>(neighborPosition.y / tileSize);

                

                if (GameManager::tiles[neighborRow][neighborCol].GetTileType() != OBSTACLE)
                {
                    if (isWorker)
                    {
                        neighbors.push_back(&GameManager::tiles[neighborRow][neighborCol]);
                       
                    }
                    else
                    {
                        if (GameManager::tiles[neighborRow][neighborCol].GetTileType() != TILE_USED_UP)
                        {
                            neighbors.push_back(&GameManager::tiles[neighborRow][neighborCol]);
                        }
                    }
                   
                }
            }
        }

        return neighbors;
    }

    static float CalculateMoveCost(Tile* fromTile, Tile* toTile)
    {
        sf::Vector2f fromPosition = fromTile->tile.getPosition();
        sf::Vector2f toPosition = toTile->tile.getPosition();

        float dx = std::abs(toPosition.x - fromPosition.x);
        float dy = std::abs(toPosition.y - fromPosition.y);

        float diagonalCost = 1.0;
        float straightCost = 1.0;

        float tileCost = 1.0; 
        if (toTile->GetTileType() == PATH)
        {
            tileCost = 0.5;
        }

        return straightCost * (dx + dy) + (diagonalCost - 2 * straightCost) * std::min(dx, dy) + tileCost;
    }


   

    static Tile** tiles;

    static Headquarters* headquarters;
    static std::vector<Buildings*> buildings;
    static std::vector<Characters*> units;
    static std::vector<Enemy*> enemies;
    static Buildings* buildingToPlace;
    static std::vector<Formation*> formations;

private:
    static sf::RenderWindow* window;
    static sf::View* gameView;
};

