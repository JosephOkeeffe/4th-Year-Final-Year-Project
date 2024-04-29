#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"

class Healer : public Characters
{
public:

	Healer();
	void Update() override;
	void Draw() override;
	void Animate(float startX, float startY, float spriteWidth, float spriteHeight, sf::Sprite& sprite, int amountOfSprites) override;

	void CheckAnimationState();
	void Heal();

	sf::Sprite& GetSprite();

private:

	int currentFrameX = 46;
	int currentFrameY = 173;
	int textureWidth = 46;
	int textureHeight = 52;
	int amountOfSprites = 6;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;

	
	bool canShoot = false;
	bool canAnimate = true;

	sf::CircleShape healBlast;

	sf::Clock healTimer;
	sf::Clock delayBetweenHealsTimer;

	float healDelay = 5;


};

