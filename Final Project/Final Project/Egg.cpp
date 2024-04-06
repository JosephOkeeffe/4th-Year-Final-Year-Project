#include "Egg.h"

Egg::Egg(sf::Vector2f pos, int _health, int _hatchTime)
{
	body.setTexture(Textures::GetInstance().GetTexture("egg"));
	body.setPosition(pos);
	body.setScale(2, 2);

	health = _health;
	hatchTime = _hatchTime;
	isReadyToHatch = false;

	hatchClock.restart();
}

void Egg::Update()
{
	if (hatchClock.getElapsedTime().asSeconds() > hatchTime)
	{
		isReadyToHatch = true;
	}
}

void Egg::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
