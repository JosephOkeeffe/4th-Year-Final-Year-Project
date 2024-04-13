#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "GameManager.h"

class LoseScreen
{
public:
	LoseScreen();
	void Init();
	void Draw(sf::RenderWindow& window);
	void HandleEvent(sf::Event event);
	void Update();

	int blockWidth;
	int blockHeight;
	int fallSpeed;

	static constexpr int numBlocks = 20;

	// Vector to store falling blocks
	std::vector<sf::RectangleShape> blocks;

	// Texture for the squares
	sf::Texture texture;

	// Full image
	sf::Sprite fullImage;

	// Texture rectangle for each block
	sf::IntRect textureRect;

};

