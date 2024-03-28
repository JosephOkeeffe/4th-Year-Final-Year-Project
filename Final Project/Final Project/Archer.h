#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"

class Archer : public Characters
{
public:

	Archer();
	void Update() override;
	void Draw() override;
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites) override;
	void CheckAnimationState();
	void Attack(Enemy* target);

	sf::Sprite& GetSprite();	

private:

	int currentFrameX = 34;
	int currentFrameY = 0;
	int textureWidth = 34;
	int textureHeight = 50;
	int amountOfSprites = 2;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;


	//int bulletRange = 210;
	//float reloadDelay = 3;
	//sf::Clock reloadTimer;

	//Enemy* closestEnemy;
	//float closestEnemyDistance = 500000;

};

 