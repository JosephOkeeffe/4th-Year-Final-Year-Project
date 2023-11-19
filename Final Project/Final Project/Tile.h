#pragma once
#include <SFML/Graphics.hpp>
#include "TileTypes.h"
class Tile
{
public:

	Tile();
	TileType tileType = NONE;
	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);
	void Update();

	void CheckType();
	void SetShop();
	void Hover(sf::Texture& texture);
	void ResetTexture();
	void SetType(TileType type);
	TileType GetType();
	int defaultTile = 0;
	sf::RectangleShape tile;
	//sf::Sprite tile;
	int tileSize = 100;
};

