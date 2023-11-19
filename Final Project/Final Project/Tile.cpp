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

	
	CheckType();

	
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(tile);
	
}

void Tile::Update()
{
}

void Tile::CheckType()
{
	if (GetType() == NONE)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));

		if (defaultTile <= 10)
		{
			tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		}
		else if (defaultTile >= 11 && defaultTile <= 15)
		{
			tile.setTextureRect(sf::IntRect(0, 200, 200, 200));
		}
		else if (defaultTile >= 16 && defaultTile <= 20)
		{
			tile.setTextureRect(sf::IntRect(202, 0, 200, 200));
		}
		else if (defaultTile >= 21 && defaultTile <= 23)
		{
			tile.setTextureRect(sf::IntRect(402, 0, 200, 200));
		}
		else if (defaultTile >= 24 && defaultTile <= 28)
		{
			tile.setTextureRect(sf::IntRect(402, 200, 200, 200));
		}
		else if (defaultTile >= 29 && defaultTile <= 30)
		{
			tile.setTextureRect(sf::IntRect(202, 200, 200, 200));
		}
	}
	else if (GetType() == SHOP)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
	}
}

void Tile::SetShop()
{
	if (ResourceManagement::isPlacingShop)
	{
		SetType(SHOP);
		CheckType();
		ResourceManagement::AddShops(1);
		ResourceManagement::isPlacingShop = false;
	}
}

void Tile::Hover(sf::Texture& texture)
{
	if (GetType() == NONE)
	{
		tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
		tile.setFillColor(sf::Color(0,255,0,100));
		tile.setTexture(&texture);
	}
}

void Tile::ResetTexture()
{
	SetType(NONE);
	CheckType();
}

void Tile::SetType(TileType type)
{
	tileType = type;
	CheckType();
}

TileType Tile::GetType()
{
	return tileType;
}







