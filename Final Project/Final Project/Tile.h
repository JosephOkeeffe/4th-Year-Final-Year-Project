#pragma once
#include <SFML/Graphics.hpp>
#include "TileTypes.h"
#include "Shader.h"
class Tile
{
public:

	Tile();

	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);
	void Update();

	void CheckGrassType();
	void SetupGrassTiles();
	void DiscoverTile();
	bool GetDiscoveredStatus();

	GrassType GetGrassType();
	ResourceType GetResourceType();
	void SetGrassType(GrassType type);
	void SetTileType(TileType type);
	TileType GetTileType();
	int defaultTile = 0;
	int pathTile = 0;
	int obstacleTile = 0;
	sf::RectangleShape tile;
	//sf::Sprite tile;
	int tileSize = 100;

private:

	bool isDiscovered = false;
	TileType tileType = NONE;
	GrassType grassType = GRASS1;
	ResourceType resourceType = NO_RESOURCE;
	Shader shader;

	static bool isShaderInitialized;
	static sf::Texture shaderTexture;

};

