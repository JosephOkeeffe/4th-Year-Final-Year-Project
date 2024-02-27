#pragma once
#include <iostream>



struct Global
{
public:

    //static sf::RenderWindow* window;
   // static sf::View* gameView;

    
   
   /* static const int S_WIDTH{ 1920U };
    static const int S_HEIGHT{ 1080U };*/

    static const int S_WIDTH{ 1080U };
    static const int S_HEIGHT{ 720U };

    static const int ROWS_COLUMNS{ 50 };
    static const int CELL_SIZE{ 100 };
    static constexpr float PI = 3.14159265359f;

    inline static const std::string gameData1 = { "Game_Data_1.json" };
    inline static const std::string gameData2 = { "Game_Data_2.json" };
    inline static const std::string gameData3 = { "Game_Data_3.json" };
    
    inline static const std::string defaultTiles = { "DefaultSave.json" };
    inline static const std::string tileData1 = { "Tile_Data_1.json" };
    inline static const std::string tileData2 = { "Tile_Data_2.json" };
    inline static const std::string tileData3 = { "Tile_Data_3.json" };

    static sf::Font font;

    static void LoadFont()
    {
       font.loadFromFile("./assets/fonts/Flinton.otf");
    }

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

    static sf::Vector2i GetLocalMousePos(sf::RenderWindow& window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return mousePos;
    }

    static float distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    static sf::Vector2f CalculateVelocityUsingAnglesForParticles(float startAngle, float endAngle, sf::Sprite body, float offset)
    {
        float minOffset = startAngle;
        float maxOffset = endAngle;
        float midpoint = body.getPosition().x;
        float randomOffset = minOffset + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (maxOffset - minOffset);
        float randomAngle = (midpoint + randomOffset) * (3.14159265359 / 180.0);
        randomAngle += (offset * (3.14159265359 / 180.0));
        sf::Vector2f randomVelocity(std::cos(randomAngle), std::sin(randomAngle));

        return randomVelocity;
    }
};