#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
public:

	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);

	sf::RectangleShape tile;
	int tileSize = 100;
};

