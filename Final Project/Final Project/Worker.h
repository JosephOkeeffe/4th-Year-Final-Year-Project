#pragma once
#include "Characters.h"
#include <SFML/Graphics.hpp>
class Worker : public Characters
{
public:
	Worker();
	void Update() override;
	void AnimateWorker();
	void CheckAnimationState();

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();

private:

	// 543
	// 348
	int currentFrameX = 0;
	int currentFrameY = 0;
	int textureWidth = 60;
	int textureHeight = 69;
	int amountOfSprites = 8;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;
};

