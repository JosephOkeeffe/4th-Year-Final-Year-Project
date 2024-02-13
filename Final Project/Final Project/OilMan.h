#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "OilExtractor.h"
#include "Headquarters.h"

class OilMan : public Characters
{
public:
	OilMan();
	void Update() override;
	void MouseRelease() override;
	void AnimateWorker();
	void CheckAnimationState();
	void CheckCurretnState();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();

private:

	// 543
	// 348
	int currentFrameX = 60;
	int currentFrameY = 0;
	int textureWidth = 60;
	int textureHeight = 66;
	int amountOfSprites = 8;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;

	OilExtractor* workingPlace = nullptr;
};

