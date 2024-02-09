#include "Tile.h"
#include <iostream>
#include "Globals.h"
#include "Textures.h"
#include "ResourceManagement.h"

Tile::Tile()
{
	defaultTile = rand() % 32;
}

void Tile::Init(sf::Vector2f& position)
{
	tile.setSize(sf::Vector2f(Global::CELL_SIZE, Global::CELL_SIZE));
	tileType = NONE;
	tile.setPosition(position);
	SetupGrassTiles();

	tile.setFillColor(sf::Color::White);
	tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
	CheckGrassType();
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(tile);

	if (!isDiscovered)
	{
		tile.setTexture(&Textures::GetInstance().GetTexture("fog"));
		//tile.setTextureRect(sf::IntRect(0, 0, 56, 56));
	}          
}

void Tile::Update()
{
	
}

//void Tile::CheckTileType()
//{
//	switch (GetTileType())
//	{
//	case NONE:
//		tile.setFillColor(sf::Color::White);
//		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
//		CheckGrassType();
//		break;
//	case OBSTACLE:
//		tile.setFillColor(sf::Color::White);
//		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
//		CheckGrassType();
//		break;
//	case PATH:
//		tile.setFillColor(sf::Color::White);
//		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
//		CheckGrassType();
//		break;
//	default:
//		break;
//	}
//}

void Tile::CheckGrassType()
{
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
	else if (GetGrassType() >= GOLD_ORE && GetGrassType() <= OIL_POOL)
	{
	
			baseX = (GetGrassType() - GOLD_ORE) * size;
			baseY = size * 3;
			tileType = RESOURCE;
		
	}

	tile.setTextureRect(sf::IntRect(baseX, baseY, spriteSize, spriteSize));

}

// Storage building that can hold a set amount
// Miner building that collects resources and can only be built on certain nodes


// MAKE DEFAULT MAP SO THIS CAN GO SOON
void Tile::SetupGrassTiles()
{
	if (defaultTile <= 10)
	{
		SetGrassType(GRASS1);
	}
	else if (defaultTile >= 11 && defaultTile <= 15)
	{
		SetGrassType(GRASS2);
	}
	else if (defaultTile >= 16 && defaultTile <= 20)
	{
		SetGrassType(GRASS3);
	}
	else if (defaultTile >= 21 && defaultTile <= 23)
	{
		SetGrassType(GRASS4);
	}
	else if (defaultTile >= 24 && defaultTile <= 28)
	{
		SetGrassType(GRASS5);
	}
	else if (defaultTile >= 29 && defaultTile <= 30)
	{
		SetGrassType(MOUNTAINS);
	}
	else
	{
		SetGrassType(GOLD_ORE);
	}
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
	//CheckTileType();
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











