#include "Egg.h"

Egg::Egg(sf::Vector2f pos, int _hatchTime, int tier) : hatchTime(_hatchTime), eggTier(tier)
{
	body.setTexture(Textures::GetInstance().GetTexture("egg"));
	body.setPosition(pos);
	body.setScale(0.3, 0.3);

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
