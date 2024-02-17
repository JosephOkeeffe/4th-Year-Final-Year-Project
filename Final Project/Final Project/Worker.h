#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "GoldMine.h"


#include "Headquarters.h"

class GoldMine;

class Worker : public Characters
{
public:
	Worker();
	void Update() override;
	void MouseRelease() override;
	void AnimateWorker();
	void CheckAnimationState();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();
	GoldMine* workingPlace = nullptr;

	bool isWorking = false;

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


};

