#pragma once
#include <SFML/Graphics.hpp>
class Tile
{
public:

	enum TileType
	{
		NONE,
		SHOP,
	};
	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);

	void SetShop();

	sf::RectangleShape tile;
	int tileSize = 100;
};

