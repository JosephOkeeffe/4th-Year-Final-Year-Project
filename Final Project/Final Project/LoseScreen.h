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

	std::vector<sf::RectangleShape> blocks;
	sf::RectangleShape fullImage;
	sf::IntRect textureRect;

	sf::RectangleShape homeButton;
	sf::Text homeText;

	bool isImageDone;
	sf::Clock timer;


};

