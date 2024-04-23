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
	void Attack(sf::Vector2f target);

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

	bool isChargingUp = false;
	bool canShoot = false;

	sf::CircleShape blast;


};

 