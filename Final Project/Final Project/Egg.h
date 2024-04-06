#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
class Egg
{
public:

	Egg(sf::Vector2f pos, int _hatchTime, int tier);
	void Update();
	void Draw(sf::RenderWindow& window);

	sf::Sprite body;
	sf::Texture texture;
	sf::Clock hatchClock;

	int eggTier;
	int hatchTime;

	bool isReadyToHatch;
};

