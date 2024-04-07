#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Textures.h"
#include "Globals.h"
#include "GameManager.h"
#include "ItemManager.h"
#include "Stats.h"

class EnemyBase
{
public:

	EnemyBase(sf::Vector2f pos, Item itemNeeded);
	void Init(sf::Vector2f pos);
	void Update();
	void Draw(sf::RenderWindow& window);
	void TakeDamage(int damage);

	void DestroyBase();



	sf::Sprite body;
	sf::Texture texture;
	sf::RectangleShape itemRequiredSprite;
	sf::Text itemRequiredText;
	Item itemRequired;

	bool isOpen;
	bool isDestroyed;
	int itemNeededAmount;

	Stats stats{ 3, 1, 1 };

	sf::Clock redTimer;

};

