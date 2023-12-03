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
	//tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
	tile.setPosition(position);

	
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
	if (GetTileType() == NONE)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));

		if (defaultTile <= 10)
		{
			grassType = GRASS1;
		}
		else if (defaultTile >= 11 && defaultTile <= 15)
		{
			grassType = GRASS2;
		}
		else if (defaultTile >= 16 && defaultTile <= 20)
		{
			grassType = GRASS3;
		}
		else if (defaultTile >= 21 && defaultTile <= 23)
		{
			grassType = GRASS4;
		}
		else if (defaultTile >= 24 && defaultTile <= 28)
		{
			grassType = GRASS5;
		}
		else if (defaultTile >= 29 && defaultTile <= 30)
		{
			grassType = MOUNTAINS;
		}

		CheckGrassType();
	}
	else if (GetTileType() == SHOP)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
	}
}

void Tile::CheckGrassType()
{
	switch (grassType)
	{
	case GRASS1:
		tile.setTextureRect(sf::IntRect(0, 0, 56, 56));
		break;
	case GRASS2:
		tile.setTextureRect(sf::IntRect(57, 0, 56, 56));
		break;
	case GRASS3:
		tile.setTextureRect(sf::IntRect(171, 0, 56, 56));
		break;
	case GRASS4:
		tile.setTextureRect(sf::IntRect(228, 0, 56, 56));
		break;
	case GRASS5:
		tile.setTextureRect(sf::IntRect(285, 0, 56, 56));
		break;
	case MOUNTAINS:
		tile.setTextureRect(sf::IntRect(114, 0, 56, 56));
		break;
	default:
		break;
	}
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
	if (GetTileType() == NONE)
	{
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setFillColor(sf::Color(0,255,0,100));
		tile.setTexture(&texture);
	}
}

void Tile::ResetTexture()
{
	SetTileType(NONE);
	CheckTileType();
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











