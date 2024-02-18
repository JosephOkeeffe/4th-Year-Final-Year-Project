#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "UraniumExtractor.h"
#include "Headquarters.h"

class UraniumExtractor;

class HazmatMan : public Characters
{
public:
	HazmatMan();
	void MouseRelease() override;
	void Update() override;
	void RemoveFromWorkPlace();
	void UpdateWorkingStates();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);
	void AnimateWorker();
	void CheckAnimationState();

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();
	UraniumExtractor* workingPlace = nullptr;

private:


	// Idle starting off
	int currentFrameX = 24;
	int currentFrameY = 100;
	int textureWidth = 23;
	int textureHeight = 45;
	int amountOfSprites = 10;
	// Moving
	sf::Vector2f targetPos;
	float moveSpeed = 2.0f;
	  
	float defaultScale = 1.8;

};

