#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "GoldMine.h"
#include "Headquarters.h"
#include "Globals.h"



class GoldMine;

class Miner : public Characters
{
public:
	Miner();
	void MouseRelease() override;
	void Update() override;
	void RemoveFromWorkPlace();
	void UpdateWorkingStates();
	void MoveSpriteToTarget(sf::Vector2f targetPosition);
	void AnimateWorker();
	void CheckAnimationState();

	sf::Sprite& GetSprite();
	sf::Vector2f& GetPos();
	GoldMine* workingPlace = nullptr;


private:
	// 543
	// 348
	int currentFrameX = 60;
	int currentFrameY = 0;
	int textureWidth = 60;
	int textureHeight = 66;
	int amountOfSprites = 8;
	// Moving
	float moveSpeed = 2.0f;

	float defaulScale = 1;

	sf::Clock particleTimer;

};

