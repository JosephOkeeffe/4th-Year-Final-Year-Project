#pragma once
#include <iostream>

struct Global
{
public:

    static const int S_WIDTH{ 1920U };
    static const int S_HEIGHT{ 1080U };

    //static const int S_WIDTH{ 1080U };
    //static const int S_HEIGHT{ 720U };

    static const int ROWS_COLUMNS{ 50 };
    static const int CELL_SIZE{ 100 };
    static constexpr float PI = 3.14159265359f;

    inline static const std::string gameData1 = { "Game_Data_1.json" };
    inline static const std::string gameData2 = { "Game_Data_2.json" };
    inline static const std::string gameData3 = { "Game_Data_3.json" };
    
    inline static const std::string tileData1 = { "Tile_Data_1.json" };
    inline static const std::string tileData2 = { "Tile_Data_2.json" };
    inline static const std::string tileData3 = { "Tile_Data_3.json" };

	static sf::Vector2f GetMousePos(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePos);
		return worldMousePosition;
	}

    static sf::Vector2f GetWindowMousePos(sf::RenderWindow& window, sf::View& view)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePos, view);
        return worldMousePosition;
    }

    static sf::Vector2i GetCurrentCell(sf::RenderWindow& window, sf::View& view)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePos, view);
        sf::Vector2i cellPosition;
        cellPosition.x = worldMousePosition.x / Global::CELL_SIZE;
        cellPosition.y = worldMousePosition.y / Global::CELL_SIZE;

        return cellPosition;
    }

   static enum TileType
    {
        NONE,
        SHOP,
    };

};