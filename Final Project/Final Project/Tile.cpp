#include "Tile.h"
#include "Globals.h"
#include <iostream>
#include "Textures.h"

void Tile::Init(sf::Vector2f& position)
{
	tile.setFillColor(sf::Color::Transparent);
	tile.setSize(sf::Vector2f(Global::CELL_SIZE, Global::CELL_SIZE));
	tile.setOutlineThickness(0.5f);
	tile.setOutlineColor(sf::Color(255, 255, 255, 100));
	tile.setPosition(position);
	
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(tile);
}

void Tile::SetShop()
{
	tile.setTexture(&Textures::GetInstance().GetTexture("shop"));
}
