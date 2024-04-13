#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Globals.h"
#include "GameManager.h"


class GameUI
{
public:
	GameUI();
	void Init();
	void Draw(sf::RenderWindow& window);
	void HandleEvent(sf::Event event);
	void Update();

	void HoverArrow();
	void MoveBackground();

	sf::RectangleShape background;
	sf::RectangleShape arrow;
	sf::RectangleShape inventoryBag;
	sf::RectangleShape pause;
	sf::RectangleShape enemyBase;
	sf::Text enemyBasesLeftText;
	int enemyBasesLeft;

	std::vector<sf::RectangleShape*> uiItems;

	float startX;
	float endX;

	bool isMenuOpen;
};

