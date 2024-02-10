#pragma once
#include <SFML/Graphics.hpp>
#include "Characters.h"
#include "GoldMine.h"
#include "Headquarters.h"
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

private:

	/*enum WorkerState
	{
		IDLE_STATE,
		SEARCH_FOR_RESOURCE,
		GATHERING,
		RETURN_TO_BASE,
		UNLOADING,
	};*/

	//WorkerState workerState =   IDLE_STATE;

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


	GoldMine* workingPlace = nullptr;
};

