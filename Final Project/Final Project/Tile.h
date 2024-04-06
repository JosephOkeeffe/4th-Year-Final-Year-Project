#pragma once
#include <SFML/Graphics.hpp>
#include "TileTypes.h"
#include "Shader.h"

class Tile
{
public:


	void Init(sf::Vector2f& position);
	void Render(sf::RenderWindow& window);

	void CheckGrassType();
	void DiscoverTile();
	bool GetDiscoveredStatus();
	void SetGrassType(GrassType type);
	void SetTileType(TileType type);

	GrassType GetGrassType();
	ResourceType GetResourceType();
	TileType GetTileType();

	sf::Vector2i cell;
	sf::RectangleShape tile;
	//sf::Sprite tile;
	int tileSize = 100;

	float gCost; // Cost from the start node to this node
	float hCost; // Cost from this node to the goal node (heuristic)
	Tile* parent; // Parent node in the path

	TileType tileType = NONE;



private:

	bool isDiscovered = true;
	GrassType grassType = GRASS1;
	ResourceType resourceType = NO_RESOURCE;
	Shader shader;

	static bool isShaderInitialized;
	static sf::Texture shaderTexture;

};

