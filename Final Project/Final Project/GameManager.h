#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Tile.h"
//#include "Buildings.h"

class Buildings;
class Characters;
class Headquarters;
class GoldMine;

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
            }
        }
	}

    static Tile** tiles;

    static Headquarters* headquarters;
    static std::vector<Buildings*> buildings;
    static std::vector<Characters*> units;
    static Buildings* buildingToPlace;

private:
    static sf::RenderWindow* window;
    static sf::View* gameView;
};

