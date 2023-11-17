#include "Tile.h"
#include <iostream>
#include "Globals.h"
#include "Textures.h"
#include "ResourceManagement.h"

void Tile::Init(sf::Vector2f& position)
{
	//tile.setFillColor(sf::Color::Transparent);
	tile.setSize(sf::Vector2f(Global::CELL_SIZE, Global::CELL_SIZE));
	//tile.setOutlineThickness(0.5f);
	//tile.setOutlineColor(sf::Color(255, 255, 255, 100));
	tile.setPosition(position);
	
	tile.setTextureRect(sf::IntRect(0, 0, 200, 200));
	tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));

	/*tile.setTexture(Textures::GetInstance().GetTexture("tiles"));
	tile.setTextureRect(sf::IntRect(0, 0, 100, 100));
	tile.setScale(2, 2);*/
	//tile.setScale(100.f / 56.f, 100.f / 56.f);
	tile.setPosition(position);
	tileType = NONE;
	//tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
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
	if (tileType == NONE)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("tiles"));
	}
	else if (tileType == SHOP)
	{
		tile.setFillColor(sf::Color::White);
		tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
	}
}

void Tile::SetShop()
{
	if (ResourceManagement::isPlacingShop)
	{
		tileType = SHOP;
		CheckType();
		ResourceManagement::AddShops(1);
		ResourceManagement::isPlacingShop = false;
	}
}

void Tile::Hover(sf::Texture& texture)
{
	if (tileType == NONE)
	{
		tile.setFillColor(sf::Color(0,255,0,100));
		tile.setTexture(&texture);
	}
}

void Tile::ResetTexture()
{
	tileType = NONE;
	CheckType();
}







