#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "UraniumExtractor.h"
#include "Headquarters.h"
class HazmatMan : public Characters
{
public:
	HazmatMan();
	void Update() override;
	void MouseRelease() override;
	void AnimateWorker();
	void CheckAnimationState();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();

private:


	int currentFrameX = 24;
	int currentFrameY = 100;
	int textureWidth = 23;
	int textureHeight = 45;
	int amountOfSprites = 10;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;
	  

	UraniumExtractor* workingPlace = nullptr;
};

