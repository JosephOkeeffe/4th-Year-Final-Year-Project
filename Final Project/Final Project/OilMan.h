#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "OilExtractor.h"
#include "Headquarters.h"
#include "Globals.h"

class OilExtractor;

class OilMan : public Characters
{
public:
	OilMan();
	void MouseRelease() override;
	void Update() override;
	void RemoveFromWorkPlace();
	void UpdateWorkingStates();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);
	void AnimateWorker();
	void CheckAnimationState();

	void StopWorking();

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();
	OilExtractor* workingPlace = nullptr;


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

	float defaulScale = 1;

	sf::Clock particleTimer;

};

