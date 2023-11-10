#pragma once
#include <SFML/Graphics.hpp>
#include "TileTypes.h"
class Tile
{
public:

	TileType tileType = NONE;
	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);
	void Update();

	void SetShop(sf::Texture& texture);
	void Hover(sf::Texture& texture);
	void ResetTexture();

	sf::RectangleShape tile;
	//sf::Sprite tile;
	int tileSize = 100;
};

