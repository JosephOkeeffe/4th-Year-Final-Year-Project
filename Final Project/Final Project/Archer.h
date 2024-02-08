#pragma once
#include "Characters.h"
#include <SFML/Graphics.hpp>
class Archer : public Characters
{
public:


	Archer();
	void Update() override;
	void AnimateArcher();
	void CheckAnimationState();

	sf::Sprite& GetSprite();	

private:

	int currentFrameX = 35;
	int currentFrameY = 0;
	int textureWidth = 35;
	int textureHeight = 50;
	int amountOfSprites = 2;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;
};

