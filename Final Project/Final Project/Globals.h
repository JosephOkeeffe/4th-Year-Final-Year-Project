#pragma once

struct Global
{
public:

    static const int S_WIDTH{ 1280U };
    static const int S_HEIGHT{ 720U };
    static const int ROWS_COLUMNS{ 100 };
    static const int CELL_SIZE{ 100 };
    static constexpr float PI = 3.14159265359f;

	static sf::Vector2f GetMousePos(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePos);
		return worldMousePosition;
	}
    static sf::Vector2i GetCurrentCell(sf::RenderWindow& window)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePos);

        sf::Vector2i cellPosition;
        cellPosition.x = worldMousePosition.x / Global::CELL_SIZE;
        cellPosition.y = worldMousePosition.y / Global::CELL_SIZE;

        return cellPosition;
    }

};