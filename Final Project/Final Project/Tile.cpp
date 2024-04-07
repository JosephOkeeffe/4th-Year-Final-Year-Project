#include "Tile.h"
#include <iostream>
#include "Globals.h"
#include "Textures.h"

void Tile::Init(sf::Vector2f& position)
{
	tile.setSize(sf::Vector2f(Global::CELL_SIZE, Global::CELL_SIZE));
	tileType = NONE;
	tile.setPosition(position);

	tile.setFillColor(sf::Color::White);
	tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
	CheckGrassType();
	
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(tile);
}

void Tile::CheckGrassType()
{

	if (cell.x == 2 && cell.y == 2)
	{
		return;
	}
	int size = 57;
	int spriteSize = 56;
	GrassType temp = GetGrassType();

	// Calculate the base X position for each grass type
	int baseX = 0;
	int baseY = 0;
	if (GetGrassType() >= GRASS1 && GetGrassType() <= GRASS5)
	{
		baseX = (GetGrassType() - GRASS1) * size;
		baseY = size * 0;
		tileType = NONE; // Added these, not tested
	}
	else if (GetGrassType() == MOUNTAINS)
	{
		baseX = 2 * size;
		baseY = size * 0;
		tileType = NONE;
	}
	else if (GetGrassType() >= BRIDGE1 && GetGrassType() <= PATH10)
	{
		baseX = (GetGrassType() - BRIDGE1) * size;
		baseY = size * 1;
		tileType = PATH;
	}
	else if (GetGrassType() >= WATER1 && GetGrassType() <= WATER13)
	{
		baseX = (GetGrassType() - WATER1) * size;
		baseY = size * 2;
		tileType = OBSTACLE;
	}
	else if (GetGrassType() >= GOLD_ORE_NODE && GetGrassType() <= OIL_POOL_NODE)
	{

		baseX = (GetGrassType() - GOLD_ORE_NODE) * size;
		baseY = size * 3;
		tileType = RESOURCE;

		if (GetGrassType() == GOLD_ORE_NODE)
		{
			resourceType = GOLD_RESOURCE;
		}
		else if (GetGrassType() == NUCLEAR_WASTE_NODE)
		{
			resourceType = URANIUM_RESOURCE;
		}
		else if (GetGrassType() == OIL_POOL_NODE)
		{
			resourceType = OIL_RESOURCE;
		}

	}

	tile.setTextureRect(sf::IntRect(baseX, baseY, spriteSize, spriteSize));

}

void Tile::DiscoverTile()
{
	isDiscovered = true;
	tile.setFillColor(sf::Color::White);
	tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
	//CheckGrassType();
}

bool Tile::GetDiscoveredStatus()
{
	return isDiscovered;
}

void Tile::SetTileType(TileType type)
{
	tileType = type;
}

TileType Tile::GetTileType()
{
	return tileType;
}

void Tile::SetGrassType(GrassType type)
{
	grassType = type;
	CheckGrassType();
}

GrassType Tile::GetGrassType()
{
	return grassType;
}

ResourceType Tile::GetResourceType()
{
	return resourceType;
}











