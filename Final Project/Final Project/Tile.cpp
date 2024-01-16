#include "Tile.h"
#include <iostream>
#include "Globals.h"
#include "Textures.h"
#include "ResourceManagement.h"

Tile::Tile()
{
	defaultTile = rand() % 30;
}

void Tile::Init(sf::Vector2f& position)
{
	tile.setSize(sf::Vector2f(Global::CELL_SIZE, Global::CELL_SIZE));
	tile.setPosition(position);
	tileType = NONE;
	tile.setPosition(position);
	SetupGrassTiles();

	CheckTileType();
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(tile);
	
}

void Tile::Update()
{
	
}

void Tile::CheckTileType()
{
	switch (GetTileType())
	{
	case NONE:
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
		CheckGrassType();
		break;
	case OBSTACLE:
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));

		CheckGrassType();
		break;
	case PATH:
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));

		CheckGrassType();
		break;
	case SHOP:
		tile.setFillColor(sf::Color::White);
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
		break;
	default:
		break;
	}
}

void Tile::CheckGrassType()
{
	int size = 57;
	int spriteSize = 56;
	GrassType temp = GetGrassType();

	// Calculate the base X position for each grass type
	int baseX = 0;
	if (GetGrassType() >= GRASS1 && GetGrassType() <= GRASS5)
	{
		baseX = (GetGrassType() - GRASS1) * size;
	}
	else if (GetGrassType() == MOUNTAINS)
	{
		baseX = 2 * size;
	}
	else if (GetGrassType() >= BRIDGE1 && GetGrassType() <= PATH10)
	{
		baseX = (GetGrassType() - BRIDGE1) * size;
	}
	else if (GetGrassType() >= WATER1 && GetGrassType() <= WATER13)
	{
		baseX = (GetGrassType() - WATER1) * size;
	}

	int baseY = 0;
	if (GetGrassType() >= GRASS1 && GetGrassType() <= MOUNTAINS)
	{
		baseY = size * 0;
	}
	else if (GetGrassType() >= BRIDGE1 && GetGrassType() <= PATH10)
	{
		baseY = size * 1;
	}
	else if (GetGrassType() >= WATER1 && GetGrassType() <= WATER13)
	{
		baseY = size * 2;
	}
	tile.setTextureRect(sf::IntRect(baseX, baseY, spriteSize, spriteSize));

}

void Tile::SetShop()
{
	if (ResourceManagement::isPlacingShop)
	{
		SetTileType(SHOP);
		CheckTileType();
		ResourceManagement::AddShops(1);
		ResourceManagement::isPlacingShop = false;
	}
}

void Tile::Hover(sf::Texture& texture)
{
	if (GetTileType() != SHOP)
	{
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setFillColor(sf::Color(0,255,0,100));
		tile.setTexture(&texture);
	}
}

void Tile::ResetTexture()
{
	SetTileType(GetTileType());
	//CheckGrassType();
	CheckTileType();
}

// Storage building that can hold a set amount
// Miner building that collects resources and can only be built on certain nodes
// Fishing buildings 

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
}

void Tile::SetTileType(TileType type)
{
	tileType = type;
	CheckTileType();
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











